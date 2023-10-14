all: skiplist.o item.o main.o
	gcc skiplist.o item.o main.o -o main -std=c99 -Wall

skiplist.o:
	gcc -c skiplist.c -o skiplist.o
	
item.o:
	gcc -c item.c -o item.o
	 
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o main

run:
	./main

