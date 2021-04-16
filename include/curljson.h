#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

//#include "jsmn.h"


struct MemoryString
{
	char *memory;
	size_t size;
	size_t head;
};

/*Data-writing curl callback function, for receiving the data sent by server*/
/* Related to CURLOPT_WRITEFUNCTION */
size_t string_callback(void *buf, size_t size, size_t nmemb, void *userp);
size_t sndfil_callback(void *buf, size_t size, size_t nmemb, void *userp);

/*Do curl when receiving JSON*/
char *receiveJson(char *url, struct curl_slist *header, char *js);

/*Do curl when receiving a soundfile*/
FILE *receiveFile(char *url, struct curl_slist *header);
