TARGET = treeview
CFLAGS = -Wall -I. --std=c++11 -c -O2
LDFLAGS =
CC = g++

all: $(TARGET)

$(TARGET):	tree.o main.o
	$(CC) $(LDFLAGS) tree.o main.o -o $(TARGET)

tree.o:	tree.hpp tree.cpp
	$(CC) $(CFLAGS) tree.cpp

main.o:	tree.hpp main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -f $(TARGET) *.o *.class

class:
	$(CC) $(CFLAGS) -fdump-class-hierarchy tree.cpp
