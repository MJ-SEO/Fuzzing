#include "../include/make_gcov.h"
#include "../include/read_gcov.h"

int main(){
	make_gcov("decoder.c", "cgi_decode", "Send+mail+to+me%40fuzzingbook.org");

	read_gcov_coverage("cgi_decoder.c");
	
	return 0;
}

