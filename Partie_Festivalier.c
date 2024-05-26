#include"Fonctions.h"

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
    printShow(Chosen_Room);                 // Display the room to the user so he can pick his seat(s)

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
            printShow(Chosen_Room);   



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
                    printShow(ChosenRoom);
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
                    printShow(ChosenRoom);
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


        printShow(Chosen_Room)
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


        


    
   
    
    
    

    



    

    





