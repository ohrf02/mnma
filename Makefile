CFLAGS = -Wall

TARGET = mergeable_heap

SRC=$(wildcard *.c *cpp *.hpp)

clean:
	-rm -v $(TARGET) *.gch

$(TARGET): $(SRC)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

run: clean $(TARGET)
	./$(TARGET)
