#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct freesound_json {
        int type;
        struct json_object *jsonp;
}; 

size_t header_callback(char *, size_t, size_t, void *);

void getCode(char *, int, char **, const char *);

struct freesound_json *parseResponse (char *);

int main(int argc, char **argv) {
         char result[10000];
         struct MemoryString chunk;
         struct MemoryString headchk;
         char refreshToken[500];
         CURL *curl;
         const char myurl[100] = "https://freesound.org/apiv2/oauth2/access_token/";
         const char mypost[200] = "client_id=1k4d2Azct3D650WgIFbh&client_secret=bgTSKIoy9dgSWhJhJSSgyHhyvBBJuyNewNkjjaBx&grant_type=refresh_token&refresh_token=";

         headchk.memory = (char *)malloc(10000*sizeof(char));
         headchk.size = 0;

         getCode(refreshToken, argc, argv, "refresh token");
         snprintf(result, sizeof(result), "%s%s", mypost, refreshToken);
         //printf("\n\nPOST: %s\n\n", result);

         curl = curl_easy_init();
         if(curl) { 
                 FILE *houtf = fopen(".rightnow-sndcsl", "w");
                 CURLcode res;
                 curl_easy_setopt(curl, CURLOPT_URL, myurl);
                 curl_easy_setopt(curl, CURLOPT_POSTFIELDS, result);
                 curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
                 curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headchk);
                 res = curl_easy_perform(curl);
                 if (res != CURLE_OK) {
                         fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                         }
                 else {
                         printf("%lu bytes retrieved\n", (unsigned long)headchk.size);
                         struct freesound_json *parsed_header = parseResponse(headchk.memory);
                 }
                 fclose(houtf);
                 curl_easy_cleanup(curl);
         }
        return 0;
}
