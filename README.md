gr-ha5kfu
=========

This is a set of GNU Radio blocks written by Andras Retzler, HA7ILM &lt;randras@sdr.hu&gt;

These blocks are not perfect and have quite limited functionality, just enough for testing <a href="http://github.com/simonyiszk/csdr">libcsdr</a>.

Run to build:

	mkdir build
	cd build
	cmake ..
	make
	sudo make install

## Execute External Process

- It spawns an external process with a given command-line. (You can use shell pipelines.)
- Its input is redirected to the STDIN of the process.
- The STDOUT of the process is redirected to the output of the block.
- It can deal with *Float* and *Complex* data.
- You should exit the running flowgraph by closing the WX GUI window (if there is one) instead of killing it in GRC.  
Doing the latter, the spawned external process(es) will not be closed properly.

## Execute External Process Sink

It does the same as the previous one, but it does not have an output.

Note: if you would need something like an *Execute External Process Source*, just connect a *Null Source* to the input of the *Execute External Process* block.

## Show Min/Max Value in Console

It prints the minimal and maximal value for the received *Float* input buffers to the GRC console.

## AGC2 Debug

It works just as AGC2 (built into GNU Radio), but it outputs the gain envelope instead of the amplified signal.


