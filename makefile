MyGlobe:Main.o LinkedList.o HashTable.o Countries.o KeyValuePair.o
	gcc Main.o LinkedList.o HashTable.o Countries.o KeyValuePair.o -o MyGlobe
Main.o: Main.c Defs.h LinkedList.h HashTable.h Countries.h KeyValuePair.h
	gcc -c Main.c
Countries.o: Countries.c Countries.h Defs.h
	gcc -c Countries.c
HashTable.o: HashTable.c HashTable.h Defs.h KeyValuePair.h LinkedList.h
	gcc -c HashTable.c
KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c
LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
clean:
	rm -f *.o
