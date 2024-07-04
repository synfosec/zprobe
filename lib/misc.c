#include "misc.h"

void title(void)
{
	puts("┌─┐╔═╗┬─┐┌─┐┌┐ ┌─┐");
	puts("┌─┘╠═╝├┬┘│ │├┴┐├┤ ");
	puts("└─┘╩  ┴└─└─┘└─┘└─┘");
	printf("    [synfosec]\n\n");
}

void errBanner(const char *ERROR_TITLE, const char* ERR) {
	title();
    fprintf(stderr, "%s: %s\n\nusage: zprobe-cli [FILENAME] [-h, --help|-v, --version|-o, --output]\nnetwork url endpoint checker\n\noptions:\n\nmandatory args:\n\tfilename:  file of URL's to use for scan\n\nargs:\n\t-h, --help:  prints this\n\t-v, --version:  prints version of program\n\t-o, --output:  outputs to a file\n\n", ERROR_TITLE, ERR);
}

void banner() {
	title();
    printf("usage: zprobe-cli [FILENAME] [-h, --help|-v, --version|-o, --output]\nnetwork url endpoint checker\n\noptions:\n\nmandatory args:\n\tfilename:  file of URL's to use for scan\n\nargs:\n\t-h, --help:  prints this\n\t-v, --version:  prints version of program\n\t-o, --output:  outputs to a file\n\n");
}

void versionBanner() {
    printf("zprobe-cli\nnetwork url endpoint checker\nauthor: synfosec(https://github.com/synfosec)\nversion: 0.1\n\n");
}

void ret(unsigned int STATUS) {
	exit(STATUS);
}

void err(const char *msg) {
	fprintf(stderr, "\n[ ERROR ] %s\n\n", msg);
	ret(1);
}
