// ZPROBE
//
// zProbe is a straight-forward program crafted to facilitate the probing for active domains within a file for both HTTP and HTTPS protocols.
// This utility offers a robust solution for security enthusiasts, ethical hackers, and network professionals seeking to comprehensively analyze and assess the connectivity status of a given list of domains.
//
// Author: synfosec
// https://github.com/synfosec
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include "lib/probe.h"
#include "lib/misc.h" 

// function for handling interrupt signals

static void sigintHandler(int sig_num) {
	if (sig_num == SIGINT || sig_num == SIGTERM) {
		signal(SIGINT, sigintHandler);
		printf("\n\nExiting saftley...\n");
		exit(0);
	} else {
		printf("\n\nUNKNOWN CODE: Exiting saftley...\n");
		exit(0);
	}
}

int main(int argc, const char **argv) {
	// [ TODO ]
	bool subFlag = false;

	// check to see if arguments exist
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            banner();
            exit(0);
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
			versionBanner();
            exit(0);
        } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--subdomains") == 0) {
			subFlag = true;
		}
    }

	// check if there are no arguments
    if (argc < 2) {
        errBanner("argument", "Needs at least one argument");
        exit(1);
    } else {
		// check filename length
        if (strlen(argv[1]) > 30) {
            errBanner("length", "Filename is too large");
            exit(1);
        } else {
			signal(SIGINT, sigintHandler);

			// clear screen
			printf("\033[2J\033[H");
			// perform functions
            if (goOverFile(argv[1], subFlag)) {
				printf("\n[+] Done!\n\n");
                exit(0);
            }
        }
    }
}
