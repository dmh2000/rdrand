#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ia_rdrand.h"

int getRand(uint64_t *r)
{
	int b;
	int i;
	b = rdrand_supported();
	if (b) {
		for(i=0;i<1000;++i) {
			b = rdrandx64(r);
			if (b) {
				break;
			}
		}
	}
	return b;
}


int main(int argc,char *argv[])
{
	uint64_t r;
	int b;

	r = 0;
	b = getRand(&r);
	printf("%d %llu\n",b,r);

	return 0;
}
