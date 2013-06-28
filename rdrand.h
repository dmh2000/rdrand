#ifndef __RDRAND_H__
#define __RDRAND_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* returns nonzero if RDRAND instruction is supported on this processor, 0 otherwise */
int hasRDRAND(void);

/* NOTE : the Intel RDRAND instruction can fail in heavily loaded situation or if a CPU malfunction occurs
          that is why there is a retry count. a value of 10 for retries is normally sufficient
*/

/* get a 16 bit random value using the RDRAND instruction
   will retry  at least 1 or more times as specified by the retry count
   if a valid random number is obtained, r is initialized with the value
   returns nonzero if a valid random number is obtained, 0 otherwise
*/
int rdrand16(uint16_t *r,int retry);

/* get a 32 bit random value using the RDRAND instruction
   will retry  at least 1 or more times as specified by the retry count
   if a valid random number is obtained, r is initialized with the value
   returns nonzero if a valid random number is obtained, 0 otherwise
*/
int rdrand32(uint32_t *r,int retry);

/* get a 64 bit random value using the RDRAND instruction
   will retry at least 1 or more times as specified by the retry count
   if a valid random number is obtained, r is initialized with the value
   returns nonzero if a valid random number is obtained, 0 otherwise
*/
int rdrand64(uint64_t *r,int retry);

#ifdef __cplusplus
}
#endif

#endif
