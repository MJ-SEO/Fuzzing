all: test_cat.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../lib/my_troff.c test_troff.c test_gcov.c ../lib/cgi_decoder.c ../lib/http_test.c
	gcc -o cat_test test_cat.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c
	gcc -o troff_test test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c
	gcc --coverage -o mytroff ../lib/my_troff.c
	gcc --coverage -o decoder ../lib/cgi_decoder.c
	gcc --coverage -o http_mutation ../lib/http_program.c
	gcc -o gcov_test test_gcov.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c
	gcc -o http_test test_http.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c

test: test_cat.c ../src/fuzzer.c ../src/create_input.c ../src/coverage.c
	gcc -o cat_test test_cat.c ../src/config.c ../src/fuzzer.c ../src/create_input.c ../src/coverage.c

mytroff: ../lib/my_troff.c
	gcc --coverage -o mytroff ../lib/my_troff.c

decoder: ../lib/cgi_decoder.c
	gcc --coverage -o decoder ../lib/cgi_decoder.c

http: ../lib/http_program.c
	gcc -o http_mutation ../lib/http_program.c

trof_test: test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c
	gcc -o troff_test test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c

gcov_test: test_gcov.c ../src/fuzzer.c ../src/create_input.c ../src/config.c .../src/coverage.c
	gcc -o gcov_test test_gcov.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c

http_test: test_http.c ../src/fuzzer.c ../src/create_input.c ../src/config.c
	gcc -o http_test test_http.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c

clean:
	rm -rf cat_test tmp.* a.out mytroff troff_test *.gcno *.gcda decoder gcov_test *.gcov http_test http_mutation a t