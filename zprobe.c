// ZPROBE
//
// zProbe is a straight-forward program crafted to facilitate the probing for active domains within a file for both HTTP and HTTPS protocols.
// This utility offers a robust solution for security enthusiasts, ethical hackers, and network professionals seeking to comprehensively analyze and assess the connectivity status of a given list of domains.
//
// Author: synfosec
// https://github.com/synfosec
//

#include "lib/probe.h"
#include "lib/misc.h" 
#include "lib/memutils.h"

// function for handling interrupt signals

static void sigintHandler(int sig_num) {
	if (sig_num == SIGINT || sig_num == SIGTERM) {
		signal(SIGINT, sigintHandler);
		printf("\n\nExiting saftley...\n");

		RET;
	} else {
		printf("\n\nUNKNOWN CODE: Exiting saftley...\n");
		
		RET;
	}
}

int main(int argc, const char **argv) {
	ARGS *arguments = AllocMem(1);

	// check to see if arguments exist
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			banner();
			FreeAllocMem(arguments);

			RET;
		}

		else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
			versionBanner();
			FreeAllocMem(arguments);

			RET;
		}

		else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--options") == 0) {
			switch (i) {
				case 1:
					errBanner("argument", "Filename needs to be second argument, following flags after");
					FreeAllocMem(arguments);

					exit(1);
				default:
					arguments->outFlag = true;

					if (argv[i + 1] == NULL) {
						FreeAllocMem(arguments);
						errBanner("file", "Needs output file name");
					}

					else {
						arguments->output = argv[i + 1];
					}
			}
		}
	}

	// check if there are no arguments
	if (argc < 2) {
		errBanner("argument", "Needs at least one argument");
		FreeAllocMem(arguments);
		ret(1);
	} else {
		// check filename length
		if (strlen(argv[1]) > 30) {
			errBanner("length", "Filename is too large");
			FreeAllocMem(arguments);
			ret(1);
		} else {
			signal(SIGINT, sigintHandler);
			arguments->filename = argv[1];

			// clear screen

			printf("\033[2J\033[H");

			// perform functions
			if (goOverFile(arguments)) {
				printf("\n[+] Done!\n\n");
				FreeAllocMem(arguments);

				RET;
			}
		}
	}
}
