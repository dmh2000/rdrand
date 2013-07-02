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
* Windows 8 with Visual Studio 2012 : works but requires manual install. node-gyp build not working yet


