all: proxyFilter 

CLIBS=
CC=gcc
CPPFLAGS=
CFLAGS=-g

PROXYOBJS=array.o array_list.o error.o list.o map.o map_node.o string.o test.o

proxyFilter: $(PROXYOBJS)
	$(CC) -o test $(PROXYOBJS) $(CLIBS)

clean:
	rm -f *.o
	rm -f test
