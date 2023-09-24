CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lpthread
all: echo
csapp.o: csapp.c csapp.h
	$(CC) $(CFLAGS) -c csapp.c
echo.o: echo.c csapp.h
	$(CC) $(CFLAGS) -c echo.c
echo: echo.o echoserveri.c echoclient.c csapp.o
	$(CC) $(CFLAGS) echoclient.c csapp.o -o echoclient $(LDFLAGS)
	$(CC) $(CFLAGS) echo.o echoserveri.c csapp.o -o echoserveri $(LDFLAGS)
clean:
	rm -f *~ *.o echo echoclient echoserveri