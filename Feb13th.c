
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

/*
 *
	 char myurl[100] = "https://freesound.org/apiv2/oauth2/authorize/?client_id=1k4d2Azct3D650WgIFbh&response_type=code";
	 */
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





 int main (int argc, char **argv) {
	 printf("\n%s\n\n", argv[1]);
	 struct MemoryString chunk;
	 chunk.memory = malloc(1);
	 chunk.size = 0;
         CURL *curl = curl_easy_init();
	 char *myurl = "https://freesound.org/apiv2/oauth2/access_token/";
	 char *mypost = "client_id=1k4d2Azct3D650WgIFbh&client_secret=bgTSKIoy9dgSWhJhJSSgyHhyvBBJuyNewNkjjaBx&grant_type=authorization_code&code=" ;
	 mypost = strcat(mypost, argv[1]);
	 printf("\n\nPOST: %s\n\n", mypost);
	 char resul[10000] = "";
	 /*
	 if(curl) {
		 CURLcode res;
		 curl_easy_setopt(curl, CURLOPT_URL, myurl);
		 curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writedata);
		 curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		 //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, mypost);
                 res = curl_easy_perform(curl);
		 if (res != CURLE_OK) {
			 fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			 }
		 else {
			 printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
		 }
		 

		 curl_easy_cleanup(curl);
		 free(chunk.memory);
	 }
	 */
	 printf("\n\nHello world!\n\n");
	 curl_global_cleanup();
	 return 0;
 }

