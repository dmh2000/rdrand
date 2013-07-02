#include <string.h>
#include "../rdrand.h"

/*

portions of the following code are taken from the intel librdrand library
Copyright � 2012, Intel Corporation.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

-       Redistributions of source code must retain the above copyright notice,
		this list of conditions and the following disclaimer.
-       Redistributions in binary form must reproduce the above copyright
		notice, this list of conditions and the following disclaimer in the
		documentation and/or other materials provided with the distribution.
-       Neither the name of Intel Corporation nor the names of its contributors
		may be used to endorse or promote products derived from this software
		without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY INTEL CORPORATION "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
EVENT SHALL INTEL CORPORATION BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/
#define __cpuid(x,y) asm volatile("cpuid":"=a"(x[0]),"=b"(x[1]),"=c"(x[2]),"=d"(x[3]):"a"(y))
#define _rdrand16(x) ({ unsigned char err; asm volatile(".byte 0x66; .byte 0x0f; .byte 0xc7; .byte 0xf0; setc %1":"=a"(*x), "=qm"(err)); err; })
#define _rdrand32(x) ({ unsigned char err; asm volatile(".byte 0x0f; .byte 0xc7; .byte 0xf0;             setc %1":"=a"(*x), "=qm"(err)); err; })
#define _rdrand64(x) ({ unsigned char err; asm volatile(".byte 0x48; .byte 0x0f; .byte 0xc7; .byte 0xf0; setc %1":"=a"(*x), "=qm"(err)); err; })
#define RDRAND_MASK	0x40000000

// determine if 64 bit build
#if defined(__LP64__) || defined(_LP64)
#define BUILD_64   1
#endif

/* returns nonzero if RDRAND instruction is supported on this processor, 0 otherwise */
int hasRDRAND(void)
{
	int info[4] = {-1, -1, -1, -1};

	/* Are we on an Intel processor? */

	__cpuid(info, 0);

	if (memcmp((void *) &info[1], (void *) "Genu", 4) != 0 ||
		memcmp((void *) &info[3], (void *) "ineI", 4) != 0 ||
		memcmp((void *) &info[2], (void *) "ntel", 4) != 0 ) {

		return 0;
	}

	/* Do we have RDRAND? */

	 __cpuid(info, /*feature bits*/1);

	 int ecx = info[2];
	 if ((ecx & RDRAND_MASK) == RDRAND_MASK)
		 return 1;
	 else
		 return 0;
}

/* get a 32 bit random value using the RDRAND instruction
   will retry  at least 1 or more times as specified by the retry count
   if a valid random number is obtained, r is initialized with the value
   returns nonzero if a valid random number is obtained, 0 otherwise
*/
int rdrand32(uint32_t *r,int retry)
{
    int b;
    int i;

    if (retry == 0) return _rdrand32(r);

    b = 0;
    for(i=0;i<retry;i++) {
        b = _rdrand32(r);
        if (b != 0) {
            break;
        }
    }
    return b;
}


/* get a 64 bit random value using the RDRAND instruction
   will retry  at least 1 or more times as specified by the retry count
   if a valid random number is obtained, r is initialized with the value
   returns nonzero if a valid random number is obtained, 0 otherwise

   if running in 32 bit mode, it will get 2 32 bit random values and multiply them together
   according to the Intel spec, this is still cryptographically valid
*/
int rdrand64(uint64_t *r,int retry)
{
    int b;
    int i;

    if (retry == 0) return _rdrand64(r);

    b = 0;
    for(i=0;i<retry;i++) {
#if defined(BUILD_64)
        b = _rdrand64(r);
        if (b != 0) {
            break;
        }
#else
        {
            // running on 32 bit ivy bridge
            // get 2 32 bit values
            uint32_t r1;
            uint32_t r2;
            b = _rdrand32(&r1);
            if (b == 0) {
                continue;
            }
            b = _rdrand32(&r2);
            if (b == 0) {
                continue;
            }
            // the intel spec says a single 32x32 multiply is still cryptographically valid
            r = (uint64_t)r1 * (uint64_t)r2;
        }
        break;
#endif
    }
    return b;
}
