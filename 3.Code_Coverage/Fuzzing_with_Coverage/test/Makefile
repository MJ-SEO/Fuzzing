all: test_cat.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../lib/my_troff.c test_troff.c test_cgi.c ../lib/cgi_decoder.c
	gcc -o cat_test test_cat.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c
	gcc -o troff_test test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c
	gcc --coverage -o mytroff ../lib/my_troff.c
	gcc --coverage -o decoder ../lib/cgi_decoder.c
	gcc -o test_cgi test_cgi.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c

test: test_cat.c ../src/fuzzer.c ../src/create_input.c ../src/coverage.c
	gcc -o cat_test test_cat.c ../src/config.c ../src/fuzzer.c ../src/create_input.c ../src/coverage.c

mytroff: ../lib/my_troff.c
	gcc --coverage -o mytroff ../lib/my_troff.c

decoder: ../lib/cgi_decoder.c
	gcc --coverage -o decoder ../lib/cgi_decoder.c

trof_test: test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c
	gcc -o troff_test test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c

test_cgi: test_cgi.c ../src/fuzzer.c ../src/create_input.c ../src/config.c .../src/coverage.c
	gcc -o test_cgi test_cgi.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c

clean:
	rm -rf cat_test tmp.* a.out mytroff troff_test *.gcno *.gcda decoder test_cgi *.gcov
