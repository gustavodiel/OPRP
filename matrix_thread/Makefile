#
#GNU Makefile

CC = gcc
CCFLAGS = -Wall -lptrhead
LDFLAGS =
TARGET = main

%.o: %.c
	@$(CC) $(CCFLAGS) -c $<

%: %.o
	@$(CC) $(LDFLAGS) $^ -o $@

test: $(TARGET)
	@clear
	@./.scripts/title "Running"
	@./$(TARGET) 3 3

# Dependencias

main: matrix.o main.c
matrix.o: matrix.c matrix.h
matrix_thread.o: matrix_thread.c matrix_thread.h

clean:
	@./.scripts/title "Cleaning"
	@rm -f *.o *~ $(TARGET)
