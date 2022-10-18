all: test_cat.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../lib/my_troff.c test_troff.c test_cgi.c ../lib/cgi_decoder.c bc_test.c
	gcc -o cat_test test_cat.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c
	gcc -o troff_test test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c
	gcc --coverage -o mytroff ../lib/my_troff.c
	gcc --coverage -o decoder ../lib/cgi_decoder.c
	gcc --coverage -o http_mutation ../lib/http_program.c
	gcc -o cgi_test test_cgi.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c
	gcc -o http_test test_http.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c
	gcc -o bc_test bc_test.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c

test: test_cat.c ../src/fuzzer.c ../src/create_input.c ../src/coverage.c
	gcc -o cat_test test_cat.c ../src/config.c ../src/fuzzer.c ../src/create_input.c ../src/coverage.c

mytroff: ../lib/my_troff.c
	gcc --coverage -o mytroff ../lib/my_troff.c

decoder: ../lib/cgi_decoder.c
	gcc --coverage -o decoder ../lib/cgi_decoder.c

http: ../lib/http_program.c
	gcc --coverage -o http_mutation ../lib/http_program.c

troff_test: test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c
	gcc -o troff_test test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c

cgi_test: test_cgi.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c
	gcc -o cgi_test test_gcov.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c

http_test: test_http.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c
	gcc --coverage -o http_mutation ../lib/http_program.c
	gcc -o http_test test_http.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c

bc: bc_test.c ../src/fuzzer.c ../src/create_input.c ../src/coverage.c ../src/config.c
	gcc -o bc_test bc_test.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c

clean:
	rm -rf bc_test cat_test tmp.* a.out mytroff troff_test *.gcno *.gcda decoder cgi_test *.gcov http_test http_mutation a b
