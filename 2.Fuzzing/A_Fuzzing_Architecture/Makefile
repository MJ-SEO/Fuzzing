all: test_cat.c fuzzer.c create_input.c config.c my_troff.c test_troff.c
	gcc -o cat_test test_cat.c fuzzer.c create_input.c config.c
	gcc -o mytroff my_troff.c
	gcc -o troff_test test_troff.c fuzzer.c create_input.c config.c

test: test_cat.c fuzzer.c create_input.c
	gcc -o cat_test test_cat.c config.c fuzzer.c create_input.c

mytroff: my_troff.c
	gcc -o mytroff my_troff.c

trof_test:
	gcc -o troff_test test_troff.c fuzzer.c create_input.c config.c

clean:
	rm -rf cat_test tmp.* a.out mytroff troff_test
