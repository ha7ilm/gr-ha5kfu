/* -*- c++ -*- */
/* 
 * Copyright 2014 Andras Retzler <ha7ilm@sdr.hu>.
 * Copyright 2006,2012 Free Software Foundation, Inc.
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
#include "agc2_debug_impl.h"

namespace gr {
  namespace ha5kfu {

    agc2_debug::sptr
    agc2_debug::make(float attack_rate, float decay_rate, float ref, float gain, float max_gain)
    {
      return gnuradio::get_initial_sptr
        (new agc2_debug_impl(attack_rate, decay_rate, ref, gain, max_gain));
    }

    /*
     * The private constructor
     */
    agc2_debug_impl::agc2_debug_impl(float attack_rate, float decay_rate, float ref, float gain, float max_gain)
      : gr::block("agc2_debug",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float))), 
              _attack_rate(attack_rate), _decay_rate(decay_rate), _reference(ref), _gain(gain), _max_gain(max_gain) //@Andris
    {}

    /*
     * Our virtual destructor.
     */
    agc2_debug_impl::~agc2_debug_impl()
    {
    }

    void
    agc2_debug_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = noutput_items;
    }


	float agc2_debug_impl::scale(float input)
	{
	  float output = input * _gain;

	  float tmp = (fabsf(output)) - _reference;
	  float rate = _decay_rate;
	  if(fabsf(tmp) > _gain) {
	    rate = _attack_rate;
	  }
	  _gain -= tmp*rate;

	  // Not sure about this
	  if(_gain < 0.0)
	    _gain = 10e-5;

	  if(_max_gain > 0.0 && _gain > _max_gain) {
	    _gain = _max_gain;
	  }
	  //return output;
	  return _gain; //@Andris
	}



    int
    agc2_debug_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const float *in = (const float*) input_items[0];
        float *out = (float *) output_items[0];

        // Do signal processing.
		noutput_items = ninput_items[0];
        for(unsigned i = 0; i < noutput_items; i++) out[i] = scale(in[i]);


        // Tell runtime system how many input items we consumed on each input stream.
        consume_each (noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace ha5kfu */
} /* namespace gr */

