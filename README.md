rdrand
======

node.js module providing support for the Intel Ivy Bridge (and later) RDRAND instruction.

This is a work in progress!

Intel Ivy Bridge/2nd generation and later Core processors have a hardware random number generator that
is compliant with various crypto standards. This module provides a wrapper around functions to access
the RDRAND instruction to get hardware generated cryptographically secure (per Intel) random numbers.

WARNING: I am not a crypto expert. I just implemented the functions. For more info on RDRAND and the hardware random number
generator, google 'intel RDRAND'. 

platforms tested
----------------
* Ubuntu Linux 13.x, x64 : npm install works and executes properly
  the RDRAND instruction is supported in the 32 bit mode of the processor, however 32 bit builds are not yet implemented here
* Windows 8 with Visual Studio 2012 : works but requires manual install. see w/readme.txt

resources used
--------------
* RDRAND64 : Author: Stephen Higgins <sjh@viathefalcon.net> Blog: http://blog.viathefalcon.net/
* Intel RDRAND library :  http://software.intel.com/en-us/articles/intel-digital-random-number-generator-drng-software-implementation-guide

license
-------
* MIT license with the exception u/rdrand.c - Intel specific license (freely reusable)



