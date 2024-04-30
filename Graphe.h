
# ifndef __GRAPHE_H__
# define __GRAPHE_H__
# include <stdlib.h>
# include <stdio.h>
#include "Reseau.h"

typedef struct {
    int u , v ; /* Numeros des sommets extremite */
} Arete ;

typedef struct cellule_arete {
    Arete * a ;/* pointeur sur l’arete */
    struct cellule_arete * suiv ;
} Cellule_arete ;

typedef struct {
    int num ;/* Numero du sommet (le meme que dans T_som) */
    double x , y ;
    Cellule_arete * L_voisin ; /* Liste chainee des voisins */
} Sommet ;

typedef struct {
    int e1 , e2 ;/* Les deux extremites de la commodite */
} Commod ;

typedef struct {
    int nbsom ; /* Nombre de sommets */
    Sommet ** T_som ; /* Tableau de pointeurs sur sommets */
    int gamma ;
    int nbcommod ; /* Nombre de commodites */
    Commod * T_commod ; /* Tableau des commodites */
} Graphe ;

Graphe * alloueGraphe(int nbsom, int gamma, int nbcomm);
Graphe *creerGraphe(Reseau *r);
int cheminMinimal(Graphe *g, int u,int v);
void liberer_arete(Cellule_arete *CA);
void liberer_graphe(Graphe *g);

# endif
