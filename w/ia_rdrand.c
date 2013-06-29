// ia_rdrand.cpp: Implements the functions for working with the RDRAND instruction on (certain) Intel processors.
//
// Author: Stephen Higgins <sjh@viathefalcon.net>
// Blog: http://blog.viathefalcon.net/
// Twitter: @viathefalcon
// modified for node.js by david howard <dmh2000@gmail.com>

// Includes
//

// Microsoft-specific Intrinsics Headers
#include <intrin.h>

// C Standard Library Headers
#include <string.h>

// Declarations
#include "ia_rdrand.h"

// Macros
//

// Defines the RDRAND instruction in terms of its opcode
#define rdrand_eax	__asm _emit 0x0F __asm _emit 0xC7 __asm _emit 0xF0

// Defines the bit mask used to examine the ecx register returned by cpuid.
// (The 30th bit is set.)
#define RDRAND_MASK	0x40000000

// Defines the result returned when the RDRAND instruction is supported by the host hardware
#define RDRAND_SUPPORTED 0

// Defines the result returned when the RDRAND instruction is unsupported by the host hardware
#define RDRAND_UNSUPPORTED 1

// Defines the result returned when whether or not the hardware supports the RDRAND instruction is unknown
#define RDRAND_SUPPORT_UNKNOWN 2

// Functions
//

// Queries CPUID to see if the RDRAND instruction is supported
int rdrand_cpuid(void) {

	// Check if we are on Intel hardware
	int info[4] = { -1, -1, -1, -1 };
	__cpuid( info, 0 );
	if (memcmp( (const void *) &info[1], (const void *) "Genu", 4 ) != 0 ||
		memcmp( (const void *) &info[3], (const void *) "ineI", 4 ) != 0 ||
		memcmp( (const void *) &info[2], (const void *) "ntel", 4 ) != 0 ){
		return 0;
	}

	// Query the feature itself
	__cpuid( info, 1 );
	return ((info[2] & RDRAND_MASK) == RDRAND_MASK); // info[2] == ecx
}


/* returns nonzero if RDRAND instruction is supported on this processor, 0 otherwise */
int hasRDRAND(void) {

	// Caching the result is cheaper than re-invoking cpuid
	static unsigned supported = RDRAND_SUPPORT_UNKNOWN;
	if (supported == RDRAND_SUPPORT_UNKNOWN){
		supported = (rdrand_cpuid( ) ? RDRAND_SUPPORTED : RDRAND_UNSUPPORTED);
	}
	return (supported == RDRAND_SUPPORTED);
}


/* NOTE : the Intel RDRAND instruction can fail in heavily loaded situation or if a CPU malfunction occurs
          that is why there is a retry count. a value of 10 for retries is normally sufficient
*/

/* get a 32 bit random value using the RDRAND instruction
   will retry  at least 1 or more times as specified by the retry count
   if a valid random number is obtained, r is initialized with the value
   returns nonzero if a valid random number is obtained, 0 otherwise
*/
int rdrand32(uint32_t *r,int retry)
{
    int b;
    int i;

    if (retry == 0) return rdrandx32(r);

    b = 0;
    for(i=0;i<retry;i++) {
        b = rdrandx32(r);
        if (b != 0) {
            break;
        }
    }
    return b;
}


/* get a 32 bit random value using the RDRAND instruction
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

    if (retry == 0) return rdrandx64(r);

    b = 0;
    for(i=0;i<retry;i++) {
        b = rdrandx64(r);
        if (b != 0) {
            break;
        }
    }
    return b;
}