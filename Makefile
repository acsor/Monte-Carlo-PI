cc=gcc
flags=-Wall


run: main
	./main

runtests: test
	./test


main: main.c
	$(cc) $(flags) -o main $?

test: test.c
	$(cc) $(flags) -o test $?

clean:
	rm -r main test
