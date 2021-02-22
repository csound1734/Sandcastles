#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

int main(int argc, char **argv) {
	char accessToken[100];
	int i;
	if (argc<2) {
		printf("\nNo access token detected!\n");
		printf("\nEnter access token now:\n");
		scanf("%s", accessToken);
	} else {
		for (i=0; argv[1][i]!=NULL; i++) {
			accessToken[i] = argv[1][i] ;
		}
	}
	printf("\nThe access token is: %s\n", accessToken);
	return 0;
}
