all: mutating_test.c ../src/mutating.c ../src/http_program.c http_test.c url_test.c multiple_test.c
	gcc -o mutate_test mutating_test.c ../src/mutating.c
	gcc -o http_test http_test.c ../src/http_program.c
	gcc -o url_test url_test.c ../src/http_program.c ../src/mutating.c
	gcc -o multiple_test multiple_test.c ../src/http_program.c ../src/mutating.c

mutate: mutating_test.c ../src/mutating.c
	gcc -o mutate_test mutating_test.c ../src/mutating.c

http: http_test.c ../src/http_program.c
	gcc -o http_test http_test.c ../src/http_program.c

url: url_test.c ../src/mutating.c ../src/http_program.c
	gcc -o url_test url_test.c ../src/http_program.c ../src/mutating.c

multiple: mutating_test.c ../src/http_program.c ../src/mutating.c
	gcc -o multiple_test multiple_test.c ../src/http_program.c ../src/mutating.c

clean:
	rm -rf mutate_test a.out http_test url_test multiple_test

