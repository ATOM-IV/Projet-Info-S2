#include "Fonctions.h"

int couleurS(char pr, char para){
    couleur("0");
    couleur(para);
    printf("%s",pr);
    couleur("0");
    return 0;
}

void Menu(int Input,int VInput,Show* List_Of_Planned_Shows){
    printf("\nMenu - Sélectionnez le mode dans lequel vous voulez entrer :  \n0 - Quitter le programme\n1 - Accéder au mode Manager pour gérer le site\n2 - Accéder au mode festivalier pour réserver des places\n");

    while (VInput==0){
        VInput=((scanf("%d",&Input)) && (Input>=0) && (Input<=2) && (getchar()=='\n'));

        if (VInput==0){
            printf("\nErreur : Choisissez un terme valide : ");
            while (getchar()!='\n');
        }
    }
    switch(Input){
        case 0 :    exit(0);break;                                                 //Mettre plus tard le save ici
        case 1 :    create_Show();break;
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
