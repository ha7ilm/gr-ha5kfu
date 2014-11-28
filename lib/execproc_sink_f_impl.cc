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
#include "execproc_sink_f_impl.h"
#include <gnuradio/gr_complex.h>
#include <stdio.h>
#include "popen2.h"
#include <fcntl.h>
#include <signal.h>


namespace gr {
  namespace ha5kfu {

    execproc_sink_f::sptr
    execproc_sink_f::make(std::string commandline)
    {
      return gnuradio::get_initial_sptr
        (new execproc_sink_f_impl(commandline));
    }

    /*
     * The private constructor
     */
    execproc_sink_f_impl::execproc_sink_f_impl(std::string commandline)
      : gr::sync_block("execproc_sink_f",
              gr::io_signature::make(1, 1024, sizeof(float)),
              gr::io_signature::make(0, 0, 0))
    {
		this->commandline=commandline;
		child_pid=popen2(commandline.c_str(), &proc_stdin, &proc_stdout);
		if(!child_pid) fprintf(stderr, "[gr-ha5kfu/execproc] error: could not open child process!\n");
		else fprintf(stderr, "[gr-ha5kfu/execproc] child process opened!\n");
		int flags = fcntl(proc_stdout, F_GETFL, 0);
		fcntl(proc_stdout, F_SETFL, flags | O_NONBLOCK);
		flags = fcntl(proc_stdin, F_GETFL, 0);
		fcntl(proc_stdin, F_SETFL, flags | O_NONBLOCK);
	}

    /*
     * Our virtual destructor.
     */
    execproc_sink_f_impl::~execproc_sink_f_impl()
    {
    }

    bool execproc_sink_f_impl::start() { return true; }

    bool execproc_sink_f_impl::stop()
    {
		kill(child_pid, SIGKILL);
		return true;
    }

#define EXECPROC_BUF_SIZE 1024

    int
    execproc_sink_f_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items) //@Andris: in fact this is the _input_ item count
    {
        const float *in = (const float *) input_items[0];

        // Do <+signal processing+>
		
		if(!child_pid) return 0; //could not open process

        // Do signal processing...
		int result;
		int to_write=0;
		int in_remain=noutput_items;
		float* in_where=(float*)in;
		for(;;)
		{
			//fprintf(stderr, "to_write=%d in_remain=%d ninput_items[0]=%d\n", to_write, in_remain, ninput_items[0]);
			to_write=(in_remain>EXECPROC_BUF_SIZE)?EXECPROC_BUF_SIZE:in_remain;
			result=write(proc_stdin, in_where, to_write*sizeof(float));
			if(result<=0) break;	
			in_where+=result/sizeof(float);
			in_remain-=result/sizeof(float);
			if(result%sizeof(float)>0) fprintf(stderr, "[gr-ha5kfu/execproc] write atomicity error!\n");
			if(!in_remain) break;
		}
		
		//flush stdout of the process
		static char zerobuf[1024];
		for(;;)
		{
			result=read(proc_stdout, zerobuf, 1024);
			if(result<=0) break;			
		}
		// Tell runtime system how many <s>output</s> input items we <s>produced.</s> consumed.
        return noutput_items-in_remain;
    }

  } /* namespace ha5kfu */
} /* namespace gr */

