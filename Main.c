#include "Fonctions.h"

int couleurS(char pr, char para){
    couleur("0");
    couleur(para);
    printf("%s",pr);
    couleur("0");
    return 0;
}

int main() {

    char Mode;

    Show* List_Of_Planned_Shows = calloc(3 , sizeof(Show));
    
    User_Reserve_Seats(List_Of_Planned_Shows, 3);

    create_Show();

    return 0;

}
