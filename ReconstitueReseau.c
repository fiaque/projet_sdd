#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Reseau.h"

int main(int argc, char ** argv){
    printf("debut\n");
    if (argc != 3) {
        printf("Utilisation : ./prog <Nom d'un fichier> <option>\n");
        exit(EXIT_FAILURE);
    }
    if (atoi(argv[2]) ==1){
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
        printf("fichier fermé\n");

        Reseau * r= reconstitueReseauListe(c);
        printf("La reconstitution du réseau est terminée :)\n");
        printf("Il y a %d liaisons dans ce réseau\n", nbLiaisons(r));
        libererChaine(c);
        free(new_name);

    }

    return 1;
}