all: blackbox.c whitebox.c decoder.c ../src/make_gcov.c ../src/my_decoder.c ../src/cgi_decoder.c ../src/read_gcov.c
	gcc -o blackbox blackbox.c ../src/my_decoder.c
	gcc -o decoder decoder.c ../src/cgi_decoder.c
	gcc -o whitebox whitebox.c ../src/make_gcov.c ../src/read_gcov.c

black: blackbox.c ../src/my_decoder.c
	gcc -o blackbox blackbox.c ../src/my_decoder.c

decoder: decoder.c ../src/cgi_decoder.c
	gcc -o decoder decoder.c ../src/cgi_decoder.c

white: whitebox.c ../src/make_gcov.c ../src/read_gcov.c
	gcc -o whitebox whitebox.c ../src/make_gcov.c ../src/read_gcov.c

clean:
	rm -rf blackbox whitebox a.out *.gcda *.gcno *.gcov cgi_decode decoder
