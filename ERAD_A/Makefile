FLAGS=-O3 -Wall -fopenmp
RM=rm -f
CC=gcc

EXEC=nbody

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) $(EXEC).c -o $(EXEC) -lm

clean:
	$(RM) $(EXEC).o $(EXEC)
