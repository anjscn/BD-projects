CC = gcc -Wall -g
EXEC = escalona
SRC = $(wildcard *.c)
OBJS = $(SRC: .c=.o) *.h

.PHONY: clean purge all

%.o %.c %.h:
	$(CC) -c $(CFLAGS) $<

$(EXEC): $(OBJS)
	@$(CC) $^ -o $@

clean: 
	@rm -f *.o *~

purge: clean
	@rm -f $(EXEC)
	@rm -f *.o escalona
