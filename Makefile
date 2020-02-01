
Go: main.o plateau.o jeu.o fonctions.o IA.o
	gcc -Wall -o Go main.o plateau.o jeu.o fonctions.o IA.o

main.o: main.c plateau.c plateau.h jeu.c fonctions.c IA.c
	gcc -Wall -o main.o -c main.c

plateau.o: plateau.c plateau.h
	gcc -Wall -o plateau.o -c plateau.c

jeu.o: jeu.c plateau.h
	gcc -Wall -o jeu.o -c jeu.c

fonctions.o: fonctions.c plateau.h
	gcc -Wall -o fonctions.o -c fonctions.c

IA.o: IA.c plateau.h
	gcc -Wall -o IA.o -c IA.c

clean:
	rm -rf *.o
