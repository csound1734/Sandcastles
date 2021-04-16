#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "misc.h"

int main(int argc, char **argv) {
	char result[10000];
	char authCode[100];
	int i;
	
	printf("fist (Sandcastles)\n\n(If you dont have an authorization code yet, visit:\nhttps://freesound.org/apiv2/oauth2/authorize/?client_id=1k4d2Azct3D650WgIFbh&response_type=code\n\nSign into your freesound account, then click Authorize. Copy the authorization code you see on the next screen.)\n");
	CURL *curl;
	getCode(authCode, argc, argv, "authorization code");
	curl = curl_easy_init();
	char *myurl = "https://freesound.org/apiv2/oauth2/access_token/";
	char *mypost = "client_id=1k4d2Azct3D650WgIFbh&client_secret=bgTSKIoy9dgSWhJhJSSgyHhyvBBJuyNewNkjjaBx&grant_type=authorization_code&code=";
	snprintf(result, sizeof(result), "%s%s", mypost, authCode);
	//printf("\n\nPOST: %s\n\n", result);
	if(curl) {
		CURLcode res;
		curl_easy_setopt(curl, CURLOPT_URL, myurl);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, result);
                res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			}
		else {
			printf("%lu bytes retrieved\n", 0);
		}
		curl_easy_cleanup(curl);
	}
	return 0;
}
