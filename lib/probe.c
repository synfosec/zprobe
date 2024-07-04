// PROBING LIBRARY

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "misc.h"
#include "curl/curl.h"

// connecting to endpoint and getting ipv4/6

static void getA(const char *domain) {
    char domain_copy[256];
    strncpy(domain_copy, domain, sizeof(domain_copy) - 1);
    domain_copy[sizeof(domain_copy) - 1] = '\0';

    char *token = strtok(domain_copy, "\n");
    if (token == NULL) {
        fprintf(stderr, "Invalid domain\n");
        return;
    }

    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int status;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(token, NULL, &hints, &result);
    if (status != 0) {
		fprintf(stderr, "\033[1;31mdead endpoint\033[0m: %s\n", token);
        return;
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        void *addr;
        char ipstr[INET6_ADDRSTRLEN];

        if (rp->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
            addr = &(ipv4->sin_addr);
            inet_ntop(rp->ai_family, addr, ipstr, sizeof(ipstr));
            printf("\033[1;32m[A] \033[0m%s => \033[1;33m%s\033[0m\n", token, ipstr);
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
            addr = &(ipv6->sin6_addr);
            inet_ntop(rp->ai_family, addr, ipstr, sizeof(ipstr));
            printf("\033[1;32m[AAAA] \033[0m%s => \033[1;33m%s\033[0m\n", token, ipstr);
        }
    }

    freeaddrinfo(result);
}

// perform curl

static void curlFunc(char *domain) {
	domain = strtok(domain, "\n");

	char httpDomain[256] = "http://";
	char httpsDomain[256] = "https://";

	strncat(httpDomain, domain, strlen(domain) + strlen(httpDomain));
	strncat(httpsDomain, domain, strlen(domain) + strlen(httpsDomain));

	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();

	if (curl) {
		getA(domain);

		char *rEndpoint = NULL;

		curl_easy_setopt(curl, CURLOPT_URL, httpDomain);
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/43.0.2357.134 Safari/537.36");
		res = curl_easy_perform(curl);

		if (res == CURLE_OK) {
			long response_code;

			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &rEndpoint);

			if (response_code == 200) {
				printf("\033[1;32m[OK]\033[0m %ld : %s\n", response_code, httpDomain);
			} else if (response_code > 200 && response_code < 400) {
				printf("\033[1;34m[REDIRECT]\033[0m %ld : %s => %s\n", response_code, httpDomain, (char*)rEndpoint);
			} else if (response_code == 404) {
				printf("\033[1;33m[NOT FOUND]\033[0m %ld: %s\n", response_code, httpDomain);
			} else if (response_code == 500) {
				printf("\033[1;33m[INTERNAL SERVER ERROR]\033[0m %ld: %s\n", response_code, httpDomain);
			} else {
				printf("\033[1;31m[ERROR]\033[0m %ld: %s\n", response_code, httpDomain);
			}
		}

		curl_easy_cleanup(curl);
		curl = curl_easy_init();

		curl_easy_setopt(curl, CURLOPT_URL, httpsDomain);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
		res = curl_easy_perform(curl);

		if (res == CURLE_OK) {
			long response_code;

			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

			if (response_code == 200) {
				printf("\033[1;32m[OK]\033[0m %ld : %s\n", response_code, httpsDomain);
			} else if (response_code > 200 && response_code < 400) {
				printf("\033[1;34m[REDIRECT]\033[0m %ld : %s => %s\n", response_code, httpsDomain, (char *)rEndpoint);
			} else if (response_code == 404) {
				printf("\033[1;33m[NOT FOUND]\033[0m %ld: %s\n", response_code, httpsDomain);
			} else if (response_code == 500) {
				printf("\033[1;33m[INTERNAL SERVER ERROR]\033[0m %ld: %s\n", response_code, httpsDomain);
			} else {
				printf("\033[1;31m[ERROR]\033[0m %ld: %s\n", response_code, httpsDomain);
			}
		}

		curl_easy_cleanup(curl);
	}
}

// loop over file and perform curlFunc

int goOverFile(ARGS *arg_pointer) {
	FILE *fp = fopen(arg_pointer->filename, "r");

	if (fp == NULL) {
		errBanner("file", "File does not exist");
		exit(0);
	} else {
		char *line = NULL;
		size_t len = 0;
		ssize_t read;

		title();

		while ((read = getline(&line, &len, fp)) != -1) {
			if (strstr(line, "http://") != NULL || strstr(line, "https://") != NULL) {
				errBanner("file", "File contains http:// or https://");
				exit(1);
			} else {
				curlFunc(line);
			}
		}

		fclose(fp);

		return 1;
	}
}
