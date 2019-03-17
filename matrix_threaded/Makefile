#
#GNU Makefile

CC = gcc
CCFLAGS = -Wall -lm
TARGET = main
all:
	$(CC) $(CCFLAGS) -o $(TARGET) src/matrix.c src/benchmarks.c src/main.c

clean:
	@./.scripts/title "Cleaning"
	@rm -f *.o *~ $(TARGET)
