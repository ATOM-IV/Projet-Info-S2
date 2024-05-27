#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#define clrscr() printf("\033[H\033[2J")
#define couleur(param) printf("\033[%sm",param)
// Struct

typedef struct {
    int Seat_Number;                // How many seats are there on this row
    int* Seat_Tab;                  // Table containing the seats of the row. 
                                    // The int corresponds to the number of persons on this seat (0, 1 or 2)
    char Category;                  // Category of the Row ("A", "B", "C")
} Row;

typedef struct {
    char* Name;                 // Name of the room
    float* Price_By_Category;     // Table of prices
    int Row_Number;                 // Number of rows in this room
    Row* Rows_Tab;                  // Table containing the rows
    int Pit;                        // 1 if the Room has a pit, 0 otherwise
    int Is_Reserved;                // 1 if the Room is reserved, 0 otherwise
    int Capacity;
    int Number_Of_Reservations;
} Room;

typedef struct {
    int Hour;
    int Minutes;
} Time;

typedef struct  {
    char* Show_Name;
    Room* Used_Room_Adress;
    Time Starting_Time;
    Time Ending_Time;
} Show;

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// CUSTOMER FONCTIONS ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////



int couleurS(char* pr, char* para){
    couleur("0");
    couleur(para);
    printf("%s",pr);
    couleur("0");
    return 0;
}

char* VerifCat(Row Ro){
    switch(Ro.Category){
        case 'A' :  return "36" ;break;
        case 'B' :  return "34" ;break;
        case 'C' :  return "35" ;break;
        default  :  return "X"  ;break;
    }

}

void printShow(Show S){
    int acc = 0;
    int disp = 0;
    int accCatA = 0;
    Room R;

    R = *(S.Used_Room_Adress);

    printf("\nPlan des places disponibles pour la %s pour le concert %s :\n", R.Name, S.Show_Name);
    printf(" ________________________________\n");
    if (R.Pit == 0){
        for (int i=0; i<R.Row_Number; i++){
            
            printf("%c %d - ", R.Rows_Tab[i].Category, i+1);
            for (int j=0; j<R.Rows_Tab[i].Seat_Number;j++){
                
                switch(R.Rows_Tab[i].Seat_Tab[j]){
                    case 0 :    couleurS("0",VerifCat(R.Rows_Tab[i])); printf(" ");break;
                    case 1 :    couleurS("X","31"); printf(" ");break;
                    case 2 :    printf(" ");break;
                    default :   printf(" ");break;
                }
            }
            printf("\n");
        }
    }
    if (R.Pit == 1){
        for (int i=0; i<R.Row_Number; i++){
            if (VerifCat(R.Rows_Tab[i]) == "36") {
                for (int j=0; j<R.Rows_Tab[i].Seat_Number;j++){
                switch(R.Rows_Tab[i].Seat_Tab[j]){
                    case 0 :    disp += 2;break;
                    case 1 :    disp += 2;acc = acc + 1;break;
                    case 2 :    disp += 2;acc = acc + 2;
                                disp = disp + 2;break;
                    default :   disp += 2;break;
                    }
                }
            accCatA = accCatA + 1;
            }
        }
        printf("A - Le nombre de place prises sur le nombre places disponibles est : %d/%d", acc, disp);
        printf("\n");
        for (int i = accCatA + 1; i<R.Row_Number; i++){
            printf("%c %d ", R.Rows_Tab[i].Category, i+1);
            for (int j=0; j<R.Rows_Tab[i].Seat_Number;j++){
                switch(R.Rows_Tab[i].Seat_Tab[j]){
                    case 0 :    couleurS("0",VerifCat(R.Rows_Tab[i])); printf(" ");break;
                    case 1 :    couleurS("X","31"); printf(" ");break;
                    case 2 :    printf(" ");break;
                    default :   printf(" ");break;
                }
            }
            printf("\n");
        }
    }
    printf("\nLégende : ");
    couleurS("\n0", "36"); printf(" - Catégorie A : %.2f", R.Price_By_Category[0]);
    couleurS("\n0", "34"); printf(" - Catégorie B : %.2f", R.Price_By_Category[1]);
    couleurS("\n0", "35"); printf(" - Catégorie C : %.2f", R.Price_By_Category[2]);
    couleurS("\nX", "31"); printf(" - Siège réservé");
}


// Displays a time in a "HHhMM" format
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


// Procedure that displays the information of every show contained in a list of a given size
void Display_Shows(Show* List_Of_Shows, int Size_Of_List) {
    for (int i = 0;(i<Size_Of_List); i++) {
        printf("Show %d : %s\n", i+1, List_Of_Shows[i].Show_Name);
        printf("Lieu : %s\n", (List_Of_Shows[i].Used_Room_Adress)->Name);
        printf("Heure de début :" ); 
        printTime(List_Of_Shows[i].Starting_Time);
        printf("\nHeure de fin :");
        printTime(List_Of_Shows[i].Ending_Time);
        printf("\n");
    }
}


// Procedure that allows 


// Procedure that allows the user to reserve seats in a room
void User_Reserve_Seats(Show* List_Of_Planned_Shows, int Size_Of_List_Of_Planned_Shows) {
    
    int Chosen_Show_Number;                     // Position of the Show in the table List_Of_Planned_Shows
    int Reservation_Size;                       // Number of seats the user wants to reserve
    char Chosen_Category;                       // Category of the reserved seat(s)
    char Manually_Choose_Seats;                 // 'O' for True, 'N' for False
    int Valid_Input;                            // Bool that will help make sure the user input is valid
    float Total_Cost;                           // Sum of the cost of each individual reservation
    int Confirm;                                // Confirm the reservation (1 or 0)
    

    Display_Shows(List_Of_Planned_Shows, Size_Of_List_Of_Planned_Shows);
    // Ask the user to choose the show
    printf("\nChoisissez le concert auquel vous voulez participez (ou entrez 0 pour revenir au menu principal): \n");
    Valid_Input = 0;
    while(Valid_Input == 0) {                                       // Valid_Input != 1
        Valid_Input = (scanf(" %d", &Chosen_Show_Number)            // Check if the entry was an int 
        &&(Chosen_Show_Number>-1)                                   
        &&(Chosen_Show_Number<=Size_Of_List_Of_Planned_Shows)       // Check if the int is between 0 and the amount of proposed Shows
        &&(getchar() == '\n'));                                     // Check if there was nothing after the int (the entry was correct)
        if (Valid_Input == 0) {
            printf("Entrée invalide. Entrez le numéro du concert auquel vous voulez participez comme présenté plus haut (ou 0 pour revenir au menu principal): \n");
            while(getchar() != '\n');                               // Empty the scanned string                        
        }
    }
    if (Chosen_Show_Number == 0) {                                  // If the user wants to go back to the main menu
        return;                                                     // Get out of the procedure User_Reserve_Seats
    }
    Chosen_Show_Number--;                                           // Reduce by 1 the variable because it will be used as an index for tables
    

    Room Chosen_Room = *(List_Of_Planned_Shows[Chosen_Show_Number].Used_Room_Adress);   // Store the room to shorten the code
    printShow(List_Of_Planned_Shows[Chosen_Show_Number]);                 // Display the room to the user so he can pick his seat(s)

    // Ask the user if he wants to manually choose his seat
    printf("Le programme peut vous attribuer des places automatiquement. Voulez vous choisir vous-même vos places ? \n'O' pour Oui, 'N' pour Non, '0' pour revenir au menu principal :\n ");
    Valid_Input = 0;
    while(!Valid_Input) {                                                               // Valid_Input != 1
        Valid_Input = ((scanf(" %c", &Manually_Choose_Seats))                           // Check if the entry was an int 
                && ((Manually_Choose_Seats == 'O')                                      // Check if the entry is valid
                || (Manually_Choose_Seats == 'N') 
                || (Manually_Choose_Seats == '0'))                                      // Check if the int is between 0 and the amount of proposed Shows
        &&(getchar() == '\n'));                                                         // Check if there was nothing after the int (the entry was correct)
        if (!Valid_Input) {
            printf("Entrée invalide. Entrez 'O', 'N' ou '0' pour revenir au menu principal: \n");            
            while(getchar() != '\n');                                                   // Empty the scanned string                        
        }
    }
    if (Manually_Choose_Seats == '0') {                                                 // If the user wants to go back to the main menu
        return;                                                                         // Get out of the procedure User_Reserve_Seats
    }





    if (Manually_Choose_Seats == 'O') {
        int Chosen_Row;                 // Row of the seat to reserve
        int Chosen_Seat;                // Number of the seat to reserve
        


        // Ask how many seats to reserve
        printf("\nIl reste %d place(s) disponible(s) pour ce concert.", Chosen_Room.Capacity - Chosen_Room.Number_Of_Reservations);
        printf("\nCombien de places voulez réserver ? (0 pour revenir au menu principal) : \n");
        Valid_Input = 0;
        while(!Valid_Input) {                                           // Valid_Input != 1
        Valid_Input = (scanf(" %d", &Reservation_Size)              // Check if the entry was an int 
            &&(Reservation_Size>-1)                                   
            &&(Reservation_Size<=Chosen_Room.Capacity - Chosen_Room.Number_Of_Reservations)                   // Check if the int is between 0 and the size of the largest row
            &&(getchar() == '\n'));                                     // Check if there was nothing after the int (the entry was correct)
            if (!Valid_Input) {
                printf("Entrée invalide. Entrez un entier entre %d et 0 (0 pour revenir au menu principal): \n");
                while(getchar() != '\n');                               // Empty the scanned string                        
            }
        }
        if (Reservation_Size == 0) {                                                        // If the user wants to go back to the main menu
            return;                                                                         // Get out of the procedure User_Reserve_Seats
        }
        
        
        // Ask for the row and position of each seats to reserve, reserve those, calculate total price
        for (int i = 0; i<Reservation_Size; i++)
        {
            printShow(List_Of_Planned_Shows[Chosen_Show_Number]);   



            // Ask the user to choose the row of his seat
            Valid_Input = 0;
            printf("Entrez le numéro de la rangée de la place à réserver, ou 0 pour revenir au menu principal: \n");
            while (!Valid_Input) {
                Valid_Input =   (scanf("%d", &Chosen_Row))            // Check if the entry is valid
                        && (Chosen_Row >= 0)                
                        && (Chosen_Row <= Chosen_Room.Row_Number)
                        &&(getchar() == '\n');                     

                if (!Valid_Input) {                   
                    while(getchar() != '\n');                               // Empty the scanned string
                    printShow(List_Of_Planned_Shows[Chosen_Show_Number]);
                    printf("\nEntrée invalide. Entrez le numéro de la rangée de la place à réserver, ou 0 pour revenir au menu principal: \n" );
                }
            }
            if (Chosen_Row == 0) {                                      // If the user wants to go back to the main menu
            return;                                                     // Get out of the procedure User_Reserve_Seats
            }
            Chosen_Row--;



            // Ask the user to choose the number of his seat
            Valid_Input = 0;
            printf("Entrez le numéro de la place à réserver, ou 0 pour revenir au menu principal: \n");
            while (!Valid_Input) {
                Valid_Input =   (scanf("%d", &Chosen_Seat))            // Check if the entry is valid
                        && (Chosen_Seat >= 0)                          // Number is positive
                        && (Chosen_Seat <= Chosen_Room.Rows_Tab[Chosen_Row].Seat_Number)    // Number is not superior to number of seats
                        && ((Chosen_Room.Rows_Tab[Chosen_Row].Seat_Tab[Chosen_Seat] == 0)
                            ||  ((Chosen_Room.Pit == 1)
                                &&(Chosen_Room.Rows_Tab[Chosen_Row].Category == 'A')
                                &&(Chosen_Room.Rows_Tab[Chosen_Row].Seat_Tab[Chosen_Seat] == 1)))
                        &&(getchar() == '\n');                     
                if (!Valid_Input) {                   
                    while(getchar() != '\n');                               // Empty the scanned string
                    printShow(List_Of_Planned_Shows[Chosen_Show_Number]);
                    printf("\nEntrée invalide. Entrez le numéro de la place à réserver, ou 0 pour revenir au menu principal: \n" );
                }
            }
            if (Chosen_Seat == 0) {                                         // If the user wants to go back to the main menu
            return;                                                         // Get out of the procedure User_Reserve_Seats
            }


            Chosen_Room.Rows_Tab[Chosen_Row].Seat_Tab[Chosen_Seat] += 1;    // Reserve this seat on the Chosen_Room var.
                                                                            // Reservation will only take effect when the procedure is done
            Total_Cost += Chosen_Room.Price_By_Category[Chosen_Room.Rows_Tab[Chosen_Row].Category -'A'];
            // Adds to the total coast
        }






    }    

    if (Manually_Choose_Seats == 'N') {

        int Max_Consecutive_Empty_Seat_Number;                  // Largest number of consecutive empty seats of the chosen category
        int Free_Places;                                        // Helps keep track of the largest number of consecutive empty seats of the chosen category
        int Sequence_Start_Index;                               // Helps keep track of

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
        if (Chosen_Category == '0') {                                   // If the user wants to go back to the main menu
            return;                                                     // Get out of the procedure User_Reserve_Seats
        }


         
        
        // Find the size of the largest amount of consecutive empty seats (on the same row) of this category
        Max_Consecutive_Empty_Seat_Number = 0;
        for (int i = 0; (i<Chosen_Room.Row_Number); i++) {                              // For each row of the room
            if (Chosen_Room.Rows_Tab[i].Category == Chosen_Category) {                  // If the row is of the correct category
                if ((Chosen_Category == 'A')&&(Chosen_Room.Pit)) {                      // If the seats may hold 2 persons
                    for (int j = 0; j<Chosen_Room.Rows_Tab[i].Seat_Number; j++) {       // For each seat of this row
                        if (Chosen_Room.Rows_Tab[i].Seat_Tab[j] !=2) {                  // If the seat is not full
                            Free_Places += 2 - Chosen_Room.Rows_Tab[i].Seat_Tab[j];     // Add the number of available places                        
                        }
                        else {                                                          // If the seat is not free
                            Free_Places = 0;                                            // Break the sequence of free seats
                        }
                        if (Free_Places > Max_Consecutive_Empty_Seat_Number) {          // If a longer sequence of empty seats was found
                            Max_Consecutive_Empty_Seat_Number = Free_Places;            // Keep its size
                        }
                    }
                }

                else {                                                                  // If each seat can only hold one person
                    for (int j = 0; j<Chosen_Room.Rows_Tab[i].Seat_Number; j++) {       // For each seat of this row
                        if (Chosen_Room.Rows_Tab[i].Seat_Tab[j] == 0) {                 // If the seat is free 
                            Free_Places ++;                                             // Add one free place to the count of free places                        
                        }
                        else {                                                          // If the seat is not free
                            Free_Places = 0;                                            // Break the sequence of free seats
                        }
                        if (Free_Places > Max_Consecutive_Empty_Seat_Number) {          // If a longer sequence of empty seats was found
                            Max_Consecutive_Empty_Seat_Number = Free_Places;            // Keep its size
                        }
                    }
                }
            }
        }


        printShow(List_Of_Planned_Shows[Chosen_Show_Number]);
        // Ask how many seats to reserve
        printf("\nVous pouvez automatiquement réserver %d place(s) de catégories %c au plus pour ce concert.", Max_Consecutive_Empty_Seat_Number, Chosen_Category);
        printf("\nCombien de places voulez réserver ? (0 pour revenir au menu principal) : \n");
        Valid_Input = 0;
        while(!Valid_Input) {                                           // Valid_Input != 1
        Valid_Input = (scanf(" %d", &Reservation_Size)              // Check if the entry was an int 
            &&(Reservation_Size>-1)                                   
            &&(Reservation_Size<=Max_Consecutive_Empty_Seat_Number)                   // Check if the int is between 0 and the size of the largest row
            &&(getchar() == '\n'));                                     // Check if there was nothing after the int (the entry was correct)
            if (!Valid_Input) {
                printf("Entrée invalide. Entrez un entier entre %d et 0 (0 pour revenir au menu principal): \n");
                while(getchar() != '\n');                               // Empty the scanned string                        
            }
        }
        if (Reservation_Size == 0) {                                                        // If the user wants to go back to the main menu
            return;                                                                         // Get out of the procedure User_Reserve_Seats
        }


        int Reservation_Seat_Start;                   // Index of the reservation's start seat (the leftmost seat )
        int Reservation_Seat_End;                     // Index of the reservation's end seat (the rightmost seat)
        int Reservation_Seat_Row = -1;                // Row containing the largest number of consecutive empty seats of the chosen category

        // Find the sequence of available seats that is closest to the scene (furthest in the front)  
        for (int i = 0; (i<Chosen_Room.Row_Number); i++) {                              // For each row of the room
            if (Chosen_Room.Rows_Tab[i].Category == Chosen_Category) {                  // If the row is of the correct category
                if ((Chosen_Category == 'A')&&(Chosen_Room.Pit)) {                      // If the seats may hold 2 persons
                    for (int j = 0; j<Chosen_Room.Rows_Tab[i].Seat_Number; j++) {       // For each seat of this row
                        Free_Places = 0;
                        Sequence_Start_Index = j;
                        if (Chosen_Room.Rows_Tab[i].Seat_Tab[j] !=2) {                  // If the seat is not full
                            Free_Places += 2 - Chosen_Room.Rows_Tab[i].Seat_Tab[j];     // Add the number of available places
                        }
                        else {                                                          // If the seat is full
                            Free_Places = 0;                                            // Break the sequence of free seats
                            Sequence_Start_Index = j;                                   // Set the new starting index for the new sequence 
                        }
                        if ((Free_Places > Reservation_Size)                            // If a sufficiently long sequence of empty seats was found
                        &&((Reservation_Seat_Row>=i)||(Reservation_Seat_Row==-1))       // And it is not further from the scene than the sequence found before 
                        &&( (((i+j)/2) - Chosen_Room.Rows_Tab[i].Seat_Number)           // And the distance of the new sequence's center relative to the row's center
                        * (((i+j)/2) - Chosen_Room.Rows_Tab[i].Seat_Number)             
                        <=                                                              // Is inferior or equal to the previous distance
                        (((Reservation_Seat_End+Reservation_Seat_Row)/2 - Chosen_Room.Rows_Tab[i].Seat_Number)
                        *(Reservation_Seat_End+Reservation_Seat_Row)/2 - Chosen_Room.Rows_Tab[i].Seat_Number)))

                                                                                        
                        {                 
                            Reservation_Seat_Start = Sequence_Start_Index;    // Store its starting index
                            Reservation_Seat_End = j;                         // Store its ending index
                            Reservation_Seat_Row = i;                         // Store its row's index
                        }
                    }
                }

                else {                                                                  // If each seat can only hold one person
                    for (int j = 0; j<Chosen_Room.Rows_Tab[i].Seat_Number; j++) {       // For each seat of this row
                        if (Chosen_Room.Rows_Tab[i].Seat_Tab[j] == 0) {                 // If the seat is free 
                            Free_Places ++;                                             // Add one free place to the count of free places                        
                        }
                        else {                                                          // If the seat is not free
                            Free_Places = 0;                                            // Break the sequence of free seats
                            Sequence_Start_Index = j;                                   // Set the new starting index for the new sequence 
                        }
                        if ((Free_Places > Reservation_Size)                            // If a sufficiently long sequence of empty seats was found
                        &&((Reservation_Seat_Row>=i)||(Reservation_Seat_Row==-1))       // And it is not further from the scene than the sequence found before 
                        &&( (((i+j)/2) - Chosen_Room.Rows_Tab[i].Seat_Number)           // And the distance of the new sequence's center relative to the row's center
                        * (((i+j)/2) - Chosen_Room.Rows_Tab[i].Seat_Number)             
                        <=                                                              // Is inferior or equal to the previous distance
                        (((Reservation_Seat_End+Reservation_Seat_Row)/2 - Chosen_Room.Rows_Tab[i].Seat_Number)
                        *(Reservation_Seat_End+Reservation_Seat_Row)/2 - Chosen_Room.Rows_Tab[i].Seat_Number)))

                                                                                        
                        {                 
                            Reservation_Seat_Start = Sequence_Start_Index;    // Store its starting index
                            Reservation_Seat_End = j;                         // Store its ending index
                            Reservation_Seat_Row = i;                         // Store its row's index
                        }
                    }
                }
            }
        }

        
        if ((Chosen_Category == 'A')&&(Chosen_Room.Pit)) {              // If the seats can hold up to 2 persons
            int Done_Reservations = 0;
            for (int i = 0; (Done_Reservations<Reservation_Size);i++) {                 // For each seat
                if (Chosen_Room.Rows_Tab[Reservation_Seat_Row].Seat_Tab[Reservation_Seat_Start+i] != 2) {   // If the seat is not full
                    Chosen_Room.Rows_Tab[Reservation_Seat_Row].Seat_Tab[Reservation_Seat_Start+i]++;       // Add a person                                                                                    
                    Done_Reservations++;
                    i--;
                } 
            }
        }
        else {
            for (int i = 0;(i<Reservation_Size); i++) {
                Chosen_Room.Rows_Tab[Reservation_Seat_Row].Seat_Tab[Reservation_Seat_Start+i]++;
            }
        }

        Total_Cost = Reservation_Size * Chosen_Room.Price_By_Category[Chosen_Category-'A'];
    }
    
    
    printf("Le prix de l'ensemble de vos réservations s'élève à %f euros. Confirmer la réservation? \nOui : 1\nNon : 0", Total_Cost);
    Valid_Input = 0;
    while(Valid_Input == 0) {                                       // Valid_Input != 1
        Valid_Input = (scanf(" %d", &Confirm)                       // Check if the entry was scanned 
        &&((Confirm == 1)||(Confirm == 0))                          // Check if the entry was 0 or 1
        &&(getchar() == '\n'));                                     // Check if there was nothing after the int (the entry was correct)
        if (Valid_Input == 0) {
            printf("Entrée invalide. Entrez 1 pour confirmer la réservation ou 0 pour l'annuler : \n");
            while(getchar() != '\n');                               // Empty the scanned string                        
        }
    }
    if (Confirm == 0) {                                             // If the user wants to go back to the main menu
        return;                                                     // Get out of the procedure User_Reserve_Seats
    }
    else{
        List_Of_Planned_Shows[Chosen_Show_Number].Used_Room_Adress = &Chosen_Room;
        Chosen_Room.Number_Of_Reservations += Reservation_Size;
        printf("\nRéservation réussie\n");
    }

}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// MANAGER FONCTIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


// Fonction that creates a time structure
Time createtime(int* Exited) {
    Time time;
    
    int Valid_Input = 0;
    printf("Entrez le nombre d'heure (ou -1 pour revenir en arrière) : \n");
    while(Valid_Input == 0) {
        Valid_Input =   (scanf("%d", &time.Hour))
                        && (time.Hour > -2) && (time.Hour < 24)
                        && (getchar() == '\n');
        if (!Valid_Input) {
            printf("\nEntrée invalide. Entrez le nombre d'heure ou -1 pour revenir en arrièr : \n");
            while(getchar() != '\n');
        }
    }

    if (time.Hour == -1){
        *Exited = 1;
        return time;
    }

    Valid_Input = 0;
    printf("Entrez le nombre de minutes (ou -1 pour revenir en arrière) : \n");
    while(Valid_Input == 0) {
        Valid_Input =   (scanf("%d", &time.Minutes))
                        && (time.Minutes > -2) && (time.Minutes < 60)
                        && (getchar() == '\n');
        if (!Valid_Input) {
            printf("\nEntrée invalide. Entrez le nombre de minutes ou -1 pour revenir en arrière : \n");
            while(getchar() != '\n');
        }
    }
    if (time.Minutes == -1){
        *Exited = 1;
        return time;
    }
    return time;
}


// Procedure that creates a row
void createrow(Row* Created_Row_Adress, char Row_Category, int Row_Position, int* Exited) {
    Row Created_Row;
    int Valid_Input = 0;
    printf("\nEntrez le nombre de sièges de la rangée %d de la catégorie %c, ou 0 pour revenir au menu manager : ", Row_Position+1, Row_Category);
    while (Valid_Input == 0) {
        Valid_Input = (scanf(" %d", &(Created_Row.Seat_Number)) == 1 && Created_Row.Seat_Number >= 0);
        if (Valid_Input == 0) {
            printf("\nEntrée invalide. Entrez le nombre de sièges pour cette rangée ou 0 pour revenir au menu manager : ");
            while (getchar() != '\n'); // Clear the input buffer
        }
    }
    Created_Row.Category = Row_Category;
    if (Created_Row.Seat_Number == 0) {
        *Exited = 1;
        return;
    }
    Created_Row.Seat_Tab = calloc(Created_Row.Seat_Number , sizeof(int));
    *Created_Row_Adress = Created_Row;
}

// Empty a room after a concert is done
void Empty_Show(Show Show_to_empty){
    for(int i=0;i<(Show_to_empty.Used_Room_Adress)->Row_Number; i++) {
        for (int j =0; j<(Show_to_empty.Used_Room_Adress)->Rows_Tab[i].Seat_Number;j++) {
            free((Show_to_empty.Used_Room_Adress)->Rows_Tab[i].Seat_Tab);
            (Show_to_empty.Used_Room_Adress)->Rows_Tab[i].Seat_Tab = calloc((Show_to_empty.Used_Room_Adress)->Rows_Tab[i].Seat_Number, sizeof(int));
        }
    }
}

// Procedure that displays Rooms names and index
void Display_Rooms(Room* List_Of_Rooms, int Size_Of_List) {
    for (int i = 0; i<Size_Of_List; i++) {
        printf("\nSalle %d\n", i);
        printf("Nom : %s\n", List_Of_Rooms[i].Name);
        if (List_Of_Rooms[i].Capacity != 0) {
        printf("Ratio réservées / non réservées : %.2f pourcents\n", (List_Of_Rooms[i].Number_Of_Reservations/List_Of_Rooms[i].Capacity) * 100);
        }
        else {printf("Ratio réservées / non réservées : La capacité de la salle est nulle\n");}
    }
}



// Procedure that displays only non reserved rooms
void Display_Not_Reserved_Rooms(Room* List_Of_Rooms, int Size_Of_List) {
    for (int i = 0; i<Size_Of_List; i++) {
        if ((List_Of_Rooms[i]).Is_Reserved == 0) {
            printf("Salle %d : \n", i);
            printf("Nom : %s", List_Of_Rooms[i].Name);
        }
    }
}


// Procedure that sets current time (simulation)
void SetTime(Time* Current_Time_Adress, int* Exited) {
    Time New_Time;
    printf("\nEntrez l'heure actuelle :");
    New_Time = createtime(Exited);
    if (*Exited == 1) {
        printf("\nL'ancien temps sera conservé\n");
        return;
    }
}



// Procedure that creates a room
void createroom(Room* Created_Room_Adress, int* Exited) {
    Room Created_Room; 
    int* Row_Number_By_Category = malloc(3*sizeof(int));
    if (Row_Number_By_Category == NULL) {
        fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
        *Exited = 1;
        return;
    }


    int Valid_Input;

    *Exited = 0;

    Created_Room.Name = malloc(120* sizeof(char));
    if (Created_Room.Name == NULL) {
        fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
        *Exited = 1;
        return;
    }
    printf("\nEntrez le nom de la salle (moins de 119 caractères) : ");
    scanf("%119s", Created_Room.Name); // Using %119s to prevent buffer overflow

    for (int i = 0; i < 3; i++) {
        Valid_Input = 0;
        printf("\nEntrez le nombre de rangées de catégorie %c (ou -1 pour revenir au menu manager) : ", i + 'A');
        while (Valid_Input == 0) {
            Valid_Input = (scanf(" %d", &Row_Number_By_Category[i]) == 1 && Row_Number_By_Category[i] >= -1);
            if (Valid_Input == 0) {
                printf("\nEntrée invalide. Entrez un entier naturel ou -1 pour revenir au menu manager : ");
                while (getchar() != '\n'); // Clear the input buffer
            }
        }

        if (Row_Number_By_Category[i] == -1) {
            *Exited = 1;
            return;
        }

        Created_Room.Price_By_Category = malloc(3*sizeof(float));
        if (Created_Room.Price_By_Category == NULL){
            fprintf(stderr, "\nErreur d'allocation mémoire\n");
            *Exited = 1;
            return;
        }
        Valid_Input = 0;
        printf("\nEntrez le prix des rangées de catégorie %c (ou -1 pour revenir au menu manager) : ", i + 'A');
        while (Valid_Input == 0) {
            Valid_Input = ((scanf(" %f", (Created_Room.Price_By_Category + i)) ==1) && (Created_Room.Price_By_Category[i] >= -1));
            if (Valid_Input == 0) {
                printf("\nEntrée invalide. Entrez un prix positif ou -1 pour revenir au menu manager : ");
                while (getchar() != '\n'); // Clear the input buffer
            }
        }

        if (Created_Room.Price_By_Category[i] == -1) {
            *Exited = 1;
            return;
        }
    }

    Created_Room.Rows_Tab = malloc((Row_Number_By_Category[0] + Row_Number_By_Category[1] + Row_Number_By_Category[2]) * sizeof(Row));
    if (Created_Room.Rows_Tab == NULL) {
        fprintf(stderr, "\nErreur d'allocation mémoire\n");
        *Exited = 1;
        return;
    }

    for (int i = 0; i < Row_Number_By_Category[0]; i++) {                   // For each row of category A
        createrow(&Created_Room.Rows_Tab[i], 'A', i, Exited);               // Create it
        Created_Room.Capacity += Created_Room.Rows_Tab[i].Seat_Number*(1 + Created_Room.Pit);
        if (*Exited) {                                                      // If the user wants to exit
            for (int j = 0; j<i; j++) {                                     // For each row of category A that is already created
                free(Created_Room.Rows_Tab[j].Seat_Tab);                    // Free the row's Seat_Tab
            }
            free(Created_Room.Name);                                        // Free the Created_Room's name
            free(Created_Room.Rows_Tab);                                    // Free the Room's row tab
            free(Created_Room.Price_By_Category);                           // Free the table of prices by Category
            return;
        }
    }
    for (int i = 0; i < Row_Number_By_Category[1]; i++) {                   // For each row of category B
        createrow(&Created_Room.Rows_Tab[i + Row_Number_By_Category[0]], 'B', i, Exited);   // Create it
        Created_Room.Capacity += Created_Room.Rows_Tab[i + Row_Number_By_Category[0]].Seat_Number;
        if (*Exited) {                                                      // If the user wants to exit
            for (int j = 0; j<Row_Number_By_Category[0]; j++){              // For each row of category A
                free(Created_Room.Rows_Tab[j].Seat_Tab);                    // Free the row's Seat_Tab
            }
            for (int j = 0; j<i; j++) {                                     // For each row of category B that has already been created
                free(Created_Room.Rows_Tab[j+Row_Number_By_Category[0]].Seat_Tab);  // Free the row's Seat_Tab
            }
            free(Created_Room.Name);                                        // Free the Created_Room's name
            free(Created_Room.Rows_Tab);                                    // Free the Room's row tab
            free(Created_Room.Price_By_Category);                           // Free the table of prices by Category
            return;
        }
    }

    for (int i = 0; i < Row_Number_By_Category[2]; i++) {                   // For each row of category C
        createrow(&Created_Room.Rows_Tab[i + Row_Number_By_Category[0] + Row_Number_By_Category[1]], 'C', i, Exited);
        Created_Room.Capacity += Created_Room.Rows_Tab[i + Row_Number_By_Category[0]+ Row_Number_By_Category[1]].Seat_Number;
        if (*Exited) {                                                      // If the user wants to exit
            for (int j = 0; j<Row_Number_By_Category[0]; j++){              // For each row of category A
                free(Created_Room.Rows_Tab[j].Seat_Tab);                    // Free the row's Seat_Tab
            }
            for (int j = 0; j<Row_Number_By_Category[1]; j++) {             // For each row of category B that has already been created
                free(Created_Room.Rows_Tab[j+Row_Number_By_Category[0]].Seat_Tab);  // Free the row's Seat_Tab
            }
            for (int j = 0; j<Row_Number_By_Category[i]; j++) {             // For each row of category B that has already been created
                free(Created_Room.Rows_Tab[j+Row_Number_By_Category[0]+ Row_Number_By_Category[1]].Seat_Tab);  // Free the row's Seat_Tab
            }
            free(Created_Room.Name);                                        // Free the Created_Room's name
            free(Created_Room.Rows_Tab);                                    // Free the Room's row tab
            free(Created_Room.Price_By_Category);                           // Free the table of prices by Category
            return;
        }
    }

    printf("\nLa salle possède-t-elle une fosse ? (Oui = 1 et Non = 0) : ");
    while (scanf("%d", &(Created_Room.Pit)) != 1 || (Created_Room.Pit != 0 && Created_Room.Pit != 1)) {
        printf("\nErreur de saisie. La salle possède-t-elle une fosse ? (Oui = 1 et Non = 0) : ");
        while (getchar() != '\n'); // Clear the input buffer
    }

    Created_Room.Row_Number = Row_Number_By_Category[0] + Row_Number_By_Category[1]+ Row_Number_By_Category[2];
    free(Row_Number_By_Category);
    *Created_Room_Adress = Created_Room;
}

// Procedure that creates a show
void create_show(Show* Created_Show_Adress, int* Exited, Room* List_Of_Rooms, int Size_Of_List) {
    Show Created_Show;

    Created_Show.Used_Room_Adress = malloc(1 * sizeof(Room));
    if (Created_Show.Used_Room_Adress == NULL) {
        fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
        *Exited = 1;
        return;
    }
    Created_Show.Show_Name = malloc(120* sizeof(char));
    if (Created_Show.Show_Name == NULL) {
        fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
        *Exited = 1;
        return;
    }
    printf("\nEntrez le nom du concert (119 caractères maximum) : ");
    scanf("%119s", Created_Show.Show_Name); // Using %119s to prevent buffer overflow

    int Valid_Input = 0;
    int Choice;
    Valid_Input = 0;
    printf("\nPour ce concert, voulez vous:\n0 - Sortir\n1 - Allouer une salle déjà existante \n2 - Créer une nouvelle salle\n");
    while (Valid_Input == 0) {
        Valid_Input = (scanf(" %d", &Choice) == 1) 
                        && ((Choice == 0)||(Choice == 1)||(Choice ==2));
        if (Valid_Input == 0) {
            printf("\nEntrée invalide. Pour ce concert, voulez vous:\n0 - Sortir\n1 - Allouer une salle déjà existante \n2 - Créer une nouvelle salle\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    }
    if (Choice == 0) {
        free(Created_Show.Show_Name);
        free(Created_Show.Used_Room_Adress);
        return;
    }
    if (Choice == 1) {
        Display_Not_Reserved_Rooms(List_Of_Rooms, Size_Of_List);
        int Chosen_Index = 0;
        printf("\nEntrez le numéro de la salle à attribuer (ou -1 pour revenir en arrière) : ");
        Valid_Input = 0;
        while(!Valid_Input) {                                   // Valid_Input != 1
            Valid_Input = ((scanf("%d", &Chosen_Index))       // Check if the entry was an int 
                    && (Chosen_Index > -2)                     // Check if the int is between 0 and the amount of actions
                    && (Chosen_Index < Size_Of_List)
                    && (List_Of_Rooms[Chosen_Index].Is_Reserved == 0)   // Check the chosen room is not reserved (it has been displayed)                   
                    && (getchar() == '\n'));                    // Check if there was nothing after the int (the entry was correct)
            if (!Valid_Input) {
                printf("Entrée invalide. Entrez le numéro de la salle à attribuer (ou 0 pour revenir en arrière) :");            
                while(getchar() != '\n');                                                   // Empty the scanned string                        
            }
        }
    }
    if (Choice == 2) {
        createroom(Created_Show.Used_Room_Adress, Exited);
        if (*Exited) {
        free(Created_Show.Show_Name);
        free(Created_Show.Used_Room_Adress);
        return;
        }
    }
    
    printf("\nRenseignez le temps de début : \n");
    Created_Show.Starting_Time = createtime(Exited);
    printf("\nRenseignez le temps de fin du concert : \n");
    Created_Show.Ending_Time = createtime(Exited);

    *Created_Show_Adress = Created_Show;
}

// Procedure that deletes a room
void deleteRoom(Room Room_To_Delete) {
    free(Room_To_Delete.Name);
    for (int i = 0; i<Room_To_Delete.Row_Number; i++) {
        free(Room_To_Delete.Rows_Tab[i].Seat_Tab);
    }

    free(Room_To_Delete.Rows_Tab);
}

// Procedure that deletes a show
void deleteShow(Show Show_To_Delete) {
    deleteRoom(*(Show_To_Delete.Used_Room_Adress));
    free(Show_To_Delete.Show_Name);
}


// Procedure that modifies a room's settings
void modifyRoom(Room* Room_To_Modify, int* Exited) {
    if (Room_To_Modify->Is_Reserved == 0) {
        deleteRoom(*Room_To_Modify);
        createroom(Room_To_Modify, Exited);
    }
}





void Menu_Customer(Room* Rooms_Tab, Show* Shows_Tab, int* Size_Of_Rooms_Tab, int* Size_Of_Shows_Tab_Adress) {
    
    int Exited_Customer = 0;
    int Valid_Input;
    int Chosen_Action;
    
    while(Exited_Customer == 0) {
        Valid_Input = 0;
        printf( "\nMenu festivalier - Sélectionnez l'action à réaliser :"
                "\n0 - Revenir au menu principal"
                "\n1 - Découvrir les concerts disponibles"
                "\n2 - Réserver des sièges pour un concert\n");

        while(!Valid_Input) {
            Valid_Input = ((scanf(" %d", &Chosen_Action))       // Check if the entry was an int 
                && (Chosen_Action >-1)                          // Check if the int is between 0 and the amount of actions
                && (Chosen_Action < 3)                   
                && (getchar() == '\n'));                        // Check if there was nothing after the int (the entry was correct)
            if (!Valid_Input) {
                printf("Entrée invalide. Sélectionnez l'action à réaliser :"
                "\n0 - Revenir au menu principal"
                "\n1 - Découvrir les concerts disponibles"
                "\n2 - Réserver des sièges pour un concert\n");            
                while(getchar() != '\n');                       // Empty the scanned string                        
            }
        }
        switch (Chosen_Action)
        {
        case 0:
            /////////////// A ENLEVER
            printShow(Shows_Tab[0]);
            Exited_Customer = 1;
            printf("\nSortie du mode festivalier\n");
            break;
        case 1:
            for (int i = 0; i<*Size_Of_Shows_Tab_Adress; i++) {
                printf("\n");
                Display_Shows(Shows_Tab, 1);
                printShow(Shows_Tab[i]);
                printf("\n");
            }
        default:
            break;
        }
    }
}

void Menu_Manager(Room* Rooms_Tab, Show* Shows_Tab, int* Size_Of_Rooms_Tab_Adress, int* Size_Of_Shows_Tab_Adress, Time* Current_Time_Adress) {

    int Valid_Input;
    int Chosen_Action;

    while(1) {
        Valid_Input = 0;
        printf( "\nMenu manager - Sélectionnez le mode dans lequel vous voulez entrer :"  
                "\n0 - Revenir au menu principal" 
                "\n1 - Créer une salle" 
                "\n2 - Créer un concert"
                "\n3 - Modifier une salle non réservé"
                "\n4 - Accéder aux ratios places réservées/non reservées"
                "\n5 - Définir le temps actuel"
                "\n6 - Supprimer une salle"
                "\n7 - Supprimer un concert \n");
        
        
        while(!Valid_Input) {                                   // Valid_Input != 1
            Valid_Input = ((scanf(" %d", &Chosen_Action))       // Check if the entry was an int 
                    && (Chosen_Action >-1)                     // Check if the int is between 0 and the amount of actions
                    && (Chosen_Action < 8)                   
                    && (getchar() == '\n'));                    // Check if there was nothing after the int (the entry was correct)
            if (!Valid_Input) {
                printf("Entrée invalide. Entrez :\n0 - Revenir au menu principal \n1 - Créer une salle\n2 - Créer un concert\n3 - Modifier une salle non réservé\n4 - Accéder aux ratios places réservées/non reservées\n5 - Définir le temps actuel\n6 - Supprimer une salle\n7 - Supprimer un concert \n");            
                while(getchar() != '\n');                                                   // Empty the scanned string                        
            }
        }

        switch (Chosen_Action)
        {
        case 0:
            return;

        case 1:{
            int Exited_Create_Room = 0;
            Room* Temp_Rooms_Tab;
            Temp_Rooms_Tab = malloc((*Size_Of_Rooms_Tab_Adress+1) * sizeof(Room));
            if (Temp_Rooms_Tab == NULL) {
                fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
                printf("Erreur d'allocation mémoire");
                break;
            }
            for (int i = 0; i<*Size_Of_Rooms_Tab_Adress; i++){
                Temp_Rooms_Tab[i] = Rooms_Tab[i];
            }
            free(Rooms_Tab);
            Rooms_Tab = Temp_Rooms_Tab;
            createroom(Rooms_Tab + *Size_Of_Rooms_Tab_Adress, &Exited_Create_Room);
            if (Exited_Create_Room) {
                Temp_Rooms_Tab = malloc(*Size_Of_Rooms_Tab_Adress * sizeof(Room));
                for (int i = 0; i<*Size_Of_Rooms_Tab_Adress; i++){
                    Temp_Rooms_Tab[i] = Rooms_Tab[i];
                }
                free(Rooms_Tab);
                Rooms_Tab = Temp_Rooms_Tab;
            }
            *Size_Of_Rooms_Tab_Adress++;
            break;
        }

        case 2:
            {
            int Exited_Create_Show = 0;
            Show* Temp_Shows_Tab;
            Temp_Shows_Tab = malloc((*Size_Of_Shows_Tab_Adress + 1) * sizeof(Show));
            if (Temp_Shows_Tab == NULL) {
                fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
                printf("Erreur d'allocation mémoire");
                return;
            }
            for (int i = 0; i<*Size_Of_Shows_Tab_Adress; i++){
                Temp_Shows_Tab[i] = Shows_Tab[i];
            }
            free(Shows_Tab);
            Shows_Tab = Temp_Shows_Tab;
            Show New_Created_Shows;
            create_show(&New_Created_Shows, &Exited_Create_Show, Rooms_Tab, *Size_Of_Shows_Tab_Adress);
            if (Exited_Create_Show) {
                Temp_Shows_Tab = malloc(*Size_Of_Shows_Tab_Adress * sizeof(Show));
                for (int i = 0; i<*Size_Of_Shows_Tab_Adress; i++){
                    Temp_Shows_Tab[i] = Shows_Tab[i];
                }
                free(Shows_Tab);
                Shows_Tab = Temp_Shows_Tab;
            }
            break;
            }

        case 3:
            {
            int Number_Of_Not_Reserved_Rooms=0;
            for (int i = 0; i<*Size_Of_Rooms_Tab_Adress; i++) {
                Number_Of_Not_Reserved_Rooms += Rooms_Tab[i].Is_Reserved == 0;
            }
            if (Number_Of_Not_Reserved_Rooms == 0) {
                printf("\nIl n'y a aucune salle non réservée que vous pouvez modifier pour l'instant");
                break;
            }

            printf("\nVoici toutes les salles actuellement non réservés : ");
            Display_Not_Reserved_Rooms(Rooms_Tab, *Size_Of_Rooms_Tab_Adress);
            int Exited_Modify = 0;
            int Chosen_Index = 0;
            printf("\nEntrez le numéro de la salle à modifier (ou -1 pour revenir en arrière) : ");
            Valid_Input = 0;
            while(!Valid_Input) {                                   // Valid_Input != 1
                Valid_Input = ((scanf("%d", &Chosen_Index))       // Check if the entry was an int 
                        && (Chosen_Index > -2)                     // Check if the int is between 0 and the amount of actions
                        && (Chosen_Index < *Size_Of_Rooms_Tab_Adress)
                        && (Rooms_Tab[Chosen_Index].Is_Reserved == 0)   // Check the chosen room is not reserved (it has been displayed)                   
                        && (getchar() == '\n'));                    // Check if there was nothing after the int (the entry was correct)
                if (!Valid_Input) {
                    printf("Entrée invalide. Entrez le numéro de la salle à modifier (ou 0 pour revenir en arrière) :");            
                    while(getchar() != '\n');                                                   // Empty the scanned string                        
                }
            }
            if (Chosen_Index == -1) {    
                break;
            }
            Room Backup_Room = Rooms_Tab[Chosen_Action];
            modifyRoom(Rooms_Tab + Chosen_Index, &Exited_Modify);
            if (Exited_Modify) {
                Rooms_Tab[Chosen_Index] = Backup_Room;
            }
            }

        case 4:{

            if (*Size_Of_Rooms_Tab_Adress == 0){
                printf("\nIl n'y a aucune salle à afficher pour l'instant");
                break;
            }
            printf("\nVoici une liste de toutes les salles accompagné de leurs ratios : \n");
            Display_Rooms(Rooms_Tab, *Size_Of_Rooms_Tab_Adress);
            break;}
        case 5: {
            int Exited_SetTime = 0;   
            Time BackupTime = *Current_Time_Adress;
            SetTime(Current_Time_Adress, &Exited_SetTime);   
            if (&Exited_SetTime) {
                *Current_Time_Adress = BackupTime;
                break;
            }
            for (int i = 0; i<*Size_Of_Shows_Tab_Adress; i++) {
                if ((Current_Time_Adress->Hour > Shows_Tab[i].Ending_Time.Hour) || ((Current_Time_Adress->Hour == Shows_Tab[i].Ending_Time.Hour) && (Current_Time_Adress->Minutes > Shows_Tab[i].Ending_Time.Minutes))) {
                    Empty_Show(Shows_Tab[i]);
                }
            }
            break;
        }
        case 6:
            
            {
            if (*Size_Of_Rooms_Tab_Adress == 0) {
                printf("\nIl n'y a aucune salle à supprimer pour l'instant");
                break;
            }
            
            int Chosen_Index;
            printf("\nVoici la liste des salles non réservées: ");
            Display_Not_Reserved_Rooms(Rooms_Tab, *Size_Of_Rooms_Tab_Adress);
            
            Valid_Input = 0;
            printf("\nChoisir l'index de la salle à supprimer (ou -1 pour revenir en arrière) : ");
            while(!Valid_Input) {                                   // Valid_Input != 1
                Valid_Input = ((scanf("%d", &Chosen_Index))       // Check if the entry was an int 
                        && (Chosen_Index > -2)                     // Check if the int is between 0 and the amount of actions
                        && (Chosen_Index < *Size_Of_Rooms_Tab_Adress)
                        && (Rooms_Tab[Chosen_Index].Is_Reserved == 0)   // Check the chosen room is not reserved (it has been displayed)                   
                        && (getchar() == '\n'));                    // Check if there was nothing after the int (the entry was correct)
                if (!Valid_Input) {
                    printf("Entrée invalide. Entrez le numéro de la salle à supprimer (ou -1 pour revenir en arrière) :");            
                    while(getchar() != '\n');                                                   // Empty the scanned string                        
                }
            }

            Room* Temp_Rooms_Tab;
            Temp_Rooms_Tab = malloc((*Size_Of_Rooms_Tab_Adress-1) * sizeof(Room));
            if (Temp_Rooms_Tab == NULL) {
                fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
                printf("Erreur d'allocation mémoire");
                break;
            }
            for (int i = 0; i<Chosen_Index; i++){
                Temp_Rooms_Tab[i] = Rooms_Tab[i];
            }
            
            deleteRoom(Rooms_Tab[Chosen_Index]);

            for (int i = Chosen_Index; i<*Size_Of_Rooms_Tab_Adress-1; i++) {
                Temp_Rooms_Tab[i] = Rooms_Tab[i+1];
            }
            Rooms_Tab = realloc(Rooms_Tab, *Size_Of_Rooms_Tab_Adress-1);
            if (Temp_Rooms_Tab == NULL) {
                fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
                break;
            }
            *Size_Of_Rooms_Tab_Adress--;

            for (int i = 0; i<*Size_Of_Rooms_Tab_Adress; i++){
                Rooms_Tab[i] = Temp_Rooms_Tab[i];
            }

            free(Temp_Rooms_Tab);
            break;
        }
        case 7: {
            int Chosen_Index;
            if (*Size_Of_Shows_Tab_Adress == 0) {
                printf("\nIl n'y a aucun concert à supprimer pour l'instant");
                break;
            }

            printf("\nVoici la liste des concerts ");
            Display_Shows(Shows_Tab, *Size_Of_Shows_Tab_Adress);
            Valid_Input = 0;
            printf("\nChoisir l'index de la salle à supprimer (ou -1 pour revenir en arrière) : ");
            while(!Valid_Input) {                                   // Valid_Input != 1
                Valid_Input = ((scanf("%d", &Chosen_Index))       // Check if the entry was an int 
                        && (Chosen_Index > -2)                     // Check if the int is between 0 and the amount of actions
                        && (Chosen_Index < *Size_Of_Rooms_Tab_Adress)
                        && (Rooms_Tab[Chosen_Index].Is_Reserved == 0)   // Check the chosen room is not reserved (it has been displayed)                   
                        && (getchar() == '\n'));                    // Check if there was nothing after the int (the entry was correct)
                if (!Valid_Input) {
                    printf("Entrée invalide. Entrez le numéro de la salle à supprimer (ou -1 pour revenir en arrière) :");            
                    while(getchar() != '\n');                                                   // Empty the scanned string                        
                }
            }

            Room* Temp_Rooms_Tab;
            Temp_Rooms_Tab = malloc((*Size_Of_Rooms_Tab_Adress-1) * sizeof(Room));
            if (Temp_Rooms_Tab == NULL) {
                fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
                printf("Erreur d'allocation mémoire");
                break;
            }
            for (int i = 0; i<Chosen_Index; i++){
                Temp_Rooms_Tab[i] = Rooms_Tab[i];
            }
            
            deleteRoom(Rooms_Tab[Chosen_Index]);
            for (int i = Chosen_Index; i<*Size_Of_Rooms_Tab_Adress-1; i++) {
                Temp_Rooms_Tab[i] = Rooms_Tab[i+1];
            }
            break;
        }
        }
    }
}

// Allows the user to pick between manager mode, customer mode, and leaving the program
void Main_Menu(Room* Rooms_Tab, Show* Shows_Tab, int Size_Of_Rooms_Tab_Adress, int Size_Of_Shows_Tab_Adress, Time* Current_Time_Adress) {
    
    int Valid_Input = 0;
    int Chosen_Mode;
    ///////////////////ImportData();

    while(1) { 
    
        Valid_Input = 0;
        printf( "\nMenu - Sélectionnez le mode dans lequel vous voulez entrer :"  
                "\n0 - Quitter le programme\n1 - Accéder au mode Manager pour gérer le site"
                "\n2 - Accéder au mode festivalier pour réserver des places\n");
        while(!Valid_Input) {                                                               // Valid_Input != 1
            Valid_Input = ((scanf(" %d", &Chosen_Mode))                                     // Check if the entry was an int 
                    && ((Chosen_Mode == 2)                                                  // Check if the entry is valid
                    || (Chosen_Mode == 1) 
                    || (Chosen_Mode == 0))                                                  // Check if the int is between 0 and 2
            &&(getchar() == '\n'));                                                         // Check if there was nothing after the int (the entry was correct)
            if (!Valid_Input) {
                printf("Entrée invalide. Entrez \n0 - Quitter le programme\n1 - Accéder au mode Manager pour gérer le site"
                "\n2 - Accéder au mode festivalier pour réserver des places\n");            
                while(getchar() != '\n');                                                   // Empty the scanned string                        
            }
        }

        switch (Chosen_Mode)
        {
        case 0:
            /////////////////SaveData();
            printf("\nSauvegarde des données");
            printf("\nSortie du programme\n");
            return;

        case 1:
            Menu_Manager(Rooms_Tab, Shows_Tab, Size_Of_Rooms_Tab_Adress, Size_Of_Shows_Tab_Adress, Current_Time_Adress);
            break;
        case 2:
            Menu_Customer(Rooms_Tab, Shows_Tab, Size_Of_Rooms_Tab_Adress, Size_Of_Shows_Tab_Adress);
            break;
        }
    }
}












// Obsolete main menu
/*
void Menu_Principal(int Input, int VInput, Show* List_Of_Planned_Shows){
    int Code;
    int VInput2 = 0;
    
    Show* myShow;
    int Choice;
    int Exited = 0;
    myShow = malloc(50 * sizeof(Show)) 
    printf("\nMenu - Sélectionnez le mode dans lequel vous voulez entrer :  \n0 - Quitter le programme\n1 - Accéder au mode Manager pour gérer le site\n2 - Accéder au mode festivalier pour réserver des places\n");

    while (VInput==0){
        VInput=((scanf("%d",&Input)) && (Input>=0) && (Input<=2) && (getchar()=='\n'));

        if (VInput==0){
            printf("\nErreur de saisie.\nChoisissez un terme valide : ");
            while (getchar()!='\n');
        }
    }
    switch(Input){
        case 0 :    if (!Exited) {deleteShow(myShow);}
                    printf("\nQuitter le programme.\n");
                    exit(0);break;                                                 //Mettre plus tard le save ici
        case 1 :    printf("\nEntrez le code Manager pour accéder à la gestion du site : ");
                    while (VInput2==0){
                        VInput2=((scanf("%d",&Code)) && (Code == 5680) && (getchar()=='\n'));
                        if (VInput2==0){
                            printf("\nMauvais code.\nEntrez à nouveau : ");
                            while (getchar()!='\n');
                        }
                    }
                    while (1) {
                        printf("\nMenu:\n");
                        printf("1. Créer un concert\n");
                        printf("2. Modifier la salle du concert\n");
                        printf("3. Supprimer le concert\n");
                        printf("4. Quitter\n");
                        printf("Entrez votre choix : ");
                        scanf("%d", &Choice);
                        while (getchar() != '\n'); // Clear the input buffer

                        switch (Choice) {
                            case 1:
                                    create_show(myShow, &Exited);
                                    printf("\nConcert créé avec succès!\n");
                                    break;

                            case 2:
                            if (!Exited) {
                                modifyRoom(&(myShow.Used_Room_Adress));
                                printf("\nSalle modifiée avec succès!\n");
                            } else {
                            printf("\nAucun concert créé pour modifier la salle.\n");
                            }
                            break;

                        case 3:
                            if (!Exited) {
                                deleteShow(*myShow);
                                Exited = 1;
                                printf("\nConcert supprimé avec succès!\n");
                            } else {
                                printf("\nAucun concert créé pour supprimer.\n");
                            }
                            break;

                        case 4: 
                            Menu_Principal(0, 0, List_Of_Planned_Shows);
                            break;

                        default:
                            printf("\nChoix invalide. Veuillez réessayer.\n");
                        }
                    };break;
        case 2 :    printf("\nVoici la liste des concerts déjà prévus : \n");
                    User_Reserve_Seats(List_Of_Planned_Shows, 3);break;
        default :   break;
    }
}
*/


// Files Fonctions
/*

void SaveShows(Show tabshow[], int T){
    FILE *file = fopen("Shows.txt", "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<T;i++){
        fprintf(file, "%s %d %d %d %d ", tabshow[i].Show_Name, tabshow[i].Starting_Time.Hour, tabshow[i].Starting_Time.Minutes, tabshow[i].Ending_Time.Hour, tabshow[i].Ending_Time.Minutes);
        fprintf(file, "%s %d %d %d %d %d ", (tabshow[i].Used_Room_Adress)->Name, (tabshow[i].Used_Room_Adress)->Pit, (tabshow[i].Used_Room_Adress)->Row_Number, (tabshow[i].Used_Room_Adress)->Is_Reserved, (tabshow[i].Used_Room_Adress)->Capacity, (tabshow[i].Used_Room_Adress)->Number_Of_Reservations);
        for (int j = 0; j < 3; j++){
            fprintf(file, "%.2f ", (tabshow[i].Used_Room_Adress)->Price_By_Category[j]);
        }
        for (int m = 0; m < (tabshow[i].Used_Room_Adress)->Row_Number; m++){
            fprintf(file, "%d %c ", (tabshow[i].Used_Room_Adress)->Rows_Tab[m].Seat_Number, (tabshow[i].Used_Room_Adress)->Rows_Tab[m].Category);
            for (int k = 0; k < (tabshow[i].Used_Room_Adress)->Rows_Tab[m].Seat_Number; k++){
                fprintf(file, "%d ", (tabshow[i].Used_Room_Adress)->Rows_Tab[m].Seat_Tab[k]);
            }
        }
    }
    fclose(file);
}

void SaveRooms(Room tabroom[], int T){
    FILE *file = fopen("Rooms.txt", "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<T;i++){
        fprintf(file, "%s %d %d %d %d %d ", tabroom[i].Name, tabroom[i].Pit, tabroom[i].Row_Number, tabroom[i].Is_Reserved, tabroom[i].Capacity, tabroom[i].Number_Of_Reservations);
        for (int j = 0; j < 3; j++){
            fprintf(file, "%.2f ", tabroom[i].Price_By_Category[j]);
        }
        for (int k=0; k<tabroom[i].Row_Number; k++){
            fprintf(file, "%d %c ", tabroom[i].Rows_Tab[k].Seat_Number, tabroom[i].Rows_Tab[k].Category);
            for (int m=0; m<tabroom[i].Rows_Tab[k].Seat_Number; m++){
                fprintf(file, "%d ", tabroom[i].Rows_Tab[k].Seat_Tab[m]);
            }
        }
    }
    fclose(file);
}



Show* readShow(){
    FILE *file = fopen("Shows.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    Show *tabshow = malloc(100 * sizeof(Show));             //Changer le 100 avec une fonction qui retourne la valeur exacte
    if (tabshow == NULL) {
        perror("Allocation mémoire échouée");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (fscanf(file, "%s %d %d %d %d ", tabshow[i].Show_Name, &(tabshow[i].Starting_Time.Hour), &(tabshow[i].Starting_Time.Minutes), &(tabshow[i].Ending_Time.Hour), &(tabshow[i].Ending_Time.Minutes)) == 5){
        fscanf(file, "%s %d %d %d %d %d ", (tabshow[i].Used_Room_Adress)->Name, &((tabshow[i].Used_Room_Adress)->Pit), &((tabshow[i].Used_Room_Adress)->Row_Number), &((tabshow[i].Used_Room_Adress)->Is_Reserved), &((tabshow[i].Used_Room_Adress)->Capacity), &((tabshow[i].Used_Room_Adress)->Number_Of_Reservations));
        for (int j = 0; j < 3; j++){
            fscanf(file, "%.2f ", &((tabshow[i].Used_Room_Adress)->Price_By_Category[j]));
        }
        for (int m = 0; m < (tabshow[i].Used_Room_Adress)->Row_Number; m++){
            fscanf(file, "%d %c ", &((tabshow[i].Used_Room_Adress)->Rows_Tab[m].Seat_Number), &((tabshow[i].Used_Room_Adress)->Rows_Tab[m].Category));
            for (int k = 0; k < (tabshow[i].Used_Room_Adress)->Rows_Tab[m].Seat_Number; k++){
                fscanf(file, "%d ", &((tabshow[i].Used_Room_Adress)->Rows_Tab[m].Seat_Tab[k]));
            }
        }
        i++;
    }
    fclose(file);
    return tabshow;
}

Room* readRoom(){
    FILE *file = fopen("Rooms.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    Room *tabroom = malloc(100 * sizeof(Room));             //Changer le 100 avec une fonction qui retourne la valeur exacte
    if (tabroom == NULL) {
        perror("Allocation mémoire échouée");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (fscanf(file, "%s %d %d %d %d %d ", tabroom[i].Name, &(tabroom[i].Pit), &(tabroom[i].Row_Number), &(tabroom[i].Is_Reserved), &(tabroom[i].Capacity), &(tabroom[i].Number_Of_Reservations))==6){
        for (int j = 0; j < 3; j++){
            fscanf(file, "%.2f ", &(tabroom[i].Price_By_Category[j]));
        }
        for (int k=0; k<tabroom[i].Row_Number; k++){
            fprintf(file, "%d %c ", &(tabroom[i].Rows_Tab[k].Seat_Number), &(tabroom[i].Rows_Tab[k].Category));
            for (int m=0; m<tabroom[i].Rows_Tab[k].Seat_Number; m++){
                fprintf(file, "%d ", &(tabroom[i].Rows_Tab[k].Seat_Tab[m]));
            }
        }
        i++;
    }
    fclose(file);
    return tabroom;
}

*/



int main() {
    int Input;
    int VInput = 0 ;    
    printf("\nBienvenue ! Vous êtes dans GE500 le gestionnaire de concerts le plus efficace !\n");

    Room* Rooms_Tab = malloc(0 * sizeof(Room));
    Show* Shows_Tab = malloc(0 * sizeof(Show));
    int Size_Of_Rooms_Tab = 0;
    int Size_Of_Shows_Tab = 0;
    Time CurrentTime;
    

    Main_Menu(Rooms_Tab, Shows_Tab, &Size_Of_Rooms_Tab, &Size_Of_Shows_Tab, &CurrentTime);
   
    return 1;

}
