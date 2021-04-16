#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

 struct MemoryString {
	 char *memory;
	 size_t size;
 } ;

int write_data(void *, size_t, size_t, void *);

void getCode(char *, int, char **, const char *);

void scanfSoundN(int *);


int main(int argc, char **argv) {
	char accessToken[100];
	int i;
	char header[10000];
	struct curl_slist *myslist = NULL;
<<<<<<< HEAD
	char *myurl = "https://freesound.org/apiv2/sounds/561210/download/";
=======
	char *myurl = "https://freesound.org/apiv2/sounds/"; // snprintf(myurl_new, sizeof(myurl_new), "%s%d/download/", myurl, 213524);
	char o_url[10000];
>>>>>>> e42927635ac5fafbaddd4ae6a4c187f063ec62f6
	char *hstrt = "Authorization: Bearer ";
	static const char *filename = "out.wav";
	FILE *file;
	CURL *curl;

	 getCode(accessToken, argc, argv, "Access Token");
	 snprintf(header, sizeof(header), "%s%s", hstrt, accessToken);

	 myslist = curl_slist_append(myslist, "Accept: ");
	 myslist = curl_slist_append(myslist, header);

	 curl_global_init(CURL_GLOBAL_ALL);
	 curl = curl_easy_init();	

	 if(curl) {

		 int down = 213524; //default value just in case
		 scanfSoundN(&down);

		 snprintf(o_url, sizeof(o_url), "%s%d/download/", myurl, down);

		 file = fopen(filename, "wb");
		 if (file) {
		         CURLcode res;
		         curl_easy_setopt(curl, CURLOPT_HTTPHEADER, myslist);
		         curl_easy_setopt(curl, CURLOPT_URL, o_url);
		         curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		         curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
                         res = curl_easy_perform(curl);
		         if (res != CURLE_OK) {
			         fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			         } 
		         curl_easy_cleanup(curl);
			 curl_global_cleanup();
		 } else {
			 printf("\nCannot open file %s!\n\n", filename);
		 }
		 fclose(file);
	 }
	return 0;
}

