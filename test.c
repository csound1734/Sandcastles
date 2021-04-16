#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#include "curljson.h"

char url[] = "https://freesound.org/apiv2/search/text/?query=piano&token=bgTSKIoy9dgSWhJhJSSgyHhyvBBJuyNewNkjjaBx";

int main(int argc, char **argv) {
	char body[] = "dummy";
	struct curl_slist *header = curl_slist_append(NULL, "Accept: application/json");
	char *res = receiveJson(url, header, body);
	printf("Hello world!\n");
	printf("\n%s\n", res);
	return 0;
}
