#ifndef MISC_H
#define MISC_H
#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#define RET ret(0);

typedef struct ARGS {
	bool outFlag;
	const char *output;
	const char *filename;
} ARGS;

void title(void);
void errBanner(const char *ERROR_TITLE, const char *ERR);
void banner();
void versionBanner();
void ret(unsigned int);
void err(const char *msg);

#endif
