#include <json-c/json.h>

struct freesound_json {
	int type;
	struct json_object *jsonp;
};

struct freesound_json *parseResponse (char *buffer) {
	struct freesound_json *resultofparse = (struct freesound_json *) malloc (sizeof(int)+sizeof(json_object *));
	struct json_object *json_parsed;
	json_parsed = json_tokener_parse(buffer);
	resultofparse->type = 0;
	resultofparse->jsonp = json_parsed;
	return resultofparse;
}

