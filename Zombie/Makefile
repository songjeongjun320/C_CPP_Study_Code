all: exe

exe: hw_<lastname>_<firstname>.o
    g++ -o exe hw_<lastname>_<firstname>.o

hw_<lastname>_<firstname>.o: hw_<lastname>_<firstname>.cpp linkedlist_<lastname>.hpp zombie_<lastname>.h
    g++ -c hw_<lastname>_<firstname>.cpp

clean:
    rm -f *.o exe
