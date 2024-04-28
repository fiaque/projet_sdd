#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include <math.h>
#include "SVGwriter.h"

Reseau * creerReseau(int gamma) {
    Reseau *R = malloc(sizeof(Reseau));
    R->gamma = gamma;
    R->nbNoeuds = 0;
    R->noeuds=NULL;
    R->commodites=NULL;
    return R;
}

Noeud * creerNoeud(double x, double y, int n){
    Noeud * nd= malloc(sizeof(Noeud));
    nd->x=x;
    nd->y=y;
    nd->num=n;
    nd->voisins=NULL;
    return nd;
}

CellNoeud * creerCellNoeud(Noeud * nd){
    CellNoeud * ncell= malloc(sizeof(CellNoeud));
    ncell->nd=nd;
    ncell->suiv=NULL;
    return ncell;
}


CellNoeud* ajouterNoeud(CellNoeud *cell, Noeud * newnd){
    CellNoeud * ncell= creerCellNoeud(newnd);
    ncell->suiv = cell;
    cell = ncell;
    return cell;
}
CellCommodite * creerCommodite(Noeud * a, Noeud *b){
    CellCommodite * newc= malloc(sizeof(CellCommodite));
    newc->extrA=a;
    newc->extrB=b;
    return newc;
}

CellCommodite * ajouterCommodite(CellCommodite * cell, Noeud * a, Noeud * b){
    CellCommodite * newc= creerCommodite(a,b);
    newc->suiv=cell;
    cell=newc;
    return cell;
}

/*Cette fonction retourne le noeud x et y s'il existe sinon la fonction le construit et l'ajoute dans le reseau*/
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    CellNoeud* cn = R->noeuds; //on récupère la liste CellNoeud

    while(cn!=NULL){ //On parcourt cette liste
        Noeud* noe = cn -> nd;
        if(noe->x == x && noe->y == y){ //On regarde s'il y a un noeud qui a les mêmes coordonnées x y.
            return noe;
        }
        cn = cn->suiv;
    }

    //Création du noeud
    R->nbNoeuds++;
    Noeud* new_noeud = creerNoeud(x,y,R->nbNoeuds);

    //Ajout dans le réseau
    R->noeuds = ajouterNoeud(R->noeuds, new_noeud);
    return new_noeud;

}

void ajouterVoisin(Noeud* n, Noeud* voisin){
    CellNoeud * v=n->voisins;
    while(v){
        if (v->nd->x==voisin->x && v->nd->y==voisin->y){
            return ;
        }
        v=v->suiv;
    }
    n->voisins= ajouterNoeud(n->voisins, voisin);
}

Reseau* reconstitueReseauListe(Chaines *C){
    Reseau * R= creerReseau(C->gamma);
    CellChaine * cc= C->chaines;
    CellPoint * cp= C->chaines->points;
    Noeud * nd;
    Noeud * first;
    Noeud * prec;
    while (cc){
        nd= rechercheCreeNoeudListe(R,cc->points->x,cc->points->y);
        first=nd;
        prec=nd;
        cc->points=cc->points->suiv;
        while (cc->points){
            prec=nd;
            nd= rechercheCreeNoeudListe(R, cc->points->x,cc->points->y);
            ajouterVoisin(nd, prec);
            ajouterVoisin(prec, nd);
            cc->points=cc->points->suiv;

        }
        R->commodites= ajouterCommodite(R->commodites,first,prec);
        cc=cc->suiv;
    }
    return R;

}

int nbCommodites(Reseau * R){
    int res=0;
    CellCommodite * cell=R->commodites;
    while (cell){
        res++;
        cell=cell->suiv;
    }
    free(cell);
    return res;
}

int existeNoeud(CellNoeud * cell, CellNoeud * noeud){
    //cette fonction retourne 1 si le noeud est présent, 0 sinon
    while (cell){
        if (cell->nd->x==noeud->nd->x && cell->nd->y==noeud->nd->y){
            return 1;
        }
        cell=cell->suiv;
    }
    return 0;
}
int nbLiaisons(Reseau * R){
    CellNoeud * cell= R->noeuds;
    CellNoeud * traites= NULL;
    CellNoeud * voisins;
    int res=0;
    while (cell){
        voisins= cell->nd->voisins;
        traites=ajouterNoeud(traites, cell->nd);
        while (voisins){
            if(!existeNoeud(traites,voisins)){
                res++;
            }
            voisins=voisins->suiv;

        }
        cell=cell->suiv;
    }
    free(voisins);
    free(cell);
    //CellNoeud * tmp;
    /*while(traites){
        tmp=traites->suiv;
        free(traites);
        traites=traites->suiv;

    }
    free(tmp);*/
    return res;
}

void ecrireReseau(Reseau *R, FILE *f){
    int nb_noeuds = R->nbNoeuds;
    fprintf(f,"NbNoeuds: %d\n",nb_noeuds);

    int nb_liaisons = nbLiaisons(R);
    fprintf(f,"NbLiaisons: %d\n",nb_liaisons);

    int nb_com = nbCommodites(R);
    fprintf(f,"NbCommodites: %d\n",nb_com);

    int gamma = R->gamma;
    fprintf(f,"Gamma: %d\n",gamma);

    fprintf(f,"\n");

    //écriture des noeuds dans le fichier (ligne 6 à 17 voir énoncé).
    CellNoeud* cell_n = R->noeuds;

    while(cell_n != NULL){
        Noeud* n = cell_n->nd;
        fprintf(f,"v %d %.6f %.6f\n",n->num,n->x,n->y);
        cell_n = cell_n->suiv;
    }

    fprintf(f,"\n");

    //écriture des liaisons
    CellNoeud* cell_n_l = R->noeuds;
    while(cell_n_l != NULL){
        Noeud* n_l = cell_n_l->nd;
        CellNoeud* voisins = n_l->voisins;

        while(voisins != NULL){
            if(n_l->num > voisins->nd->num){
                fprintf(f,"l %d %d\n",voisins->nd->num,n_l->num);
            }
            voisins = voisins->suiv;
        }
        cell_n_l = cell_n_l->suiv;
    }

    fprintf(f,"\n");

    //écriture des commodités
    CellCommodite *cell_c = R->commodites;
    while(cell_c != NULL){
        fprintf(f,"k %d %d\n",cell_c->extrA->num,cell_c->extrB->num);
        cell_c = cell_c->suiv;
    }
}
void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}


void libererNoeud(Noeud *n){
    CellNoeud* courant;
    while(n->voisins){
        courant = n->voisins;
        n->voisins = n->voisins->suiv;
        free(courant);
    }
    free(n);
}

void libererCellNoeud(CellNoeud *cn){
    CellNoeud *tmp = NULL;
    while(cn){
        tmp = cn->suiv;
        libererNoeud(cn->nd);
        free(cn);
        cn = tmp;
    }
}


void libererCellComodite(CellCommodite *cc){
    CellCommodite *tmp = NULL;
    while(cc){
        tmp = cc->suiv;
        free(cc);
        cc = tmp;
    }
}


void libererReseau(Reseau *r){
    libererCellNoeud(r->noeuds);
    libererCellComodite(r->commodites);
    free(r);
}
