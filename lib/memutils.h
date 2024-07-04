#ifndef MEMUTILS_H
#define MEMUTILS_H
#pragma once
#include "misc.h"

ARGS *AllocMem(unsigned short int allocation);
void FreeAllocMem(ARGS *args);

#endif
