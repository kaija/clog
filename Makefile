

CFLAGS= -Werror -Wall -DCOLOR_LOG
all: log.o test.o
	$(CC) -o test test.o log.o $(CFLAGS)
clean:
	rm *.o test
