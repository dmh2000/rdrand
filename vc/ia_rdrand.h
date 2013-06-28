// ia_rdrand.h: Declares the types and functions for working with the RDRAND instruction on (certain) Intel processors.
//
// Author: Stephen Higgins <sjh@viathefalcon.net>
// Blog: http://blog.viathefalcon.net/
// Twitter: @viathefalcon
//

// Functions
//
#include <stdint.h>

// Returns true if the host CPU supports the RDRAND instruction
int rdrand_supported(void);

// Invokes rdrand to generate a 32-bit unsigned random number
// Returns true if a random value was available; false otherwise
#ifdef _WIN64
int __fastcall rdrandx64(__deref_out uint64_t*);
#else
int rdrand(__deref_out unsigned*);
#endif
