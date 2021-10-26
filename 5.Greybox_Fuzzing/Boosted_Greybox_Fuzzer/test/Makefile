all: test_cat.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../lib/my_troff.c test_troff.c test_gcov.c ../lib/cgi_decoder.c bc_test.c crash_test.c
	gcc -o cat_test test_cat.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../src/sched.c
	gcc -o troff_test test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../src/sched.c
	gcc --coverage -o mytroff ../lib/my_troff.c
	gcc --coverage -o decoder ../lib/cgi_decoder.c
	gcc --coverage -o http_mutation ../lib/http_program.c
	gcc --coverage -o crashme ../lib/crashme.c
	gcc -o gcov_test test_gcov.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../src/sched.c
	gcc -o http_test test_http.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../src/sched.c
	gcc -o bc_test bc_test.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../src/sched.c
	gcc -o crash_test crash_test.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../src/sched.c

test: test_cat.c ../src/fuzzer.c ../src/create_input.c ../src/coverage.c
	gcc -o cat_test test_cat.c ../src/config.c ../src/fuzzer.c ../src/create_input.c ../src/coverage.c

mytroff: ../lib/my_troff.c
	gcc --coverage -o mytroff ../lib/my_troff.c

decoder: ../lib/cgi_decoder.c
	gcc --coverage -o decoder ../lib/cgi_decoder.c

http: ../lib/http_program.c
	gcc --coverage -o http_mutation ../lib/http_program.c

trof_test: test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c
	gcc -o troff_test test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c

gcov_test: test_gcov.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c
	gcc -o gcov_test test_gcov.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c

http_test: test_http.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c
	gcc --coverage -o http_mutation ../lib/http_program.c
	gcc -o http_test test_http.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../src/sched.c

bc: bc_test.c ../src/fuzzer.c ../src/create_input.c ../src/coverage.c ../src/config.c
	gcc -o bc_test bc_test.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../src/sched.c

crash: crash_test.c ../lib/crashme.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/sched.c
	gcc --coverage -o crashme ../lib/crashme.c
	gcc -o crash_test crash_test.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../src/sched.c

json:
	gcc --coverage -o cjson ../lib/CJSON/testCJSON.c ../lib/CJSON/cJSON.c
	gcc -o jtest cjson_test.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../src/sched.c -lm

jin1:
	gcc --coverage -o jin1 ../lib/CJSON/jin1.c ../lib/CJSON/cJSON.c
	gcc -o jin1_test -g jin1_test.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../src/sched.c -lm

seoye:
	gcc --coverage -o seoye ../lib/CJSON/seoye.c ../lib/CJSON/cJSON.c
	gcc -o seoye_test seoye_test.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../src/sched.c -lm

woosam:
	gcc --coverage -o woosam ../lib/CJSON/woosam.c ../lib/CJSON/cJSON.c
	gcc -o woosam_test woosam_test.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../src/sched.c

jyeong:
	gcc --coverage -o jyeong ../lib/CJSON/jyeong.c ../lib/CJSON/cJSON.c
	gcc -o jyeong_test jyeong_test.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../src/coverage.c ../src/mutating.c ../src/sched.c

clean:
	rm -rf woosam jin1 seoye jyeong *_test cjson jtest crash_test crashme bc_test cat_test tmp.* a.out mytroff troff_test *.gcno *.gcda decoder gcov_test *.gcov http_test http_mutation a b result.csv
