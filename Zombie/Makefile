OBJS = hw_Yeo_Hyeonjin.o zombie_Yeo.o
EXE = exe
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAG = -Wall $(DEBUG)

$(EXE): $(OBJS)
	$(CC) $(LFLAG) $(OBJS) -o $(EXE)

hw_Yeo_Hyeonjin.o: linkedlist_Yeo.hpp zombie_Yeo.h
	$(CC) $(CFLAGS) hw_Yeo_Hyeonjin.cpp

zombie_Yeo.o: zombie_Yeo.h
	$(CC) $(CFLAGS) zombie_Yeo.cpp

clean:
	rm *.o $(EXE) -v
