TARGETS = interpreter example sieve driver driverCov

OBJECTS = \
          interpreter.o \
          Expr.o \
          example.o \
          Binary.o \
          BinaryCov.o \
          driver.o \
          sieve.o

all: $(TARGETS)

CC = gcc
CFLAGS = -Wall -std=c99 -g
COVER_FLAGS = -ftest-coverage -fprofile-arcs

# dependencies, listing header files each object is dependent
# on (you can auto-generate this, by the way).
example.o: Binary.h
Binary.o: Binary.h
driver.o: Binary.h
sieve.o: Binary.h
Expr.o: Binary.h Expr.h
interpreter.o: Binary.h Expr.h 

# rules to actually build the targets.

interpreter: interpreter.o Binary.o Expr.o
	$(CC) $(CFLAGS) $^ -o $@

example: example.o Binary.o
	$(CC) $(CFLAGS) $^ -o $@

sieve: sieve.o Binary.o
	$(CC) $(CFLAGS) $^ -o $@

driver: driver.o Binary.o
	$(CC) $(CFLAGS) $^ -o $@

driverCov: driver.o BinaryCov.o
	$(CC) $(CFLAGS) $(COVER_FLAGS) $^ -o $@

BinaryCov.o: Binary.c Binary.h
	$(CC) $(CFLAGS) $(COVER_FLAGS) -c Binary.c -o BinaryCov.o

clean:
	rm -f $(TARGETS)
	rm -f $(OBJECTS)
	rm -f *.gcda *.gcno *.gcov



