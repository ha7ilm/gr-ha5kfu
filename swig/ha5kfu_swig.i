/* -*- c++ -*- */

#define HA5KFU_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ha5kfu_swig_doc.i"

%{
#include "ha5kfu/execproc_cf.h"
#include "ha5kfu/debug_minmax_f.h"
#include "ha5kfu/execproc_cc.h"
#include "ha5kfu/execproc_ff.h"
#include "ha5kfu/agc2_debug.h"
#include "ha5kfu/execproc_sink_f.h"
%}


%include "ha5kfu/execproc_cf.h"
GR_SWIG_BLOCK_MAGIC2(ha5kfu, execproc_cf);
%include "ha5kfu/debug_minmax_f.h"
GR_SWIG_BLOCK_MAGIC2(ha5kfu, debug_minmax_f);
%include "ha5kfu/execproc_cc.h"
GR_SWIG_BLOCK_MAGIC2(ha5kfu, execproc_cc);
%include "ha5kfu/execproc_ff.h"
GR_SWIG_BLOCK_MAGIC2(ha5kfu, execproc_ff);
%include "ha5kfu/agc2_debug.h"
GR_SWIG_BLOCK_MAGIC2(ha5kfu, agc2_debug);
%include "ha5kfu/execproc_sink_f.h"
GR_SWIG_BLOCK_MAGIC2(ha5kfu, execproc_sink_f);
