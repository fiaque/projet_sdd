#ifndef __RESEAU_H__
#define __RESEAU_H__
#include "Chaine.h"

typedef struct noeud Noeud;

/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des voisins de chaque noeud) */
typedef struct cellnoeud {
    Noeud *nd;               /* Pointeur vers le noeud stock\'e */
    struct cellnoeud *suiv;         /* Cellule suivante dans la liste */
} CellNoeud;

/* Noeud du reseau */
struct noeud{
   int num;                        /* Numero du noeud */
   double x, y;                    /* Coordonnees du noeud*/
   CellNoeud *voisins;             /* Liste des voisins du noeud */
};

/* Liste chainee de commodites */
typedef struct cellCommodite {
    Noeud *extrA, *extrB;       /* Noeuds aux extremites de la commodite */
    struct cellCommodite *suiv;     /* Cellule suivante dans la liste */
} CellCommodite;

/* Un reseau */
typedef struct {
    int nbNoeuds;                   /* Nombre de noeuds du reseau */
    int gamma;                      /* Nombre maximal de fibres par cable */
    CellNoeud *noeuds;              /* Liste des noeuds du reseau */
    CellCommodite *commodites;      /* Liste des commodites a relier */
} Reseau;

Reseau * creerReseau(int gamma);
Noeud * creerNoeud(double x, double y, int n);
CellNoeud * creerCellNoeud(Noeud * nd);
CellNoeud* ajouterNoeud(CellNoeud *cell, Noeud * newnd);
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);
Reseau* reconstitueReseauListe(Chaines *C);
int nbCommodites(Reseau * R);
int existeNoeud(CellNoeud * cell, CellNoeud * noeud);
int nbLiaisons(Reseau * R);
void libererNoeud(Noeud *n);
void libererCellNoeud(CellNoeud *cn);
void libererCellComodite(CellCommodite *cc);
void libererReseau(Reseau *r);
int estVoisin(Noeud * noeud, CellNoeud * voisins);
void ajouterVoisin(Noeud* n, Noeud* voisin);
CellCommodite * ajouterCommodite(CellCommodite * cell, Noeud * a, Noeud * b);
void ecrireReseau(Reseau *R, FILE *f);
char * changerExt(char * old, char * newext);
void afficheReseauSVG(Reseau *R, char* nomInstance);



#endif

