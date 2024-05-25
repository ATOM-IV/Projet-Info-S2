#include "Fonctions.h"


// A refaire par rapport aux printfs (il faudrait garder les scanf seulement dans cette fonction)
Time createtime(){
    Time time;
    printf("\nChoisissez l'heure de début du concert : ");
    scanf("%d",&time.Hour);

    printf("\nChoisissez les minutes de début du concert : ");
    scanf("%d",&time.Minutes);

    return time;
}


void createrow(Row* Created_Row_Adress, char Row_Category, int Row_Position, int* Exited) {
    
    Row Created_Row;
    int Valid_Input = 0;
    printf("\nEntrez le nombre de sièges de la rangée %d de la catégorie %c, ou 0 pour revenir au menu manager : ", Row_Position, Row_Category);
    while (Valid_Input == 0) {
        Valid_Input = (scanf(" %d", &(Created_Row.Seat_Number))
            && (Created_Row.Seat_Number >= 0)
            && (getchar() == '\n'));

        if (Valid_Input == 0) {
            printf("\nEntrée invalide. Entrez le nombre de siège pour cette rangée ou 0 pour revenir au menu manager : ");
            while(getchar() != '\n');
        }
    }

    if (Created_Row.Seat_Number == 0) {
        *Exited = 1;
        return;
    }   
    
    
    *Created_Row_Adress = Created_Row;
}

//fonction visant à créer une salle 
void createroom(Room* Created_Room_Adress, int* Exited){
    
    Room Created_Room;
    int Row_Number_By_Category[2];
    int Valid_Input;


    *Exited = 0;

    printf("\nEntrez le nom de la salle (moins de 119 caractères) : ");
    scanf("%s",Created_Room.Name);

    Valid_Input = 0;

    for (int i = 0; i < 3 ; i++) {    // For categories A, B and C (3 times)

        // Ask the manager to choose the number of rows of categories A, B and C
        Valid_Input = 0;
        printf("\nEntrez le nombre de rangées de catégories %c (ou -1 pour revenir au menu manager) : ", i + 'A');
        while(Valid_Input == 0) {
            Valid_Input = ( (scanf(" %d", Row_Number_By_Category+i) == 1)
                &&(Row_Number_By_Category[i] >= -1)
                &&(getchar() == '\n'));
                
            if (Valid_Input == 0) {
                printf("\nEntrée invalide. Entrez un entier naturel ou -1 pour revenir au menu manager : \n");
                while(getchar() != '\n');
            }
        }

        if (Row_Number_By_Category[i] == -1) {
            *Exited = 1;
            return;
        }

        // Ask the manager to choose the price of seats of categories A, B and C
        Valid_Input = 0;
        printf("\nEntrez le prix des rangées de catégories  %c (ou -1 pour revenir au menu manager) : ", i + 'A');
        while(Valid_Input == 0) {
            Valid_Input = ( (scanf(" %f", Created_Room.Price_By_Category+i) == 1)
                &&((Created_Room.Price_By_Category[i] >= 0) || (Created_Room.Price_By_Category[i] == -1))
                &&(getchar() == '\n'));
                
            if (Valid_Input == 0) {
                printf("\nEntrée invalide. Entrez un prix positif ou -1 pour revenir au menu manager : ");
                while(getchar() != '\n');
            }
        }

        if (Created_Room.Price_By_Category[i] == -1) {
            *Exited = 1;
            return;
        }
    }

    Created_Room.Rows_Tab = malloc((Row_Number_By_Category[0] + Row_Number_By_Category[1] + Row_Number_By_Category[2] )*sizeof(Row));
    if (Created_Room.Rows_Tab == NULL){
        fprintf(stderr,"\nErreur d'allocation mémoire\n");
    };


    for(int i=0;i<Row_Number_By_Category[i]; i++){
        createrow(Created_Room.Rows_Tab + i, 'A', i, Exited);
    }



    printf("\nLa salle possède t'elle une fosse ? (Oui = 1 et Non = 0) : ");
    scanf("%d",&Created_Room.Pit);
    while(Created_Room.Pit!=0 && Created_Room.Pit!=1){
    printf("\nErreur de saisie.\nLa salle possède t'elle une fosse ? (Oui = 1 et Non = 0) : ");
    scanf("%d",&Created_Room.Pit);
    };
    
    *Created_Room_Adress = Created_Room;
}


Show create_Show(){
    Show Created_Show;
    printf("\nEntrez le nom du concert (119 caractères maximum) : ");
    scanf("%s",Created_Show.Show_Name);

    
    int Exited;
    createroom(&(Created_Show.Used_Room), &Exited);

    Created_Show.Starting_Time = createtime();

    Created_Show.Ending_Time = createtime();

    return Created_Show;
    }

