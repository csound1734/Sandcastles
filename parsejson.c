#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json.h>

struct freesound_json {
	int type;
	struct json_object *jsonp;
};

struct freesound_json *parseResponse (char *buffer) {
	struct freesound_json *resultofparse;
	struct json_object *json_parsed;
	json_parsed = json_object_new_object();
	json_parsed = json_tokener_parse(buffer);
	const char *result = json_object_to_json_string_ext(json_parsed, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY);
	printf("\n\nRESUT PARSED:\n\n%s\n\n", result);
	//resultofparse->type = 0;
	//resultofparse->jsonp = json_parsed;
	json_object_put(json_parsed);
	return resultofparse;
}

