all: test_cat.c ../src/fuzzer.c ../src/create_input.c ../src/config.c ../lib/my_troff.c test_troff.c
	gcc -o cat_test test_cat.c ../src/fuzzer.c ../src/create_input.c ../src/config.c
	gcc -o troff_test test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c
	gcc --coverage -o mytroff ../lib/my_troff.c

test: test_cat.c ../src/fuzzer.c ../src/create_input.c
	gcc -o cat_test test_cat.c ../src/config.c ../src/fuzzer.c ../src/create_input.c

mytroff: ../lib/my_troff.c
	gcc --coverage -o mytroff ../lib/my_troff.c

trof_test: test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c
	gcc -o troff_test test_troff.c ../src/fuzzer.c ../src/create_input.c ../src/config.c

clean:
	rm -rf cat_test tmp.* a.out mytroff troff_test *.gcno *.gcda
