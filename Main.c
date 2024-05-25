#include "Fonctions.h"

int couleurS(char pr, char para){
    couleur("0");
    couleur(para);
    printf("%s",pr);
    couleur("0");
    return 0;
}

char* VerfiCat(Row* Ro){
    switch(Ro.Category){
        case 'A' :  return "36" ;break;
        case 'B' :  return "34" ;break;
        case 'C' :  return "35" ;break;
    }

}


void printShow(Room R){
    printf("\nPlan des places disponibles pour la %s :\n", R.Name);
    printf("________________________________\n");
    for (int i=0; i<R.Row_Number; i++){
        printf("%c %d", R.Rows_Tab[i].Category, i+1);
        if (R.Pit == 0){
            for (int j=0; j<R.Rows_Tab[i].Seat_Number;j++){
                switch(R.Rows_Tab[i].Seat_Tab[j]){
                    case 0 :    couleurS("0",VerfiCat(R.Rows_Tab[i])); printf(" ");break;
                    case 1 :    couleurS("X","31"); printf(" ");break;
                    case 2 :    printf(" ");break;
                    default :   printf(" ");break;
                }
            }
        }
        if (R.Pit == 1){
            for (int j=0; j<R.Rows_Tab[i].Seat_Number;j++){
                switch(R.Rows_Tab[i].Seat_Tab[j]){
                    case 0 :    couleurS("0",VerfiCat(R.Rows_Tab[i])); printf(" ");break;
                    case 1 :    couleurS("X","31"); printf(" ");break;
                    case 2 :    printf(" ");break;
                    default :   printf(" ");break;
                }
            }
        }
    }
}
















void Menu(int Input, int VInput, Show* List_Of_Planned_Shows){
    int Code;
    int VInput2 = 0;
    printf("\nMenu - Sélectionnez le mode dans lequel vous voulez entrer :  \n0 - Quitter le programme\n1 - Accéder au mode Manager pour gérer le site\n2 - Accéder au mode festivalier pour réserver des places\n");

    while (VInput==0){
        VInput=((scanf("%d",&Input)) && (Input>=0) && (Input<=2) && (getchar()=='\n'));

        if (VInput==0){
            printf("\nErreur de saisie.\nChoisissez un terme valide : ");
            while (getchar()!='\n');
        }
    }
    switch(Input){
        case 0 :    exit(0);break;                                                 //Mettre plus tard le save ici
        case 1 :    printf("\nEntrez le code Manager pour accéder à la gestion du site : ");
                    while (VInput2==0){
                        VInput2=((scanf("%d",&Code)) && (Code == 5680) && (getchar()=='\n'));
                        if (VInput2==0){
                            printf("\nMauvais code.\nEntrez à nouveau : ");
                            while (getchar()!='\n');
                        }
                    }
                    create_Show();break;
        case 2 :    printf("\nVoici la liste des concerts déjà prévus : \n");
                    User_Reserve_Seats(List_Of_Planned_Shows, 3);break;
        default :   break;
    }
}



int main() {
    int Input;
    int VInput = 0 ;
    Show* List_Of_Planned_Shows = calloc(3 , sizeof(Show));                         //Remplacer par la fonction qui importe les structures

    printf("\nBienvenue ! Vous êtes dans GE500 le gestionnaire de concerts le plus efficace !\n");
    while(1){Menu(Input,VInput,List_Of_Planned_Shows);}
   
    return 0;

}
