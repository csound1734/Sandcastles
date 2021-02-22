#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <curl/curl.h>

int main(int argc, char **argv) {
	char accessToken[100];
	int i;
	if (argc<2) {
		printf("\nNo access token detected!\n");
		printf("To obtain an access token, copy and paste the following URL into your browser:\n");
		printf("https://freesound.org/apiv2/oauth2/authorize/?client_id=1k4d2Azct3D650WgIFbh&response_type=code\n");
		printf("Then click the Authorize button and the access token will appear on the screen.\n");
		printf("\nEnter access token now:\n");
		scanf("%s", accessToken);
	} else {
		for (i=0; argv[1][i]!='\0'; i++) {
			accessToken[i] = argv[1][i] ;
		}
	}
	printf("\nThe access token is: %s\n", accessToken);
	return 0;
}
