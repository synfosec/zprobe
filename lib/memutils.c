#include "memutils.h"
#include "misc.h"

ARGS *AllocMem(unsigned short int allocation) {
	ARGS *args = (ARGS *)calloc(allocation, sizeof(ARGS));

	if (args == NULL) {
		err("allocation");
	}

	return args;
}

void FreeAllocMem(ARGS *args) {
	memset(args, 0, sizeof(ARGS));
	free(args);
}
