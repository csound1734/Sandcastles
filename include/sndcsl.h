#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <jsmn.h>

struct MemoryString
{
 	char *memory;
	size_t size;
	size_t head;
};

/* Data-writing curl callback function. The user data struct, userp, should
 * be already allocated before anything happens.
size_t write_callback(void *buf, size_t size, size_t nmemb, void *userp) {
	size_t i;
	struct MemoryString *outbuf = (struct MemoryString *)userp;
	size_t total = size*nmemb;

	if (outbuf = NULL) {
		outbuf = malloc(size_of(MemoryString);
		outbuf->memory = NULL;
		outbuf->size = 0;
		outbuf->head = 0;
	}
	
	if (outbuf->size - outbuf->head < total) {
		outbuf->memory = realloc(outbuf->memory, outbuf->size + total);
		outbuf->size += total;
	}

	for (i=0; i<total; i++) {
		outbuf->memory[outbuf->head] = buf[i];
		outbuf->head += 1;
	}

	return total;
}

