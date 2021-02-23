#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

 struct MemoryString {
	 char *memory;
	 size_t size;
 } ;

 size_t writedata(void *contents, size_t size, size_t nmemb, void *userp) {
	 size_t realsize = size*nmemb;
	 struct MemoryString *mem = (struct MemoryString *)userp;
	 char *ptr = realloc(mem->memory, mem->size + realsize + 1);
	 if(ptr == NULL) {
		 /* out of memory! */
		 printf("not enough memory");
		 return 0;
	 }
	 mem->memory = ptr;
	 memcpy(&(mem->memory[mem->size]), contents, realsize);
	 mem->size += realsize;
	 mem->memory[mem->size] = 0;
	 return realsize;
 }

int main(int argc, char **argv) {
	char accessToken[100];
	int i;
	struct MemoryString chunk;
	char header[10000];
	struct curl_slist *myslist = NULL;
	char *myurl = "https://freesound.org/apiv2/sounds/213524/";
	char *hstrt = "Authorization: Bearer ";
	 CURL *curl;
	if (argc<2) {
		printf("\nNo access token detected!\n");
		printf("To obtain an access token, copy and paste the following URL into your browser:\n");
		printf("\nhttps://freesound.org/apiv2/oauth2/authorize/?client_id=1k4d2Azct3D650WgIFbh&response_type=code\n");
		printf("\nThen click the Authorize button and the access token will appear on the screen.\n");
		printf("Enter access token now. Copy and paste it and press enter:\n");
		scanf("%s", accessToken);
	} else {
		for (i=0; argv[1][i]!='\0'; i++) {
			accessToken[i] = argv[1][i] ;
		}
	}
	 printf("\nAccess Token Detected: %s\n\n", accessToken);
	 curl = curl_easy_init();	
	 snprintf(header, sizeof(header), "%s%s", hstrt, accessToken);
	 printf("\n\nHEADER: %s\n\n", header);
	 myslist = curl_slist_append(myslist, "Accept: ");
	 myslist = curl_slist_append(myslist, header);
	 if(curl) {
		 CURLcode res;
		 curl_easy_setopt(curl, CURLOPT_HTTPHEADER, myslist);
		 curl_easy_setopt(curl, CURLOPT_URL, myurl);
		 curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		 //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writedata);
		 //curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
                 res = curl_easy_perform(curl);
		 if (res != CURLE_OK) {
			 fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			 }
		 else {
			 printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
		 }
		 

		 curl_easy_cleanup(curl);
	 }
	return 0;
}
