#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

struct MemoryString {
	char *memory;
	size_t size;
};

struct freesound_json {
        int type;
        struct json_object *jsonp;
}; 

/* Write header callback. */
size_t header_callback(char *, size_t, size_t, void *);

/* Write data callback */
int write_data(void *, size_t, size_t, void *);

void getCode(char *, int, char **, const char *);

struct freesound_json *parseResponse (char *);

int main(int argc, char **argv) {
         char result[10000];
         struct MemoryString chunk;
	 FILE *fp;
         char refreshToken[500];
         CURL *curl;
         const char myurl[100] = "https://freesound.org/apiv2/oauth2/access_token/";
         const char mypost[200] = "client_id=1k4d2Azct3D650WgIFbh&client_secret=bgTSKIoy9dgSWhJhJSSgyHhyvBBJuyNewNkjjaBx&grant_type=refresh_token&refresh_token=";

         getCode(refreshToken, argc, argv, "refresh token");
         snprintf(result, sizeof(result), "%s%s", mypost, refreshToken);
         //printf("\n\nPOST: %s\n\n", result);

	 curl_global_init(CURL_GLOBAL_ALL);
         curl = curl_easy_init();
         if(curl) { 
             fp = fopen(".rightnow-sndcsl", "wb");
	     if (fp) {
                 CURLcode res;
                 curl_easy_setopt(curl, CURLOPT_URL, myurl);
                 curl_easy_setopt(curl, CURLOPT_POSTFIELDS, result);
                 //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                 //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &fp);
                 res = curl_easy_perform(curl);
                 if (res != CURLE_OK) {
                         fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                         }
                 else {
                         printf(" A OK \n");
			 //printf("\nDirect: \n%s\n\n", headchk.memory);
                         //struct freesound_json *parsed_header = parseResponse(headchk.memory);
                 }
                 fclose(fp);
                 curl_easy_cleanup(curl);
		 curl_global_cleanup();
         }
        return 0;
}
