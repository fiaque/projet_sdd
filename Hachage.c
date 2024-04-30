#include "Hachage.h"
#include "Reseau.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*==================================EXERCICE 4==================================*/

double cle(double x, double y){
    return y+(x + y)*(x + y + 1)/2;
}

int h(double k, int M){
    float A=(sqrt(5)-1)/2;
    // printf('%d',(floor(M*(k*A-floor(k*A))))) ;
    return (floor(M*(k*A-floor(k*A))));
}

Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y) {

    /*CALCUL DE L'INDICE DE LA TABLE DE HASHAGE*/
    double c = cle(x, y);
    int indice = h(c, H->tailleMax);

    /*RECUPERATION DE LA CASE CORRESPONDANTE*/
    CellNoeud *currcellnoeud = H->T[indice];
    Noeud *noeud;

    /*CAS OU LA CASE EST VIDE*/
    if (!currcellnoeud) {
        R->nbNoeuds++;
        Noeud *new = creerNoeud(x, y, R->nbNoeuds);
        ajouterNoeud(R->noeuds, new);

        CellNoeud *cellnoeud = (CellNoeud *) malloc(sizeof(CellNoeud));
        cellnoeud->nd = noeud;
        cellnoeud->suiv = NULL;

        //on ajoute la case dans la table
        H->T[indice] = cellnoeud;
        H->nbElement++;

        return noeud; // On retourne le nouveau noeud
    }else{
        CellNoeud *precCellnoeud = NULL;
        while (currcellnoeud) {
            if (currcellnoeud->nd->x == x && currcellnoeud->nd->y) {
                return currcellnoeud->nd;
            }
            precCellnoeud = currcellnoeud;
            currcellnoeud = currcellnoeud->suiv;
        }

        //si on est arrivé a la fin de la boucle alors le noeud n'exsite pas
        Noeud *new = creerNoeud(x, y, ++R->nbNoeuds);
        ajouterNoeud(R->noeuds, new);
        CellNoeud *cellnoeud = (CellNoeud *) malloc(sizeof(CellNoeud));
        cellnoeud->nd = noeud;
        cellnoeud->suiv = NULL;
        precCellnoeud->suiv = cellnoeud;
        H->nbElement++;
        return new;
    }

    //cas ou la case n'est pas vide, on parcourt la liste chainee, si on trouve le noeud on le retourne, sinon on l'ajoute a la fin de la liste


}

Reseau* reconstitueReseauHachage(Chaines *C, int M){

    TableHachage *H=(TableHachage*)malloc(sizeof(TableHachage));
    H->nbElement=0;
    H->tailleMax=M;
    H->T=(CellNoeud**)malloc(M*sizeof(CellNoeud*));
    if(!H->T){
        fprintf(stderr,"allocation de H->T a échoué");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<M;i++){
        H->T[i]=NULL;
    }

    Reseau * R= creerReseau(C->gamma);
    CellChaine * cc= C->chaines;
    Noeud * nd;
    Noeud * first;
    Noeud * prec;
    while (cc){
        nd= rechercheCreeNoeudHachage(R,H,cc->points->x,cc->points->y);
        first=nd;
        prec=nd;
        cc->points=cc->points->suiv;
        while (cc->points){
            prec=nd;
            nd= rechercheCreeNoeudHachage(R,H, cc->points->x,cc->points->y);
            ajouterVoisin(nd, prec);
            ajouterVoisin(prec, nd);
            cc->points=cc->points->suiv;

        }
        R->commodites= ajouterCommodite(R->commodites,first,prec);
        cc=cc->suiv;
    }
    return R;
}
