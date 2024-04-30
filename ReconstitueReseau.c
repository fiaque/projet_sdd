#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"

int main(int argc, char ** argv) {
    /* tests pour les fonctions creerReseau, RechercheCreerNoeudListe et ajouterCommodite
    Reseau * R= creerReseau(5);
    Noeud * nd;
    for (int j=0;j<6;j++){
        nd=rechercheCreeNoeudListe(R,j,j);
    }*/


    printf("debut\n");
    if (argc != 3) {
        printf("Utilisation : ./prog <Nom d'un fichier> <option>\n");
        exit(EXIT_FAILURE);
    }
    char* old = argv[1];
    char * res = changerExt(old, ".res");
    char * noext= changerExt(old,"");
    FILE * f1 = fopen(old,"r");
    if (!f1){
        fprintf(stderr,"Echec de l'ouverture du fichier %s\n",old);
        exit(EXIT_FAILURE);
    }
    Chaines * c=lectureChaines(f1);
    fclose(f1);
    printf("fichier fermé\n");
    Reseau * r;



    if (atoi(argv[2]) ==1){
        r= reconstitueReseauListe(c);
        printf("La reconstitution du réseau est terminée :)\n");
    }


    if (atoi(argv[2]) ==2){
        int  t;
        printf("Entrer la taille de la table de hachage");
        scanf("%d",&t);
        r= reconstitueReseauHachage(c,t);
    }


    if (atoi(argv[2]) ==3){

        r= reconstitueReseauArbre(c);
        printf("La reconstitution du réseau avec les arbres quaternaires est terminée :)\n");


    }
    printf("Le reseau contient %d liaisons\n", nbLiaisons(r));
    printf("Le reseau contient %d commodites\n", nbCommodites(r));


    FILE * f2= fopen(res, "w");
    if(!f2){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", res);
        exit(EXIT_FAILURE);
    }
    ecrireReseau(r, f2);
    fclose(f2);
    printf("L'écriture du fichier %s est finie\n", res);
    afficheReseauSVG(r,noext);

    free(res);
    libererChaine(c);
    libererReseau(r);
    return 1;


}