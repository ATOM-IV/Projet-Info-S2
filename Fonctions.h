#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

// Struct

typedef struct {
    int Seat_Number;                // How many seats are there on this row
    int* Seat_Tab;                  // Table containing the seats of the row. 
                                    // The int corresponds to the number of persons on this seat (0, 1 or 2)
    char Category;                  // Category of the Row ("A", "B", "C")
} Row;

typedef struct {
    char* Name;                     // Name of the room
    float* Price_By_Category;       // Table of prices
    int Row_Number;                 // Number of rows in this room
    Row* Rows_Tab;                  // Table containing the rows
    int Pit;                        // 1 if the Room has a pit, 0 otherwise
    int Is_Reserved;                // 1 if the Room is reserved, 0 otherwise
    int Capacity;                   // Max number of people the room can hold
    int Number_Of_Reservations;     // Number of clients' reservations
} Room;

typedef struct {
    int Hour;
    int Minutes;
} Time;

typedef struct  {
    char Show_Name[120];
    Room* Used_Room_Adress;
    Time Starting_Time;
    Time Ending_Time;
    int Number_Of_Reserved_Seats;
} Show;





// Colors

#define clrscr() printf("\033[H\033[2J")
#define couleur(param) printf("\033[%sm",param)



//Manager

Time createtime();
void createrow(Row* Created_Row_Adress, char Row_Category, int Row_Position, int* Exited);
void createroom(Room* Created_Room_Adress, int* Exited);
Show create_Show();



//Client

void printTime(Time T);
void Display_Shows(Show* List_Of_Shows, int Size_Of_List);
void User_Reserve_Seats(Show* List_Of_Planned_Shows, int Size_Of_List_Of_Planned_Shows);
void Reserve_Seats(Room* Room_To_Modify, int Chosen_Row, int Chosen_Seat);

//Main
char* VerifCat(Row Ro);
void printShow(Room R);

#endif
