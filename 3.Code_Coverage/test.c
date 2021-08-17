#include "cgi_decoder.c"
#include <assert.h>

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

void
whitebox_testing(){

}

int main(){
	testing();
	
	blackbox_testing();

	printf("%s\n",	cgi_decode("a+b"));
}

