// ia_rdrand.h: Declares the types and functions for working with the RDRAND instruction on (certain) Intel processors.
//
// Author: Stephen Higgins <sjh@viathefalcon.net>
// Blog: http://blog.viathefalcon.net/
// Twitter: @viathefalcon
// modified for node.js by david howard <dmh2000@gmail.com>

#ifndef __IA_RDRAND_H__
#define __IA_RDRAND_H__

#ifndef _WIN64
#error This implementation requires 64 bit compilation
#endif

// Functions
//
#include <stdint.h>

// Returns true if the host CPU supports the RDRAND instruction
int rdrand_supported(void);

// Invokes rdrand to generate a 32-bit unsigned random number
// Returns true if a random value was available; false otherwise
int __fastcall rdrandx32(__deref_out uint32_t*);
int __fastcall rdrandx64(__deref_out uint64_t*);

#endif
