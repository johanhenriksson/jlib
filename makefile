
CLIBS=
CC=gcc
CPPFLAGS=
CFLAGS=-g

PROXYOBJS=array.o array_list.o error.o list.o map.o map_node.o string.o jtest.o
TESTOBJS=tests/main.o tests/string.o

test: $(PROXYOBJS) $(TESTOBJS)
	$(CC) -o test $(PROXYOBJS) $(TESTOBJS) $(CLIBS)

clean:
	rm -f *.o
	rm -f test
