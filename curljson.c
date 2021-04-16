#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "curljson.h"

#define BUFFER_SIZE 10000

/* Data-writing curl callback function, for recieving the json sent by server */
size_t string_callback(void *buf, size_t size, size_t nmemb, void *userp) {
	//printf("\nNow inside string callback function.\n");
	size_t i;
	struct MemoryString *outbuf = (struct MemoryString *)userp;
	char *inbuf = (char *)buf;
	size_t total = size*nmemb;

	for (i=0; i<total; i++) {
		outbuf->memory[outbuf->head++] = inbuf[i];
		printf("%c", outbuf->memory[outbuf->head]);
	}
	
	outbuf->memory[outbuf->head+1] = '\0';
	printf("\nNow inside string callback function. %zu bytes so far.\n", outbuf->size);

	return total;

}

size_t sndfil_callback(void *contents, size_t size, size_t nmemb, void *stream) {
        size_t written = fwrite(contents, size, nmemb, (FILE *)stream);
        printf("\nin callback function, writing data from curl now\n");
        return written;
}

/*Do curl*/
char *receiveJson(char *url, struct curl_slist *header, char *js) {

	/* Initialize curl. */
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl = curl_easy_init();

	/* Select the URL */
	curl_easy_setopt(curl, CURLOPT_URL, url);
	
	/* Prepare to receive JSON from a server via curl
	 * The string_callback function will take care of
	 * all memory allocation during curl performance. */
	struct MemoryString *curlBuf = (struct MemoryString *)malloc(sizeof(struct MemoryString));
	curlBuf->memory = (char *)malloc(BUFFER_SIZE);
	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, string_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, curlBuf);

	/* Authentication is by passing a header when contacting server.
	 * The header can be created in a separate step before this. */
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		printf("\nNot OK\n");
	}

	curl_easy_cleanup(curl);
	curl_global_cleanup();

	/* Now data is in a MemoryString with no \0 byte terinating it.
	 * So we will convert curlBuf to a string and name the string js. */

	/* All data is in js, so we can free curlBuf. */
	free(curlBuf->memory);
	free(curlBuf);

	return js;
}

/*Do curl*/
FILE *receiveFile(char *url, struct curl_slist *header) {

	/* Initialize curl. */
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl = curl_easy_init();

	/* Select the URL */
	curl_easy_setopt(curl, CURLOPT_URL, url);

	/* Prepare to receive JSON from a server via curl
	 * The string_callback function will take care of
	 * all memory allocation during curl performance. */
	FILE *fp = fopen("out.wav", "w"); //data will be written to file
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, sndfil_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

	/* Authentication is by passing a header when contacting server.
	 * The header can be created in a separate step before this. */
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		printf("\nNot OK\n");
	}

	curl_easy_cleanup(curl);
	curl_global_cleanup();
	return fp;
}
