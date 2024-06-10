#include <stdio.h>

void title(void)
{
	puts("┌─┐╔═╗┬─┐┌─┐┌┐ ┌─┐");
	puts("┌─┘╠═╝├┬┘│ │├┴┐├┤ ");
	puts("└─┘╩  ┴└─└─┘└─┘└─┘");
	printf("    [synfosec]\n\n");
}

void errBanner(const char *errTitle, const char* err) {
	title();
    fprintf(stderr, "%s: %s\n\nusage: zprobe-cli [FILENAME]\nnetwork url endpoint checker\n\noptions:\n\nmandatory args:\n\tfilename:  file of URL's to use for scan\n\nargs:\n\t-h, --help:  prints this\n\t-v, --version:  prints version of program\n\n", errTitle, err);
}

void banner() {
	title();
    printf("usage: zprobe-cli [FILENAME]\nnetwork url endpoint checker\n\noptions:\n\nmandatory args:\n\tfilename:  file of URL's to use for scan\n\nargs:\n\t-h, --help:  prints this\n\t-v, --version:  prints version of program\n\n");
}

void versionBanner() {
    printf("zprobe-cli\nnetwork url endpoint checker\nauthor: synfosec(https://github.com/synfosec)\nversion: 0.1\n\n");
}
