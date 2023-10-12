all: item.o main2.o
	gcc item.o main2.o -o main2 -std=c99 -Wall

item.o:
	gcc -c item.c -o item.o
	 
main2.o:
	gcc -c main2.c -o main2.o
	 
clean:
	rm *.o main2

run:
	./main2

