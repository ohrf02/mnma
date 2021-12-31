CFLAGS = -Wall -static

# Should be equivalent to your list of C files, if you don't build selectively
SRC=$(wildcard *.c *cpp *.hpp)

mergeable_heap: $(SRC)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

run: mergeable_heap
	./mergeable_heap
