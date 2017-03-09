all: tp1

tp1: main.o structures.o fonctions.o
	gcc -Wall -Wextra –ansi -pedantic -o tp1 main.o structures.o fonctions.o

main.o: main.c structures.h fonctions.h
	gcc -Wall -Wextra –ansi -pedantic -o main.o -c main.c

fonctions.o: fonctions.c structures.h
	gcc -Wall -Wextra –ansi -pedantic -o fonctions.o -c fonctions.c

structures.o: structures.c
	gcc -Wall -Wextra –ansi -pedantic -o structures.o -c structures.c

clean:
	rm -rf *.o

mrproper: clean
rm -rf tp1
