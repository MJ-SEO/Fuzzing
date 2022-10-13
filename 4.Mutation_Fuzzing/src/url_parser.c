#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

int main(){
	//	regex_t http_state;
	char* uri = "http://www.google.com/search?q=fuzzing#frag";
	char schema[7];
	char netloc[50];
	char path[200];
	char params[30];
	char query[30];
	char fragment[30];

	memset(schema, 0, sizeof(schema));
	memset(netloc, 0, sizeof(netloc));
	memset(path, 0, sizeof(path));
	memset(params, 0, sizeof(params));
	memset(query, 0, sizeof(query));
	memset(fragment, 0, sizeof(fragment));

	int uri_scan_status = sscanf(uri, "%10[^:]%*[^a-z|^A-Z]%50[^/]/%200[^?]?%30[^#]#%s", schema, netloc, path, query, fragment);

	printf("[info] URI scan status : %d\n", uri_scan_status);
		
	printf("[info] Schemas : '%s'\n", schema);
	printf("[info] Netloc: '%s'\n", netloc);
	printf("[info] Path : '%s'\n", path);
	printf("[info] Params : '%s'\n", params);
	printf("[info] Query : '%s'\n", query);
	printf("[info] Fragment : '%s'\n", fragment);

	return 0;    
}
