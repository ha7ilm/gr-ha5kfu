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


#ifndef INCLUDED_HA5KFU_EXECPROC_CF_H
#define INCLUDED_HA5KFU_EXECPROC_CF_H

#include <ha5kfu/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace ha5kfu {

    /*!
     * \brief <+description of block+>
     * \ingroup ha5kfu
     *
     */
    class HA5KFU_API execproc_cf : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<execproc_cf> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ha5kfu::execproc_cf.
       *
       * To avoid accidental use of raw pointers, ha5kfu::execproc_cf's
       * constructor is in a private implementation
       * class. ha5kfu::execproc_cf::make is the public interface for
       * creating new instances.
       */
      static sptr make(std::string commandline);
    };

  } // namespace ha5kfu
} // namespace gr

#endif /* INCLUDED_HA5KFU_EXECPROC_CF_H */

