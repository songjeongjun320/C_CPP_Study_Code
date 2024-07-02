all: exe

exe: hw_<lastname>_<firstname>.o zombie_<lastname>.o
    g++ -o exe hw_<lastname>_<firstname>.o zombie_<lastname>.o

hw_<lastname>_<firstname>.o: hw_<lastname>_<firstname>.cpp linkedlist_<lastname>.hpp zombie_<lastname>.h
    g++ -c hw_<lastname>_<firstname>.cpp

zombie_<lastname>.o: zombie_<lastname>.cpp zombie_<lastname>.h
    g++ -c zombie_<lastname>.cpp

clean:
    rm -f *.o exe
