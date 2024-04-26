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
    return new;
}

Noeud * rechercherCellNoeud(CellNoeud * cell, double x, double y){
    CellNoeud * parc=cell;
    while(parc && parc->nd->x!=x && parc->nd->y!=y){
        parc=parc->suiv;
    }
    Noeud * n = parc ? parc->nd : NULL;
    return n;
}


Noeud * rechercheCreeNoeudListe(Reseau *R, double x, double y){
    //on suppose ici que le réseau est bien alloué et que les champs gamma et nbnoeuds sont bien initialisés
    if (R){
        Noeud * existe= rechercherCellNoeud(R->noeuds,x,y);
        if (!existe){ //si le noeud n'existait pas on le crée et on l'ajoute
            R->nbNoeuds++;
            existe= creernoeud(x,y,R->nbNoeuds);
            ajouterNoeud(R->noeuds,existe);
        }
        return existe;
    }
    return NULL;
}

/* version de la fonction sans fonctions auxiliaires(terrible) (faut pas)
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

/*Reseau* reconstitueReseauListe(Chaines *C){
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
*/
CellCommodite * creerCommodite(Noeud* a,Noeud* b){
    CellCommodite * c= malloc(sizeof(CellCommodite));
    c->extrA=a;
    c->extrB=b;
    return c;
}
CellCommodite * ajouterCommodite(CellCommodite* liste, Noeud* a, Noeud* b){
    CellCommodite * tmp= liste;
    CellCommodite * new= creerCommodite(a,b);
    new->suiv=tmp;
    return new;
}
/*On utilise un ensemble de nœuds V qui est initialisé vide: V ← ∅
On parcourt une à une chaque chaıne:
Pour chaque point p de la chaıne:
Si p 6∈ V (on teste si le point n’a pas déjà été rencontré auparavant)
On ajoute dans V un nœud correspond au point p.
On met à jour la liste des voisins de p et celles de ses voisins.
On conserve la commodité de la chaıne.*/

Reseau* reconstitueReseauListe(Chaines *C){
    if (!C){
        fprintf(stderr, "pointeur invalide");
        EXIT_FAILURE;
    }
    Reseau * R= malloc(sizeof(Reseau));
    R->nbNoeuds=0;
    R->gamma=C->gamma;
    R->noeuds=NULL;
    R->commodites=NULL;
    CellChaine* cell= C->chaines;
    while (cell){
        CellPoint * point= cell->points;
        Noeud * first= creernoeud(point->x,point->y,1);
        R->noeuds=ajouterNoeud(R->noeuds,first);
        Noeud * precedent=first;
        point=point->suiv;
        while (point){
            Noeud * existe= rechercherCellNoeud(R->noeuds, point->x, point->y);
            if (existe==NULL){
                R->nbNoeuds++;
                existe= creernoeud(point->x,point->y, R->nbNoeuds);
                ajouterNoeud(R->noeuds,existe);


            }
            majVoisins(existe,precedent);
            precedent=existe;
            point=point->suiv;

        }
        R->commodites=ajouterCommodite(R->commodites,first,precedent);
        cell=cell->suiv;
    }
    return R;
    //on a une liste de listes chainées
    //Il faut se mettre dans la grande liste, la parcourir et dans chaque parcours de la petite liste on garde le premier et dernier element
    //pour ajouter les noeuds on utilise recherche noeud et ajouter noeud, et pour mettre à jour on utilise la fonction majvoisins


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

