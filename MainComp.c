#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"
#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include <time.h>


int main(int argc, char** argv){
    int nbPoint=100;
    int xmax=500;
    int ymax=500;
    clock_t debut, fin;
    Chaines * C;
    Reseau * R;


    int i;
    /*char* stat1 ="testChaine";
    FILE * f1=fopen(stat1,"w");
    if (!f1){
        fprintf(stderr,"erreur d'ouverture du fichier %s\n",stat1);
        exit(EXIT_FAILURE);
    }
     for (i=50;i<=500;i+=50){
        C=generationAleatoire(i,nbPoint,xmax,ymax);
        debut = clock();
        R=reconstitueReseauListe(C);
        fin = clock();
        fprintf(f1,"%d %f\n",i,(double)(fin-debut)/CLOCKS_PER_SEC);
    }
    fclose(f1);*/

    char * stat2= "testHach_arbre";
    FILE * f2=fopen(stat2,"w");

    if (!f2){
        fprintf(stderr,"erreur d'ouverture du fichier %s\n",stat2);
        exit(EXIT_FAILURE);
    }
    int j,k;
    long double tab[7];
    for (k=50;k<=500;k+=50){
        C=generationAleatoire(k,nbPoint,xmax,ymax);
        afficheChainesSVG(C,"aleabis");

        debut = clock();
        R=reconstitueReseauArbre(C);
        fin = clock();
        afficheReseauSVG(R,"aleabisres");
        tab[6]= (long double)(fin-debut)/CLOCKS_PER_SEC;
        fprintf(f2,"%d %Lf\n",k,tab[6]);
        for(j=0;j<5;j++){
            debut = clock();
            Reseau * R1=reconstitueReseauHachage(C,(j+5)*5);
            fin = clock();
            tab[j]=(fin-debut)/CLOCKS_PER_SEC;
            libererReseau(R1);
        }
    }

    fclose(f2);
    libererChaine(C);
    libererReseau(R);
    return 1;
}
