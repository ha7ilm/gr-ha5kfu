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

#ifndef INCLUDED_HA5KFU_EXECPROC_SINK_F_IMPL_H
#define INCLUDED_HA5KFU_EXECPROC_SINK_F_IMPL_H

#include <ha5kfu/execproc_sink_f.h>

namespace gr {
  namespace ha5kfu {

    class execproc_sink_f_impl : public execproc_sink_f
    {
     private:
		std::string commandline;
		int proc_stdin;
		int proc_stdout;
		pid_t child_pid;

     public:
      execproc_sink_f_impl(std::string commandline);
      ~execproc_sink_f_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
	  bool stop();
	  bool start();
    };


  } // namespace ha5kfu
} // namespace gr

#endif /* INCLUDED_HA5KFU_EXECPROC_SINK_F_IMPL_H */

