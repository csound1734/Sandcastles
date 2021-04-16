#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "misc.h"

size_t header_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
	size_t numbytes = size * nmemb;
	struct MemoryString *userp = (struct MemoryString *)userdata;
	size_t initsize = userp->size;
	int i = 0;
	for (i=0; i<(int)nmemb; i++) {
		*(userp->memory + i + initsize) = *(ptr + i);
		printf("%c", *(userp->memory + i));
		userp->size++;
	}
	printf("%lu", userp->size);
	printf("\n.\n");
        return numbytes;
}

void getCode (char *code, int argc, char **argv, const char *codename) {
	int i;
	if (argc<2) {
		printf("\nNo %s detected!\n", codename);
		printf("Enter %s now. Copy and paste it and press enter:\n", codename);
		scanf("%s", code);
	} else {
		for (i=0; argv[1][i]!='\0'; i++) {
			code[i] = argv[1][i] ;
		}
	}
	 printf("\n%s Detected: %s\n\n", codename, code);
}

size_t write_data(void *contents, size_t size, size_t nmemb, void *stream) {
        size_t written = fwrite(contents, size, nmemb, (FILE *)stream);
        printf("\nin callback function, writing data from curl now\n");
        return written;
}

void scanfSoundN(int *userinput) {
	printf("\n\nNOW PLEASE INPUT THE NUMBER OF A SOUND FROM FREESOUND.ORG ON THE LINE BELOW\n");
        scanf("%d", userinput);
}
