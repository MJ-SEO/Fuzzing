all: bugs_test.c bugs.c ../src/fuzzer.c 
	gcc -o bugs bugs_test.c bugs.c ../src/fuzzer.c

bugs: bugs_test.c bugs.c ../src/fuzzer.c
	gcc -o bugs bugs_test.c bugs.c ../src/fuzzer.c

clean:
	rm -rf bugs
