#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"
#include "SVGwriter.h"

int main(int argc, char** argv){

    if (argc != 2) {
        printf("Utilisation : ./prog <Nom d'un fichier>\n");
        exit(EXIT_FAILURE);
    }
    char* old = argv[1];
    char * new_name = malloc(sizeof(old)+5);
    strcpy(new_name, "new_");
    strcat(new_name, old);
    FILE * f1 = fopen(old,"r");
    if (!f1){
        fprintf(stderr,"Echec de l'ouverture du fichier %s\n",old);
        exit(EXIT_FAILURE);
    }
    Chaines * c=lectureChaines(f1);
    fclose(f1);

    FILE * f2= fopen(new_name,"w");
    if(!f2){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", new_name);
        exit(EXIT_FAILURE);
    }
    ecrireChaines(c, f2);
    fclose(f2);
    printf("L'écriture du fichier %s est finie\n", new_name);
    free(new_name);
    afficheChainesSVG(c,"00014burma");

    printf("La longeur de la chaine 00014burma est %lf\n", longueurTotale(c));
    printf("Le nombre de points dans cette chaine est %d\n", comptePointsTotal(c));
    libererChaine(c);
    return 1;


}
