#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

/*Useful structure for keeping track of buffers.*/
 struct MemoryString {
	 char *memory;
	 size_t size;
 } ;

/*libcurl header callback. Set CURLOPT_HEADERFUNCTION to this.
 * Allows main() to access the header as a string after writing the string. */
size_t header_callback(char *, size_t, size_t, void *);

/*libcurl data write callback. Set CURLOPT_WRITEFUNCTION to this.
 * This function writes to disk whenever curl gets data to write.*/
size_t write_data(void *, size_t, size_t, void *);

/*generic procedure that fills the buffer (first argument) with a code either
 * provided via argv[1] (i.e. a command-line option input at execution) or, failing
 * that, interrupts runtime to ask the user for the missing code (stdin).
 * The code can be an access token, an authorization code, a refresh token, or anything
 * else. The final argument lets the code be named so that the prompts are explanatory.*/
void getCode(char *, int, char **, const char *);

/* Ask the user for the number of a sound on freesound.org
 * The address pointed to by argument will be filled with the number the user enters.*/
void scanfSoundN(int *);

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
