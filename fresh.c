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

size_t header_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
	size_t numbytes = size * nmemb;
        printf("%.*s\n", numbytes, ptr);
        return numbytes;
}

int main(int argc, char **argv) {
	char result[10000];
	char refreshToken[100];
	char headerbuf[10000];
	int i;
	 struct MemoryString chunk;
	 struct MemoryString headchk;
	 headchk.memory = (char *)malloc(10000*sizeof(char));
	 headchk.size = 10000*sizeof(char);
	 CURL *curl;
	if (argc<2) {
		printf("\nNo refresh token detected!\n");
		printf("To obtain an refresh token, use program\n");
		printf("Enter refresh token now. Copy and paste it and press enter:\n");
		scanf("%s", refreshToken);
	} else {
		for (i=0; argv[1][i]!='\0'; i++) {
			refreshToken[i] = argv[1][i] ;
		}
	}
	 printf("\nRefresh Token Detected: %s\n\n", refreshToken);
	 chunk.memory = malloc(1);
	 chunk.size = 0;
	 curl = curl_easy_init();
	 char *myurl = "https://freesound.org/apiv2/oauth2/access_token/";
	 char *mypost = "client_id=1k4d2Azct3D650WgIFbh&client_secret=bgTSKIoy9dgSWhJhJSSgyHhyvBBJuyNewNkjjaBx&grant_type=refresh_token&refresh_token=";
	 snprintf(result, sizeof(result), "%s%s", mypost, refreshToken);
	 printf("\n\nPOST: %s\n\n", result);
	 if(curl) {
		 CURLcode res;
		 curl_easy_setopt(curl, CURLOPT_URL, myurl);
		 //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writedata);
		 //curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		 curl_easy_setopt(curl, CURLOPT_POSTFIELDS, result);
		 curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
		 curl_easy_setopt(curl, CURLOPT_HEADERDATA, headerbuf);
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
