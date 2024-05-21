
all : exec

Partie_Festivalier.o : Partie_Festivalier.c Fonctions.h
		gcc -c Partie_Festivalier.c -o Partie_Festivalier.o

Partie_Manager.o : Partie_Manager.c Fonctions.h
		gcc -c Partie_Manager.c -o Partie_Manager.o

Main.o : Main.c Fonctions.h
		gcc -c Main.c -o Main.o

exec : Main.o Partie_Festivalier.o Partie_Manager.o
		gcc Partie_Festivalier.o Partie_Manager.o Main.o -o exec
