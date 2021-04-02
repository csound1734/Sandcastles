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

