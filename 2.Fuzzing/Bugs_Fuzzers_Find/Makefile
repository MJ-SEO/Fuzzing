all: bugs_test.c bugs.c ../fuzzer.c 
	gcc -o bugs bugs_test.c bugs.c ../fuzzer.c

bugs: bugs_test.c bugs.c ../fuzzer.c
	gcc -o bugs bugs_test.c bugs.c ../fuzzer.c

clean:
	rm -rf bugs
