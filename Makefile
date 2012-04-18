CPPFLAGS=-g

all: main.o funcs.o stack.o trees.o
	g++ $(CPPFLAGS) -o a.out main.o funcs.o stack.o trees.o

main.o: header.h main.cpp
	g++ $(CPPFLAGS) -c main.cpp

funcs.o: header.h funcs.cpp
	g++ $(CPPFLAGS) -c funcs.cpp

stack.o: header.h stack.cpp
	g++ $(CPPFLAGS) -c stack.cpp

trees.o: header.h trees.cpp
	g++ $(CPPFLAGS) -c trees.cpp

clean:
	rm -f *.o core p

