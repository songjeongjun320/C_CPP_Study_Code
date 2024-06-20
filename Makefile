# Makefile example
OBJS = .o files that need to be made (l .o per .cpp file)
EXE = exe
CC = g++/gcc (g++ for c++, gcc for c)
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAG = -Wall $(DEBUG)

$(EXE): $(OBJS)
	$(CC) $(LFLAG) $(OBJS) -o $(EXE)

main.o: .h files that main depends on (what ever you #include "something.h" NOT #include <something>)
	$(CC) $(CFLAGS) main.cpp

obj1.o: .h files that obj1 depends on (what ever you #include " " NOT #include < >)
	$(CC) $(CFLAGS) obj1.cpp

obj2.o: .h files that obj2 depends on
	$(CC) $(CFLAGS) obj2.cpp

obj3.o: .h files that obj3 depends on
	$(CC) $(CFLAGS) obj3.cpp

and so on for all your objects

called with "make clean", removes all .o files and the xecutable while giving output on what was removed
clean:
	rm *.o $(EXE) -v

