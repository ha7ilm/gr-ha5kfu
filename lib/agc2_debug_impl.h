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

#ifndef INCLUDED_HA5KFU_AGC2_DEBUG_IMPL_H
#define INCLUDED_HA5KFU_AGC2_DEBUG_IMPL_H

#include <ha5kfu/agc2_debug.h>

namespace gr {
  namespace ha5kfu {

    class agc2_debug_impl : public agc2_debug
    {
     private:
      // Nothing to declare in this block.
     float _gain, _max_gain, _reference, _attack_rate, _decay_rate;
     public:
      agc2_debug_impl(float attack_rate, float decay_rate, float ref, float gain, float max_gain);
      ~agc2_debug_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);

      float scale(float input);
	
    };

  } // namespace ha5kfu
} // namespace gr

#endif /* INCLUDED_HA5KFU_AGC2_DEBUG_IMPL_H */

