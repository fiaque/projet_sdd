#include "ArbreQuat.h"
#include "Chaine.h"
#include "Reseau.h"
#include <stdlib.h>
#include <math.h>

void chaineCoordMinMax(Chaines *c, double *xmin, double *ymin, double *xmax, double *ymax) {
    CellChaine *chaine = c->chaines;
    while (chaine) {
        CellPoint *point = chaine->points;
        while (point) {
            if (point->x < *xmin)
                *xmin = point->x;
            if (point->x > *xmax)
                *xmax = point->x;
            if (point->y < *ymin)
                *ymin = point->y;
            if (point->y > *ymax)
                *ymax = point->y;
            point = point->suiv;
        }
        chaine = chaine->suiv;
    }
}

ArbreQuat *creerArbreQuat(double xc, double yc, double coteX, double coteY) {
    ArbreQuat *arbre = (ArbreQuat *) malloc(sizeof(ArbreQuat));
    arbre->xc = xc;
    arbre->yc = yc;
    arbre->coteX = coteX;
    arbre->coteY = coteY;
    arbre->noeud = NULL;
    arbre->ne = NULL;
    arbre->no = NULL;
    arbre->se = NULL;
    arbre->so = NULL;
    return arbre;
}

void insererNoeudArbre(Noeud *n, ArbreQuat **a, ArbreQuat *parent) {
    if ((*a) == NULL) {
        double xc = parent->xc, yc = parent->yc;
        double coteX = parent->coteX, coteY = parent->coteY;

        if (n->x < xc) {
            if (n->y < yc) {
                *a = creerArbreQuat(xc - coteX / 4, yc - coteY / 4, coteX / 2, coteY / 2);
                parent->so = *a;
            } else {
                *a = creerArbreQuat(xc - coteX / 4, yc + coteY / 4, coteX / 2, coteY / 2);
                parent->no = *a;
            }
        } else {
            if (n->y < yc) {
                *a = creerArbreQuat(xc + coteX / 4, yc - coteY / 4, coteX / 2, coteY / 2);
                parent->se = *a;
            } else {
                *a = creerArbreQuat(xc + coteX / 4, yc + coteY / 4, coteX / 2, coteY / 2);
                parent->ne = *a;
            }
        }

        (*a)->noeud = n;

        return;
    }

    if ((*a)->noeud != NULL) {
        if ((*a)->noeud->x < (*a)->xc && (*a)->noeud->y < (*a)->yc)
            insererNoeudArbre((*a)->noeud, &((*a)->so), *a);
        if ((*a)->noeud->x >= (*a)->xc && (*a)->noeud->y < (*a)->yc)
            insererNoeudArbre((*a)->noeud, &((*a)->se), *a);
        if ((*a)->noeud->x < (*a)->xc && (*a)->noeud->y >= (*a)->yc)
            insererNoeudArbre((*a)->noeud, &((*a)->no), *a);
        if ((*a)->noeud->x >= (*a)->xc && (*a)->noeud->y >= (*a)->yc)
            insererNoeudArbre((*a)->noeud, &((*a)->ne), *a);

        (*a)->noeud = NULL;

        if (n->x < (*a)->xc && n->y < (*a)->yc)
            insererNoeudArbre(n, &((*a)->so), *a);
        if (n->x >= (*a)->xc && n->y < (*a)->yc)
            insererNoeudArbre(n, &((*a)->se), *a);
        if (n->x < (*a)->xc && n->y >= (*a)->yc)
            insererNoeudArbre(n, &((*a)->no), *a);
        if (n->x >= (*a)->xc && n->y >= (*a)->yc)
            insererNoeudArbre(n, &((*a)->ne), *a);

        return;
    }

    if ((*a)->noeud == NULL) {
        double xc = (*a)->xc;
        double yc = (*a)->yc;

        if (n->x < xc) {
            if (n->y < yc)
                insererNoeudArbre(n, &((*a)->so), *a);
            else
                insererNoeudArbre(n, &((*a)->no), *a);
        } else {
            if (n->y < yc)
                insererNoeudArbre(n, &((*a)->se), *a);
            else
                insererNoeudArbre(n, &((*a)->ne), *a);
        }
    }
}

Noeud *rechercheCreeNoeudArbre(Reseau *R, ArbreQuat **a, ArbreQuat *parent, double x, double y) {
    if (*a == NULL) {
        // création du noeud
        Noeud *n = malloc(sizeof(Noeud));
        n->x = x;
        n->y = y;
        n->num = R->nbNoeuds++;
        n->voisins = NULL;

        // création de la cellule et ajout en tête dans le réseau
        CellNoeud *newC = malloc(sizeof(CellNoeud));
        newC->nd = n;
        newC->suiv = R->noeuds;
        R->noeuds = newC;

        insererNoeudArbre(n, a, parent);
        return n;
    }

    if ((*a)->noeud != NULL) {
        Noeud *currentNode = (*a)->noeud;

        // si c'est le noeud en question on le retourne
        if (fabs(currentNode->x - x) <= 0.0001 && fabs(currentNode->y - y) <= 0.0001)
            return currentNode;

        // création du noeud
        Noeud *n = malloc(sizeof(Noeud));
        n->x = x;
        n->y = y;
        n->num = R->nbNoeuds++;
        n->voisins = NULL;

        // création de la cellule et ajout en tête dans le réseau
        CellNoeud *newC = malloc(sizeof(CellNoeud));
        newC->nd = n;
        newC->suiv = R->noeuds;
        R->noeuds = newC;

        insererNoeudArbre(n, a, parent);

        return n;
    }

    if ((*a)->noeud == NULL) {
        double xc = (*a)->xc;
        double yc = (*a)->yc;

        if (x < xc) {
            if (y < yc)
                rechercheCreeNoeudArbre(R, &((*a)->so), *a, x, y);
            else
                rechercheCreeNoeudArbre(R, &((*a)->no), *a, x, y);
        } else {
            if (y < yc)
                rechercheCreeNoeudArbre(R, &((*a)->se), *a, x, y);
            else
                rechercheCreeNoeudArbre(R, &((*a)->ne), *a, x, y);
        }
    }
}

Reseau *reconstitueReseauArbre(Chaines *C) {
    Reseau *R = (Reseau *) malloc(sizeof(Reseau));

    // création de l'arbre
    double xmin, ymin, xmax, ymax;
    chaineCoordMinMax(C, &xmin, &ymin, &xmax, &ymax);
    double coteX = xmax - xmin, coteY = ymax - ymin;
    ArbreQuat *arbre = creerArbreQuat(xmin + coteX / 2, ymin + coteY / 2, coteX, coteY);

    // comodité précédente pour les liées
    CellCommodite *cellComPrec = NULL;
    CellCommodite *cellCom = NULL;

    R->gamma = C->gamma;
    R->nbNoeuds = 1;
    R->noeuds = NULL;

    // liste de toute les chaînes
    CellChaine *cellC = C->chaines;
    while (cellC) {
        CellPoint *CurrentPoint = cellC->points;
        CellPoint *PrecPoint = NULL;

        while (CurrentPoint) {
            // noeud courant
            Noeud *CurrentNode = rechercheCreeNoeudArbre(R, &arbre, NULL, CurrentPoint->x, CurrentPoint->y);

            Noeud *PrecNode = NULL;
            Noeud *NextNode = NULL;

            CellPoint *NextPoint = CurrentPoint->suiv;

            // commodité
            // si on est au début de la chaîne (PrecPoint non encore initialisé)
            if (!PrecPoint) {
                cellCom = (CellCommodite *) malloc(sizeof(CellCommodite));
                cellCom->suiv = NULL;
                if (cellComPrec == NULL) {
                    R->commodites = cellCom;
                } else {
                    cellComPrec->suiv = cellCom;
                }
                cellCom->extrA = CurrentNode;
            }

            // si on est en fin de chaîne
            if (!NextPoint) {
                cellCom->extrB = CurrentNode;
                cellComPrec = cellCom;
            }

            // voisins

            // récupération des noeuds du point précédant et suivant du point courant
            if (PrecPoint) {
                PrecNode = rechercheCreeNoeudArbre(R, &arbre, NULL, PrecPoint->x, PrecPoint->y);
                int Voisin = estVoisin(PrecNode, CurrentNode->voisins);
                if (!Voisin) {
                    // mise à jour des voisins du noeud courant
                    CellNoeud *NewVoisinForCurrent = malloc(sizeof(CellNoeud));
                    NewVoisinForCurrent->nd = PrecNode;
                    NewVoisinForCurrent->suiv = CurrentNode->voisins;
                    CurrentNode->voisins = NewVoisinForCurrent;

                    // mise à jour du noeud précédent
                    CellNoeud *NewVoisinForPrec = malloc(sizeof(CellNoeud));
                    NewVoisinForPrec->nd = CurrentNode;
                    NewVoisinForPrec->suiv = PrecNode->voisins;
                    PrecNode->voisins = NewVoisinForPrec;
                }
            }
            if (NextPoint) {
                NextNode = rechercheCreeNoeudArbre(R, &arbre, NULL, NextPoint->x, NextPoint->y);
                int Voisin = estVoisin(NextNode, CurrentNode->voisins);
                if (!Voisin) {
                    // mise à jour des voisins du noeud courant
                    CellNoeud *NewVoisinForCurrent = malloc(sizeof(CellNoeud));
                    NewVoisinForCurrent->nd = NextNode;
                    NewVoisinForCurrent->suiv = CurrentNode->voisins;
                    CurrentNode->voisins = NewVoisinForCurrent;

                    // mise à jour du noeud suivant
                    CellNoeud *NewVoisinForNext = malloc(sizeof(CellNoeud));
                    NewVoisinForNext->nd = CurrentNode;
                    NewVoisinForNext->suiv = NextNode->voisins;
                    NextNode->voisins = NewVoisinForNext;
                }
            }

            PrecPoint = CurrentPoint;
            CurrentPoint = CurrentPoint->suiv;
        }

        cellC = cellC->suiv;
    }
    libererArbre(arbre);
    return R;
}

void libererArbre(ArbreQuat * a){
    if(a) {
        if ((!a->ne) && (!a->no) && (!a->se) && (!a->so)) {
            free(a);
        } else {
            libererArbre(a->ne);
            libererArbre(a->no);
            libererArbre(a->ne);
            libererArbre(a->so);
        }
    }
}