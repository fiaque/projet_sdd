#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include "Reseau.h"

typedef struct{
  int nbElement; //pas necessaire ici
  int tailleMax;
  CellNoeud** T;
} TableHachage ;

/*Retoune une cle à partir des coordonnes de deux points*/
double cle(double x, double y);

/*Retourne une cle de hashage a partir d'une cle k*/
int h(double k, int M);

/*Retourne un Noeud du réseau R correspondant au point (x, y) dans la table de hashage R (ou le crée)*/
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);

/*Retourne le réseau R à partir de la liste des chaînes C et en utilisant une table de hachage H de taille M*/
Reseau* reconstitueReseauHachage(Chaines *C, int M);

#endif
