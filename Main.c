#include "Fonctions.h"

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




void Menu_Customer(Room* Rooms_Tab, Show* Shows_Tab, int Size_Of_Rooms_Tab, int Size_Of_Shows_Tab) {
    
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
            for (int i = 0; i<Size_Of_Shows_Tab; i++) {
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

void Menu_Manager(Room* Rooms_Tab, Show* Shows_Tab, int Size_Of_Rooms_Tab, int Size_Of_Shows_Tab, Time* Current_Time_Adress) {

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
            Temp_Rooms_Tab = malloc((Size_Of_Rooms_Tab+1) * sizeof(Room));
            if (Temp_Rooms_Tab == NULL) {
                fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
                printf("Erreur d'allocation mémoire");
                break;
            }
            for (int i = 0; i<Size_Of_Rooms_Tab; i++){
                Temp_Rooms_Tab[i] = Rooms_Tab[i];
            }
            free(Rooms_Tab);
            Rooms_Tab = Temp_Rooms_Tab;
            createroom(Rooms_Tab + Size_Of_Rooms_Tab, &Exited_Create_Room);
            if (Exited_Create_Room) {
                Temp_Rooms_Tab = malloc(Size_Of_Rooms_Tab * sizeof(Room));
                for (int i = 0; i<Size_Of_Rooms_Tab; i++){
                    Temp_Rooms_Tab[i] = Rooms_Tab[i];
                }
                free(Rooms_Tab);
                Rooms_Tab = Temp_Rooms_Tab;
            }
            Size_Of_Rooms_Tab++;
            break;
        }

        case 2:
            {
            int Exited_Create_Show = 0;
            Show* Temp_Shows_Tab;
            Temp_Shows_Tab = malloc((Size_Of_Shows_Tab + 1) * sizeof(Show));
            if (Temp_Shows_Tab == NULL) {
                fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
                printf("Erreur d'allocation mémoire");
                return;
            }
            for (int i = 0; i<Size_Of_Shows_Tab; i++){
                Temp_Shows_Tab[i] = Shows_Tab[i];
            }
            free(Shows_Tab);
            Shows_Tab = Temp_Shows_Tab;
            Show New_Created_Shows;
            create_show(&New_Created_Shows, &Exited_Create_Show, Rooms_Tab, Size_Of_Shows_Tab);
            if (Exited_Create_Show) {
                Temp_Shows_Tab = malloc(Size_Of_Shows_Tab * sizeof(Show));
                for (int i = 0; i<Size_Of_Shows_Tab; i++){
                    Temp_Shows_Tab[i] = Shows_Tab[i];
                }
                free(Shows_Tab);
                Shows_Tab = Temp_Shows_Tab;
            }
            break;
            }

        case 3:
            {
            printf("\nVoici toutes les salles actuellement non réservés : ");
            Display_Not_Reserved_Rooms(Rooms_Tab, Size_Of_Rooms_Tab);
            int Exited_Modify = 0;
            int Chosen_Index = 0;
            printf("\nEntrez le numéro de la salle à modifier (ou -1 pour revenir en arrière) : ");
            Valid_Input = 0;
            while(!Valid_Input) {                                   // Valid_Input != 1
                Valid_Input = ((scanf("%d", &Chosen_Index))       // Check if the entry was an int 
                        && (Chosen_Index > -2)                     // Check if the int is between 0 and the amount of actions
                        && (Chosen_Index < Size_Of_Rooms_Tab)
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
            printf("\nVoici une liste de toutes les salles accompagné de leurs ratios : \n");
            Display_Rooms(Rooms_Tab, Size_Of_Rooms_Tab);
            break;}
        case 5:{
            int Exited_SetTime = 0;
            Time BackupTime = *Current_Time_Adress;
            SetTime(Current_Time_Adress, &Exited_SetTime);   
            if (&Exited_SetTime) {
                *Current_Time_Adress = BackupTime;
                break;
            }         
        }
        case 6:
            {
            int Chosen_Index;
            printf("\nVoici la liste des salles non réservées: ");
            Display_Not_Reserved_Rooms(Rooms_Tab, Size_Of_Rooms_Tab);
            
            Valid_Input = 0;
            printf("\nChoisir l'index de la salle à supprimer (ou -1 pour revenir en arrière) : ");
            while(!Valid_Input) {                                   // Valid_Input != 1
                Valid_Input = ((scanf("%d", &Chosen_Index))       // Check if the entry was an int 
                        && (Chosen_Index > -2)                     // Check if the int is between 0 and the amount of actions
                        && (Chosen_Index < Size_Of_Rooms_Tab)
                        && (Rooms_Tab[Chosen_Index].Is_Reserved == 0)   // Check the chosen room is not reserved (it has been displayed)                   
                        && (getchar() == '\n'));                    // Check if there was nothing after the int (the entry was correct)
                if (!Valid_Input) {
                    printf("Entrée invalide. Entrez le numéro de la salle à supprimer (ou -1 pour revenir en arrière) :");            
                    while(getchar() != '\n');                                                   // Empty the scanned string                        
                }
            }

            Room* Temp_Rooms_Tab;
            Temp_Rooms_Tab = malloc((Size_Of_Rooms_Tab-1) * sizeof(Room));
            if (Temp_Rooms_Tab == NULL) {
                fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
                printf("Erreur d'allocation mémoire");
                break;
            }
            for (int i = 0; i<Chosen_Index; i++){
                Temp_Rooms_Tab[i] = Rooms_Tab[i];
            }
            
            deleteRoom(Rooms_Tab[Chosen_Index]);
            for (int i = Chosen_Index; i<Size_Of_Rooms_Tab-1; i++) {
                Temp_Rooms_Tab[i] = Rooms_Tab[i+1];
            }
        }
        case 7: {
            int Chosen_Index;
            printf("\nVoici la liste des concerts ");
            Display_Shows(Shows_Tab, Size_Of_Shows_Tab);
            
            Valid_Input = 0;
            printf("\nChoisir l'index de la salle à supprimer (ou -1 pour revenir en arrière) : ");
            while(!Valid_Input) {                                   // Valid_Input != 1
                Valid_Input = ((scanf("%d", &Chosen_Index))       // Check if the entry was an int 
                        && (Chosen_Index > -2)                     // Check if the int is between 0 and the amount of actions
                        && (Chosen_Index < Size_Of_Rooms_Tab)
                        && (Rooms_Tab[Chosen_Index].Is_Reserved == 0)   // Check the chosen room is not reserved (it has been displayed)                   
                        && (getchar() == '\n'));                    // Check if there was nothing after the int (the entry was correct)
                if (!Valid_Input) {
                    printf("Entrée invalide. Entrez le numéro de la salle à supprimer (ou -1 pour revenir en arrière) :");            
                    while(getchar() != '\n');                                                   // Empty the scanned string                        
                }
            }

            Room* Temp_Rooms_Tab;
            Temp_Rooms_Tab = malloc((Size_Of_Rooms_Tab-1) * sizeof(Room));
            if (Temp_Rooms_Tab == NULL) {
                fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
                printf("Erreur d'allocation mémoire");
                break;
            }
            for (int i = 0; i<Chosen_Index; i++){
                Temp_Rooms_Tab[i] = Rooms_Tab[i];
            }
            
            deleteRoom(Rooms_Tab[Chosen_Index]);
            for (int i = Chosen_Index; i<Size_Of_Rooms_Tab-1; i++) {
                Temp_Rooms_Tab[i] = Rooms_Tab[i+1];
            }
        }
        }
    }
}

// Allows the user to pick between manager mode, customer mode, and leaving the program
void Main_Menu(Room* Rooms_Tab, Show* Shows_Tab, int Size_Of_Rooms_Tab, int Size_Of_Shows_Tab, Time* Current_Time_Adress) {
    
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
            Menu_Manager(Rooms_Tab, Shows_Tab, Size_Of_Rooms_Tab, Size_Of_Shows_Tab, Current_Time_Adress);
            break;
        case 2:
            Menu_Customer(Rooms_Tab, Shows_Tab, Size_Of_Rooms_Tab, Size_Of_Shows_Tab);
            break;
        }
    }
}

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
            fscanf(file, "%d %c ", &(tabroom[i].Rows_Tab[k].Seat_Number), &(tabroom[i].Rows_Tab[k].Category));
            for (int m=0; m<tabroom[i].Rows_Tab[k].Seat_Number; m++){
                fscanf(file, "%d ", &(tabroom[i].Rows_Tab[k].Seat_Tab[m]));
            }
        }
        i++;
    }
    fclose(file);
    return tabroom;
}



int main() {
    int Input;
    int VInput = 0 ;
    Show* List_Of_Planned_Shows = calloc(3 , sizeof(Show));                         //Remplacer par la fonction qui importe les structures
    
    printf("\nBienvenue ! Vous êtes dans GE500 le gestionnaire de concerts le plus efficace !\n");

    Room* Rooms_Tab = malloc(0 * sizeof(Room));
    Show* Shows_Tab = malloc(0 * sizeof(Show));
    int Size_Of_Rooms_Tab = 0;
    int Size_Of_Shows_Tab = 0;
    Time CurrentTime;

    Shows_Tab = readShow();
    
    create_show(Shows_Tab, &Input, Rooms_Tab, Size_Of_Rooms_Tab);
    Display_Shows(Shows_Tab, 1);
    printShow(Shows_Tab[0]);
    
    SaveShows(Shows_Tab, Size_Of_Shows_Tab);

    
    //Main_Menu(Rooms_Tab, Shows_Tab, Size_Of_Rooms_Tab, Size_Of_Shows_Tab, &CurrentTime);
   
    return 1;

}
