all: test_cat.c fuzzer.c create_input.c
	gcc -o test test_cat.c fuzzer.c create_input.c

test: test_cat.c fuzzer.c create_input.c
	gcc -o test test_cat.c fuzzer.c create_input.c

clean:
	rm -rf test
