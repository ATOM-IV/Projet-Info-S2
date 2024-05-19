#include "Fonctions.h"

int couleurS(char pr, char para){
    couleur("0");
    couleur("%s", para);
    printf("%s",pr);
    couleur("0");
    return 0;
}

int main(){
    couleur("0");
    couleur("1;36");
    printf("Test");
    couleur("0");
    return 0;
}
