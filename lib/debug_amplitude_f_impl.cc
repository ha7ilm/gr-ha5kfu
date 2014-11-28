/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
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
#include "debug_amplitude_f_impl.h"
#include <float.h>

namespace gr {
  namespace ha5kfu {

    debug_amplitude_f::sptr
    debug_amplitude_f::make(int samplecount)
    {
      return gnuradio::get_initial_sptr
        (new debug_amplitude_f_impl(samplecount));
    }

    /*
     * The private constructor
     */
    debug_amplitude_f_impl::debug_amplitude_f_impl(int samplecount)
      : gr::sync_block("debug_amplitude_f",
              gr::io_signature::make(samplecount, samplecount, sizeof(flot)),
              gr::io_signature::make(0, 0, 0))
    {}

    /*
     * Our virtual destructor.
     */
    debug_amplitude_f_impl::~debug_amplitude_f_impl()
    {
    }

    int
    debug_amplitude_f_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];

		float max=FLT_MAX;
		float min=FLT_MIN;
        // Do <+signal processing+>
		for(int i=0;i<ninput_items[0];i++)
		{
			if(min>in[i]) min=in[i];
			if(max<in[i]) max=in[i];
		}
		
		fprintf(stderr,"[gr-ha5kfu/debug_amplitude] Block min = %g, max = %g\n",min,max);

		consume_each (ninput_items[0]);
        // Tell runtime system how many output items we produced.
        return 0;
    }

  } /* namespace ha5kfu */
} /* namespace gr */

