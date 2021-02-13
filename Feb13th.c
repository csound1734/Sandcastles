
#include <stdio.h>
#include <curl/curl.h>

 int main () {
         CURL *curl = curl_easy_init();
	 char myurl[100] = "https://google.com";
	 if(curl) {
		 CURLcode res;
		 curl_easy_setopt(curl, CURLOPT_URL, myurl);
                 curl_easy_perform(curl);
		 curl_easy_cleanup(curl);
	 }
	 printf("\n\nHello world!\n\n");
	 return 0;
 }

