all: test_cat.c fuzzer.c create_input.c config.c
	gcc -o cat_test test_cat.c fuzzer.c create_input.c config.c

test: test_cat.c fuzzer.c create_input.c
	gcc -o cat_test test_cat.c config.c fuzzer.c create_input.c

clean:
	rm -rf cat_test tmp.* a.out
