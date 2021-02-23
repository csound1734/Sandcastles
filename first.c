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
	char result[10000];
	char accessToken[100];
	int i;
	 struct MemoryString chunk;
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
	 chunk.memory = malloc(1);
	 chunk.size = 0;
	 curl = curl_easy_init();
	 char *myurl = "https://freesound.org/apiv2/oauth2/access_token/";
	 char *mypost = "client_id=1k4d2Azct3D650WgIFbh&client_secret=bgTSKIoy9dgSWhJhJSSgyHhyvBBJuyNewNkjjaBx&grant_type=authorization_code&code=";
	 snprintf(result, sizeof(result), "%s%s", mypost, accessToken);
	 printf("\n\nPOST: %s\n\n", result);
	 if(curl) {
		 CURLcode res;
		 curl_easy_setopt(curl, CURLOPT_URL, myurl);
		 //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writedata);
		 //curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		 curl_easy_setopt(curl, CURLOPT_POSTFIELDS, result);
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
	return 0;
}
