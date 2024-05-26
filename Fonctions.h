#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

// Struct

typedef struct {
    int Hour;
    int Minutes;
} Time;

typedef struct {
    int Seat_Number;                // How many seats are there on this row
                                    // The int corresponds to the number of persons on this seat (0, 1 or 2)
    char Category;                  // Category of the Row ("A", "B", "C")
    int* Seat_Tab;                  // Table containing the seats of the row. 
} Row;

typedef struct {
    char* Name;                      // Name of the room
    int Pit;                         // 1 if the Room has a pit, 0 otherwise
    int Row_Number;                  // Number of rows in this room
    int Is_Reserved;                 // 1 if the Room is reserved, 0 otherwise
    int Capacity;                    // Max number of people the room can hold
    int Number_Of_Reservations;      // Number of clients' reservations
    float* Price_By_Category;        // Table of prices
    Row* Rows_Tab;                   // Table containing the rows
} Room;

typedef struct {
    char* Show_Name;
    Time Starting_Time;
    Time Ending_Time;
    Room* Used_Room_Adress;
} Show;





// Colors

#define clrscr() printf("\033[H\033[2J")
#define couleur(param) printf("\033[%sm",param)



//Manager

Time createtime(int* Exited);
void createrow(Row* Created_Row_Adress, char Row_Category, int Row_Position, int* Exited);
void Display_Rooms(Room* List_Of_Rooms, int Size_Of_List);
void Display_Not_Reserved_Rooms(Room* List_Of_Rooms, int Size_Of_List);
void SetTime(Time* Current_Time_Adress, int* Exited);
void createroom(Room* Created_Room_Adress, int* Exited);
void create_show(Show* Created_Show_Adress, int* Exited, Room* List_Of_Rooms, int Size_Of_List);
void deleteRoom(Room Room_To_Delete);
void deleteShow(Show Show_To_Delete);
void modifyRoom(Room* Room_To_Modify, int* Exited);


//Customer

void printTime(Time T);
void Display_Shows(Show* List_Of_Shows, int Size_Of_List);
void User_Reserve_Seats(Show* List_Of_Planned_Shows, int Size_Of_List_Of_Planned_Shows);


//Main

int couleurS(char* pr, char* para);
char* VerifCat(Row Ro);
void printShow(Show S);
void Menu_Customer(Room* Rooms_Tab, Show* Shows_Tab, int Size_Of_Rooms_Tab, int Size_Of_Shows_Tab);
void Menu_Manager(Room* Rooms_Tab, Show* Shows_Tab, int Size_Of_Rooms_Tab, int Size_Of_Shows_Tab, Time* Current_Time_Adress);
void Main_Menu(Room* Rooms_Tab, Show* Shows_Tab, int Size_Of_Rooms_Tab, int Size_Of_Shows_Tab, Time* Current_Time_Adress);
void SaveShows(Show tabshow[], int T);
void SaveRooms(Room tabroom[], int T);
Show* readShow();
Room* readRoom();
#endif
