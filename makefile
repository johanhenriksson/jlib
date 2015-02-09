
CLIBS=
CC=gcc
CPPFLAGS=
CFLAGS=-g

# library
PROXYOBJS=array.o array_list.o error.o list.o map.o map_node.o string.o jtest.o

# test cases
TESTOBJS=tests/main.o tests/string.o tests/list.o

test: $(PROXYOBJS) $(TESTOBJS)
	$(CC) -o test $(PROXYOBJS) $(TESTOBJS) $(CLIBS)

clean:
	rm -f *.o tests/*.o
	rm -f test
