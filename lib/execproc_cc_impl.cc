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
#include "execproc_cc_impl.h"
#include <gnuradio/gr_complex.h>
#include <stdio.h>
#include "popen2.h"
#include <fcntl.h>
#include <signal.h>

namespace gr {
  namespace ha5kfu {

    execproc_cc::sptr
    execproc_cc::make(std::string commandline)
    {
      return gnuradio::get_initial_sptr
        (new execproc_cc_impl(commandline));
    }

    /*
     * The private constructor
     */
    execproc_cc_impl::execproc_cc_impl(std::string commandline)
      : gr::block("execproc_cc",
              gr::io_signature::make(1, 1024, sizeof(gr_complex)),
              gr::io_signature::make(1, 1024, sizeof(gr_complex)))
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
    execproc_cc_impl::~execproc_cc_impl()
    {
    }

    bool
    execproc_cc_impl::start()
	{
		return true;
    }

    bool
    execproc_cc_impl::stop()
    {
		kill(child_pid, SIGKILL);
		return true;
    }
    
    void
    execproc_cc_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = noutput_items;
    }
    
    #define EXECPROC_BUF_SIZE 1024

    int
    execproc_cc_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];

        // Do <+signal processing+>
        // Tell runtime system how many input items we consumed on
        // each input stream.
		if(!child_pid) return 0; //could not open process

        // Do signal processing...
	int result;
	int to_write=0;
	int in_remain=ninput_items[0];
	gr_complex* in_where=(gr_complex*)in;
	for(;;)
	{
		//fprintf(stderr, "to_write=%d in_remain=%d ninput_items[0]=%d\n", to_write, in_remain, ninput_items[0]);
		to_write=(in_remain>EXECPROC_BUF_SIZE)?EXECPROC_BUF_SIZE:in_remain;
		result=write(proc_stdin, in_where, to_write*sizeof(gr_complex));
		if(result<=0) break;	
		in_where+=result/sizeof(gr_complex);
		in_remain-=result/sizeof(gr_complex);
		if(result%sizeof(gr_complex)>0) fprintf(stderr, "[gr-ha5kfu/execproc] write atomicity error!\n");
		if(!in_remain) break;
	}
	consume_each (ninput_items[0]-in_remain);

	/*
	fprintf(stderr, "writing %d items\n", ninput_items[0]);
	result=write(proc_stdin, in, ninput_items[0]*sizeof(gr_complex));
	consume_each (ninput_items[0]);
	fprintf(stderr, "%d items consumed\n", ninput_items[0]);
	*/
	
	int out_remain=noutput_items;
	int to_read=0;
	gr_complex *read_where=out;
	for(;;)
	{
		//fprintf(stderr, "to_read=%d out_remain=%d noutput_items=%d\n", to_read, out_remain, noutput_items);
		to_read=(out_remain>EXECPROC_BUF_SIZE)?EXECPROC_BUF_SIZE:out_remain;
		result=read(proc_stdout, read_where, to_read*sizeof(gr_complex));
		if(result<=0) return noutput_items-out_remain;			
		read_where+=result/sizeof(gr_complex);
		out_remain-=result/sizeof(gr_complex);
		if(result%sizeof(gr_complex)>0) fprintf(stderr, "[gr-ha5kfu/execproc] read atomicity error!\n");
		if(!to_read) return noutput_items;
	}

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace ha5kfu */
} /* namespace gr */

