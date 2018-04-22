cc=gcc
flags=-Wall
libs=-lm -lpthread -lgmp
FIXDIR=fixtures/


run: main.out
	./main.out

testrun: test.out
	./test.out

scratchesrun: scratches.out
	./scratches.out


main.out: utils.o point.o main.c
	$(cc) $(flags) $(libs) -o main.out $^

# fixtures/test_is_within_circle.csv is an order-only prerequisite
test.out: utils.o point.o test.c | fixtures/test_is_within_circle.csv
	$(cc) $(flags) $(libs) -o test.out $^

scratches.out: utils.o point.o scratches.c
	$(cc) $(flags) $(libs) -o scratches.out $^

utils.o: utils.h utils.c
	$(cc) $(flags) -c utils.c

point.o: point.h point.c
	$(cc) $(flags) -c point.c

fixtures/test_is_within_circle.csv: fixtures.py
	python3.6 ./fixtures.py


clean: *.o *.out
	rm $^


.PHONY: run testrun scratchesrun clean
