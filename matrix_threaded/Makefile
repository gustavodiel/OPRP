#
#GNU Makefile

CC = gcc
CCFLAGS = -Wall -lm -lpthread -O3
TARGET = main
all:
	$(CC) $(CCFLAGS) -o $(TARGET) src/matrix.c src/threaded_matrix.c src/benchmarks.c src/main.c

clean:
	@./.scripts/title "Cleaning"
	@rm -f *.o *~ $(TARGET)
