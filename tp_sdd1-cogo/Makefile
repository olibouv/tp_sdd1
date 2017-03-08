all: tp1

tp1: main.o structures.o fonctions.o
	gcc -o tp1 main.o structures.o fonctions.o

main.o: main.c structures.h fonctions.h
	gcc -o main.o -c main.c

fonctions.o: fonctions.c structures.h
	gcc -o fonctions.o -c fonctions.c

structures.o: structures.c
	gcc -o structures.o -c structures.c

clean:
	rm -rf *.o

mrproper: clean
	rm -rf tp1
