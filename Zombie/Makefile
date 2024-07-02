all: exe

exe: hw_song_jun.o zombie_song.o
\tg++ -o exe hw_song_jun.o zombie_song.o

hw_song_jun.o: hw_song_jun.cpp linkedlist_song.hpp zombie_song.h
\tg++ -c hw_song_jun.cpp

zombie_song.o: zombie_song.cpp zombie_song.h
\tg++ -c zombie_song.cpp

clean:
\trm -f *.o exe
