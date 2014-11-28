/* -*- c++ -*- */
/* 
 * Copyright 2014 Andras Retzler <ha7ilm@sdr.hu>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "debug_minmax_f_impl.h"
#include <float.h>
#include <stdio.h>

namespace gr {
  namespace ha5kfu {

    debug_minmax_f::sptr
    debug_minmax_f::make(int samplecount)
    {
      return gnuradio::get_initial_sptr
        (new debug_minmax_f_impl(samplecount));
    }

    /*
     * The private constructor
     */
    debug_minmax_f_impl::debug_minmax_f_impl(int samplecount)
      : gr::sync_block("debug_minmax_f",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(0, 0, 0))
    {
		this->samplecount=samplecount;
	}

    /*
     * Our virtual destructor.
     */
    debug_minmax_f_impl::~debug_minmax_f_impl()
    {
    }

    int
    debug_minmax_f_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items) //@Andris: in fact this is the _input_ item count
    {
        const float *in = (const float *) input_items[0];
		float max=FLT_MIN;
		float min=FLT_MAX;


        // Do signal processing
		for(int i=0;i<noutput_items;i++)
		{
			if(min>in[i]) min=in[i];
			if(max<in[i]) max=in[i];
		}
		
		fprintf(stderr,"[gr-ha5kfu/debug_amplitude] Block min = %g and max = %g of %d items\n",min,max, noutput_items);

        // Tell runtime system how many <s>output</s> input items we <s>produced.</s> consumed.
        return noutput_items;
    }

  } /* namespace ha5kfu */
} /* namespace gr */

