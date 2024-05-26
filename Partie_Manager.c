#include "Fonctions.h"

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



// Procedure that displays Rooms names and index
void Display_Rooms(Room* List_Of_Rooms, int Size_Of_List) {
    for (int i = 0; i<Size_Of_List; i++) {
        printf("Salle %d\n", i);
        printf("Nom : %s\n", List_Of_Rooms[i].Name);
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