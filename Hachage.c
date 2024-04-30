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

Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y){

    /*CALCUL DE L'INDICE DE LA TABLE DE HASHAGE*/
    double c=cle(x,y);
    int indice=h(c, H->tailleMax);

    /*RECUPERATION DE LA CASE CORRESPONDANTE*/
    CellNoeud *currcellnoeud=H->T[indice];
    Noeud *noeud;

    /*CAS OU LA CASE EST VIDE*/
    if(currcellnoeud==NULL){

        noeud=rechercheCreeNoeudListe(R, x, y); // On utilise rechercheCreeNoeudListe de Reseau.c pour créer le noeud 

        /*CREATTION DE LA CASE POUR TABLE*/
        CellNoeud *cellnoeud=(CellNoeud*)malloc(sizeof(CellNoeud));
        cellnoeud->nd=noeud; 
        cellnoeud->suiv=NULL;

        /*AFFECTATION DE LA CASE DANS LA TABLE*/
        H->T[indice]=cellnoeud;
        H->nbElement++;

        return noeud; // On retourne le nouveau noeud
    }

    /*CAS OU LA CASE N'EST PAS VIDE*/
    noeud=currcellnoeud->nd; // On récupère le noeud en tête de liste

    /*ON TEST POUR LE PREMIER NOEUD*/
    if (fabs(noeud->x - x)<0.001 && fabs(noeud->y - y)<0.001){ // On test l'egalite des coordonnees (double) avec la fabs (qui retourne la valeur absolue d'un double) et un epsilone à 0.001
            
            /*CAS OU LE PREMIER NOEUD EST CELUI QU'ON CHERCHE*/
            return noeud; // On quitte la fonction en revoyant le premier noeud
        } 

    /*ON TEST POUR LE RESTE DES NOEUDS DE LA CASE*/
    while(currcellnoeud->suiv){

        noeud=currcellnoeud->suiv->nd; // On récupère le noeud suivant

        if(fabs(noeud->x - x)<0.001 && fabs(noeud->y - y)<0.001){ // On test l'egalite des coordonnees

            return noeud;// On quitte la fonction en revoyant le noeud s'il s'agit de celui qu'on cherche
        }

        currcellnoeud=currcellnoeud->suiv; // On passe au noeud suivant
    }

    /*LE NOEUD RECHERCHE N'EST PAS DANS LA TABLE*/
    noeud=rechercheCreeNoeudListe(R, x, y); // On utilise rechercheCreeNoeudListe de Reseau.c pour créer le noeud 

    /*CREATION DU CELLNOEUD SUIVANT A PARTIR DU NOUVEAU NOEUD*/
    CellNoeud *cellnoeud=(CellNoeud*)malloc(sizeof(CellNoeud));
    cellnoeud->nd=noeud; 
    cellnoeud->suiv=NULL;

    /*AFFECTATION DU NOUVEAU NOEUD EN FIN DE CHAINE*/
    currcellnoeud->suiv=cellnoeud;
    H->nbElement++;

    return noeud; // On retourne le nouveau noeud
}

Reseau* reconstitueReseauHachage(Chaines *C, int M){

    TableHachage *H=(TableHachage*)malloc(sizeof(TableHachage));
    H->nbElement=0;
    H->tailleMax=M;
    H->T=(CellNoeud**)malloc(M*sizeof(CellNoeud*));
    for(int i=0;i<M;i++){
        H->T[i]=(CellNoeud*)malloc(sizeof(CellNoeud*));
        H->T[i]=NULL;
    }

    /*Reseau *R=(Reseau*)malloc(sizeof(Reseau));
    R->gamma=C->gamma;
    R->nbNoeuds=0;
    R->noeuds=NULL;*/

    /*INITIALISATION DES POINTEURS DE PARCOURS ET VARIABLES D'INSTANCIATIONS*/
    /*CellPoint *cellPoint; //Pointeur de parcours de la liste chainee des Points
    CellChaine *cellChaine=C->chaines; //Récuperation de la première chaine

    Noeud *noeud; // Pour les nouveaux noeuds
    Noeud *noeudprec=NULL;

    CellCommodite *currcellcommodite=NULL; // Pour les nouvelles Commodites
    CellCommodite *cellcommodite;
    Noeud *extrA; // Pour les noeuds des nouvelles Commodites
    Noeud *extrB;*/

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

void libererTableHash(TableHachage * T){

}