#include<stdio.h>
#include<stdlib.h>Returned_Roomr
#include<string.h>
#include<time.h>

typedef struct {
    int Seat_Number;                // How many seats are there on this row
    int* Seat_Tab;                  // Table containing the seats of the row. 
                                // The int corresponds to the number of persons on this seat (0, 1 or 2)
    char Category;                  // Category of the Row ("A", "B", "C")
} Row;

typedef struct {
    char Name[120];                 // Name of the room
    float Price_By_Category[2];     // Table of prices
    int Row_Number;                 // Number of rows in this room
    Row* Rows_Tab;                  // Table containing
    int Pit;                        // 1 if the Room has a pit, 0 otherwise
    int Is_Reserved;                // 1 if the Room is reserved, 0 otherwise
} Room;

typedef struct {
    int Hour;
    int Minutes;
} Time;

typedef struct  {
    char Show_Name[120];
    Room Used_Room;
    Time Starting_Time;
    Time Ending_Time;
} Show;

void printTime(Time T){
    if (T.Hour < 10) {
        printf("0");
    }
    printf("%dh", T.Hour);

    if (T.Minutes < 10) {
        printf("0");
    }
    printf("%d", T.Minutes);
}

void Display_Shows(Show* List_Of_Shows, int Size_Of_List) {
    for (int i = 0;(i<Size_Of_List); i++) {
        printf("i = %d\n", i);
        printf("Show %d : %s\n", i+1, List_Of_Shows[i].Show_Name);
        printf("Lieu : %s\n", List_Of_Shows[i].Used_Room);
        printf("Heure de début :" ); 
        printTime(List_Of_Shows[i].Starting_Time);
        printf("\nHeure de fin : %dh:%d \n\n", List_Of_Shows[i].Ending_Time.Hour, List_Of_Shows[i].Ending_Time.Minutes);
    }
}

void User_Reserve_Seats(Show* List_Of_Planned_Shows, int Size_Of_List_Of_Planned_Shows) {
    // Procedure that allows the user to reserve seats in a room
    
    int Chosen_Show_Number;                  // Position of the Show in the table List_Of_Planned_Shows
    int Reservation_Size;              
    char Chosen_Category;                       // Category of the reserved seat(s)
    char Manually_Choose_Seats;                 // "O" for True (then the program finds available seats), "N" for False
    int Size_Of_Largest_Row;                    // Size of the largest row of the category chosen by the user
    int Valid_Input;                            // Bool that will help make sure the user input is valid
   

    Display_Shows(List_Of_Planned_Shows, Size_Of_List_Of_Planned_Shows);


    // Ask the user to choose the show
    printf("\nChoisissez le concert auquel vous voulez participez (ou entrez 0 pour revenir au menu principal): \n");
    Valid_Input = 0;
    while(!Valid_Input) {           // Valid_Input != 1
        Valid_Input = (scanf(" %d", &Chosen_Show_Number)            // Check if the entry was an int 
        &&(Chosen_Show_Number>-1)                                   
        &&(Chosen_Show_Number<=Size_Of_List_Of_Planned_Shows)       // Check if the int is between 0 and the amount of proposed Shows
        &&(getchar() == '\n'));                                     // Check if there was nothing after the int (the entry was correct)
        if (!Valid_Input) {
            printf("Entrée invalide. Entrez le numéro du show auquel vous voulez participez comme présenté plus haut (ou 0 pour revenir au menu principal): \n");
            while(getchar() != '\n');                               // Empty the scanned string                        
        }
    }

    if (Chosen_Show_Number == 0) {             // If the user wants to go back to the main menu
        return;                                // Get out of the procedure User_Reserve_Seats
    }
    Chosen_Show_Number--;                      // Reduce by 1 the variable because it will be used as an index for tables




    // printRoom(List_of_Planned_Shows[Chosen_Show_Number].Used_Room);                            // Display the room to the user so he can pick his seat(s)    

    // Ask the user to choose the category of his seat
    Valid_Input = 0;
    printf("Entrez catégorie de places voulez vous réserver (A, B ,C ou 0 pour revenir au menu): \n");
    while (!Valid_Input) {
        Valid_Input =   ((scanf("%c", &Chosen_Category)) 
                        &&(getchar() == '\n'))                      // Check if there was nothing after the int (the entry was correct)
                        && ((Chosen_Category == 'A')                // Check if the entry is valid
                        || (Chosen_Category == 'B') 
                        || ( Chosen_Category == 'C') 
                        || (Chosen_Category == '0'));
        if (!Valid_Input) {
            printf("\nEntrée invalide. Entrez catégorie de places voulez vous réserver (A, B ,C ou 0 pour revenir au menu): \n" );
            while(getchar() != '\n');                               // Empty the scanned string
        }
    }
    if (Chosen_Category == '0') {             // If the user wants to go back to the main menu
        return;                               // Get out of the procedure User_Reserve_Seats
    } 



    // Ask the user if he wants to manually choose his seat

    printf("Le programme peut vous attribuer des places automatiquement. \nVoulez vous choisir vous-même vos places ? (Oui : 'O', Non : 'N', '0' pour revenir au menu principal): ");
    Valid_Input = 0;
    while(!Valid_Input) {                                           // Valid_Input != 1
        Valid_Input = (scanf(" %c", &Manually_Choose_Seats)            // Check if the entry was an int 
                && ((Manually_Choose_Seats == 'O')                // Check if the entry is valid
                || (Manually_Choose_Seats == 'N') 
                || (Manually_Choose_Seats == '0'))       // Check if the int is between 0 and the amount of proposed Shows
        &&(getchar() == '\n'));                                     // Check if there was nothing after the int (the entry was correct)
        if (!Valid_Input) {
            printf("Entrée invalide. Entrez 'O', 'N' ou '0' pour revenir au menu principal: \n");
            while(getchar() != '\n');                               // Empty the scanned string                        
        }
    }
    if (Manually_Choose_Seats == '0') {             // If the user wants to go back to the main menu
        return;                                     // Get out of the procedure User_Reserve_Seats
    }



    // Find the size of the largest row of this category
    Room Chosen_Room = List_Of_Planned_Shows[Chosen_Show_Number].Used_Room;             // Store the room to shorten the code
    Size_Of_Largest_Row = 0;
    for (int i = 0; (i<Chosen_Room.Row_Number); i++) {
        if ((Chosen_Room.Rows_Tab)[i].Category == Chosen_Category) {
            // Keep the max between Size_Of_Largest_Row and the current row's size

            if (Size_Of_Largest_Row < (Chosen_Room.Rows_Tab)[i].Seat_Number){           // If this row has a larger size
                Size_Of_Largest_Row = (Chosen_Room.Rows_Tab)[i].Seat_Number;            // Keep the size of the largest row 
            }
        }
    }

    if (Manually_Choose_Seats == 'O') {
        
    }    


    int Ask_Reservation_Size() {

    int Reservation_Size;
    // Ask the user how many seats does he want to reserve
    printf("Combien de places voulez réserver (0 pour revenir au menu principal) : ");
    Valid_Input = 0;
    while(!Valid_Input) {                                         // Valid_Input != 1
        Valid_Input = (scanf(" %d", &Reservation_Size)            // Check if the entry was an int 
        &&(Reservation_Size>-1)                                   
        &&(Reservation_Size<=Size_Of_Largest_Row)       // Check if the int is between 0 and the amount of proposed Shows
        &&(getchar() == '\n'));                                     // Check if there was nothing after the int (the entry was correct)
        if (!Valid_Input) {
            printf("Entrée invalide. Entrez le numéro du show auquel vous voulez participez comme présenté plus haut (ou 0 pour revenir au menu principal): \n");
            while(getchar() != '\n');                               // Empty the scanned string                        
        }
    }
    return Reservation_Size;}
    





    Reservation_Size = 0; // Set the var to 0 by default to avoid it being a valid value from the get-go. Forces the user to enter a valid value
    do {
    printf("Combien de places voulez réserver : ");
    scanf("%d", &Reservation_Size);
    } while(Reservation_Size<0);
}

void Reserve_Seats(Room* Room_To_Modify, int Chosen_Row, int Chosen_Seat) {
    // Adds a person to the chosen seat (the program has already checked if the seat can be reserved)

    (((Room_To_Modify->Rows_Tab)[Chosen_Row]).Seat_Tab)[Chosen_Seat] += 1;
}

int main() {

    //setlocale(LC_ALL, "fr_FR.UTF-8");
    char Mode;

    Show* List_Of_Planned_Shows = calloc(25 , sizeof(Show));
    

    User_Reserve_Seats(List_Of_Planned_Shows, 25);
    

    return 1;
}

