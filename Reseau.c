#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"

Noeud* creernoeud(double x, double y, int n){
    //cette fonction crée un noeud numero n avec des coordonnées x et y
    Noeud* new = malloc(sizeof (Noeud));
    new->num=n;
    new->x=x;
    new->y=y;
    new->voisins=NULL;
    return new;
}
void majVoisins(Noeud *a, Noeud *b){
    //cette fonction ajoute le noeud a(resp b) a la liste des voisins du noeud b(resp a)
    CellNoeud * voisinA= a->voisins;
    CellNoeud * voisinB= b->voisins;
    CellNoeud * newA= malloc(sizeof(CellNoeud));
    CellNoeud * newB= malloc(sizeof(CellNoeud));
    newA->nd=b;
    newA->suiv=voisinA;
    newB->nd=a;
    newB->suiv=voisinB;
    a->voisins=newA;
    b->voisins=newB;
}

CellNoeud * ajouterNoeud(CellNoeud * cell, Noeud * n){
    CellNoeud * new= malloc(sizeof(CellNoeud));
    CellNoeud * tmp= cell;
    new->nd=n;
    new->suiv=tmp;
    cell=new;
    return cell;

}

/*créer noeud liste omg:
 * Créer une fonction Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);
qui retourne un Noeud du réseau R correspondant au point (x, y) dans la liste chaı̂née noeuds de R.
Noter que si ce point existe dans noeuds, la fonction retourne un nœud existant dans noeuds et que,
dans le cas contraire, la fonction crée un nœud et l’ajoute dans la liste des nœuds du réseau de R. Le
numéro d’un nouveau nœud est simplement choisi en prenant le nombre nbNoeuds+1 (just’avant de
mettre à jour à la valeur nbNoeuds)*/

Noeud * rechercheCreerNoeudListe(Reseau *R, double x, double y){

}

/*
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    CellNoeud  * n= R->noeuds;
    CellNoeud * npred=n;
    Noeud * r=NULL;
    CellNoeud * tmp;
    while(n){
        if(n->nd->x==x && n->nd->y==y){
            r=n->nd;
            break;
        }
        npred=n;
        n=n-> suiv;
    }

    if(!npred){
        npred=malloc(sizeof(CellNoeud));
        r=malloc(sizeof(Noeud));
        r->x=x;
        r->y=y;
        r->num= R->nbNoeuds+1;
        R->nbNoeuds++;
        tmp=npred;
        npred->nd=r;
        npred->suiv=tmp;
    }

    return r;
}
 */

Reseau* reconstitueReseauListe(Chaines *C){
    Reseau * r= (Reseau *) malloc (sizeof (Reseau));
    r->gamma= C->gamma;
    r->nbNoeuds=0;
    r->noeuds=NULL;
    r->commodites=NULL;
    CellCommodite * tmpc;
    CellChaine * cell =C->chaines;
    CellPoint * p, *pred;
    CellNoeud * tmp;
    Noeud * n, * npred=NULL ;
    while(cell){
        p=cell->points;
        tmpc=r->commodites;
        r->commodites= malloc(sizeof(CellCommodite));
        r->commodites->extrA= rechercheCreeNoeudListe(r,p->x,p->y);
        while(p){
            n=rechercheCreeNoeudListe(r,p->x,p->y);
            if (pred){ //mise a jour des voisins
                npred = rechercheCreeNoeudListe(r, pred->x, pred->y);
                tmp=n->voisins;
                n->voisins=malloc(sizeof (CellNoeud));
                n->voisins->nd= npred;
                n->voisins->suiv=tmp;
                tmp= npred->voisins;
                npred->voisins=malloc(sizeof (CellNoeud));
                npred->voisins->nd= n;
                npred->voisins->suiv=tmp;
            }
            pred=p;
            p=p->suiv;
        }
        r->commodites->extrB= rechercheCreeNoeudListe(r,pred->x,pred->y);
        r->commodites->suiv=tmpc;
        cell=cell->suiv;
    }
    return r;
}
int nbLiaisons(Reseau *R){
    CellNoeud * traite, *voisin, *tmp;
    CellNoeud * traiteInit=NULL;
    CellNoeud * noeud= R->noeuds;
    int res=0;
    // on se place dans le premier noeud, on compte toutes ses liaisons et on ajoute le premier noeud dans la liste traite
    while (noeud){
        voisin=noeud->nd->voisins;
        tmp=traiteInit;
        traiteInit=malloc(sizeof(CellNoeud));
        traiteInit->nd=noeud->nd;
        traiteInit->suiv=tmp;
        traite=traiteInit;
        while(voisin){
            //ici on vérifie que dans la liste des voisins on n'a pas de neouds déja traités
            while(traite &&!(voisin->nd->x==traite->nd->x && traite->nd->y==traite->nd->y )){
                traite=traite->suiv;
            }
            if(!traite){
                res++;
            }
            voisin=voisin->suiv;
        }
        noeud=noeud->suiv;

    }
    return res;
}
void libererVoisins(Noeud * nd){
    CellNoeud * voisin= nd->voisins;
    CellNoeud * tmp;
    while(voisin){
        tmp=voisin->suiv;
        voisin=voisin->suiv;
        free(tmp);
    }
    free(voisin);
}

void libererCellNoeud(CellNoeud * n){
    CellNoeud * tmp;
    while (n){
        tmp=n;
        n=n->suiv;
        libererVoisins(tmp->nd);
        free(tmp->nd);
    }
}
void libererCommodites(CellCommodite * c){
    CellCommodite * tmp;
    while (c){
        tmp = c;
        c=c->suiv;
        free(c->extrA);
        free(c->extrB);
        free(tmp);

    }
    free(c);
}
void libererReseau(Reseau * r){
  libererCommodites(r->commodites);
   libererCellNoeud(r->noeuds);
    free(r);
}
