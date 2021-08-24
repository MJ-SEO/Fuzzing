#include "../include/http_program.h"

#define DEBUG

url_t
url_parser(char* target_url){
	url_t url;// = (url_t*)malloc(sizeof(url_t) * 1);
	
	url.url_status = sscanf(target_url, "%10[^:]%*[^a-z|^A-Z]%50[^/]%150[^?]?%30[^#]#%s", url.schema, url.netloc, url.path, url.query, url.fragment);

	return url;
}

int 
http_program(char* target_url){
	url_t result = url_parser(target_url);

#ifdef DEBUG
	printf("[info] Schemas : '%s'\n", result.schema);
	printf("[info] Netloc: '%s'\n", result.netloc);
	printf("[info] Path : '%s'\n", result.path);
	printf("[info] Query : '%s'\n", result.query);
	printf("[info] Fragment : '%s'\n", result.fragment);
#endif
	
	if(strstr(result.schema, "http") == NULL && strstr(result.schema, "https") == NULL){
		perror("Schemae must be 'http' or 'https'");
		return 1;
	}

	if(strlen(result.netloc) < 1){
		perror("Host must be non-empty");
		return 2;
	}

	return 0;
}
