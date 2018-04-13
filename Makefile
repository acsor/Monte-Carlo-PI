cc=gcc
flags=-Wall


run: main
	./main

runtests: test
	./test


main: main.c utils
	$(cc) $(flags) -o main $?

test: utils test.c 
	$(cc) $(flags) -o test $?

utils: utils.h utils.c
	$(cc) $(flags) -c -o utils utils.c


clean:
	rm -r main test utils
