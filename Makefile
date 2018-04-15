cc=gcc
flags=-Wall
libs=-lm -lpthread -lgmp


run: main
	./main

runtests: test
	./test

scratchesrun: scratches
	./scratches

main: main.c utils
	$(cc) $(flags) -o main $?


test: utils point test.c 
	$(cc) $(flags) $(libs) -o test $?

scratches: utils scratches.c
	$(cc) $(flags) $(libs) -o scratches $?

utils: utils.h utils.c
	$(cc) $(flags) -c -o utils utils.c


clean: main test utils scratches point
	rm -r $?
