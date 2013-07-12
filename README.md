rdrand
======

node.js module providing support for the Intel Ivy Bridge (and later) RDRAND instruction.

This is a work in progress!

Intel Ivy Bridge/3rd generation and later Core processors have a hardware random number generator that
is compliant with various crypto standards. This module provides a wrapper around functions to access
the RDRAND instruction to get hardware generated cryptographically secure (per Intel) random numbers.

WARNING: I am not a crypto expert. I just implemented the functions. For more info on RDRAND and the hardware random number
generator, google 'intel RDRAND'. 

Consider using the built-in node Crypto package for random number generation in real apps unless you really know what you are doing.

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

API 
---

    function hasRdrand() : returns a boolean indicating if the processor supports the RDRAND instruction
    // true if it does, false if it doesn't
    // be sure to call this first because if you call one of the following functions on a processor
    // that doesn't support RDRAND, you will be a segfault for an illegal instruction.
    // That is by design. If you need a fallback alternative, build that on top of this module.

    function rdrand32() : returns a 32 bit random number as a whole number , type Number

    function rdrand53() : returns a 53 bit random number as a whole number , type Number 
    // why a 53 bit value? because a Number is a 64 bit float and it has 53 bits of precision.
    // any value larger than what fits in 53 bits will be an approximation which is not what you want here.
    // if you want a full 64 bits, use rdrand64b or rdrand64s
    // I'm not even sure if this is useful. 

    function rdrand64b() : returns an array of 8 bytes comprising the full 64 bit random value

    function rdrand64s() : returns a string of up to 20 digits comprising the full 64 bit random value




