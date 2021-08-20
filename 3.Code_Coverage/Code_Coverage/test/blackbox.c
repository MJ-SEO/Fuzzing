#include "../include/my_decoder.h"

#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>

void
testing(){
	char* buf = cgi_decode("Hello%2c+World%21");
	printf("%s\n", buf);
}

void
blackbox_testing(){
	assert(strcmp(cgi_decode("+")," ") == 0);
	assert(strcmp(cgi_decode("%20"), " ") == 0);
	assert(strcmp(cgi_decode("abc"), "abc") == 0);

	assert((cgi_decode("%?a")) == NULL);
}

int main(){
	testing();

	blackbox_testing();
}

