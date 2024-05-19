#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

// Colors

#define clrscr() printf("\033[H\033[2J")
#define couleur(param) printf("\033[%sm",param)



//Manager

Time createtime();
Row createrow(char category, int acc);
Room createroom();
Show create_Show();



//Client

void printTime(Time T);
void Display_Shows(Show* List_Of_Shows, int Size_Of_List);
void User_Reserve_Seats(Show* List_Of_Planned_Shows, int Size_Of_List_Of_Planned_Shows);
void Reserve_Seats(Room* Room_To_Modify, int Chosen_Row, int Chosen_Seat);



#endif