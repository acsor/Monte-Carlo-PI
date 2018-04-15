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


main: utils point main.c 
	$(cc) $(flags) $(libs) -o main $?

test: utils point test.c 
	$(cc) $(flags) $(libs) -o test $?

scratches: utils scratches.c
	$(cc) $(flags) $(libs) -o scratches $?

utils: utils.h utils.c
	$(cc) $(flags) -c -o utils utils.c

point: point.h point.c
	$(cc) $(flags) -c -o point point.c


clean: main test utils scratches point
	rm -r $?
