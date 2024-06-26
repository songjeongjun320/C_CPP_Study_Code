exe: geometry.o circle_test.o
	g++ -g -Wall geometry.o circle_test.o -o exe
	
geometry.o: geometry.h
	g++ -g -Wall -c geometry.cpp

circle_test.o: geometry.h
	g++ -g -Wall -c circle_test.cpp

clean:
	rm *.o exe -v