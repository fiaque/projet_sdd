#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Chaine.h"
#include "SVGwriter.h"

Chaines *lectureChaines(FILE *f) {
    Chaines *c = malloc(sizeof(Chaines));
    c->chaines = NULL;

    //fscanf(f,"Nb Chain: %d",&c->nbChaines); //on recupere le nombre de chaines
    //fscanf(f,"Gamma: %d",&c->gamma); //on recupere le gamma
    int i;
    char *buffer = malloc(sizeof(char) * 257);
    char * initial_buffer = buffer;
    int nb;
    int j;
    fgets(buffer, 257 * sizeof(char), f);
    sscanf(buffer, "NbChain: %d", &c->nbChaines);
    fgets(buffer, 257 * sizeof(char), f);
    sscanf(buffer, "Gamma: %d", &c->gamma);

    CellChaine *cell;
    CellChaine *tmpc;

    for (i = 0; i < c->nbChaines; i++) { //on lit autant de lignes qu'il y a de chaines
        cell = malloc(sizeof (CellChaine));
        tmpc = c->chaines;
        buffer=initial_buffer;
        fgets(buffer, 257 * sizeof(char), f);//on met la ligne dans un buffer
        //printf("buffer: %s", buffer);
        int n;
        sscanf(buffer, "%d %d%n", &cell->numero, &nb, &n);//on recupere le nb de fibres et le nb de points
        //printf("numero: %d, nb:%d\n", cell->numero, nb);
        buffer+=n;
        cell->points = NULL;//on alloue la liste des points
        CellPoint *tmp;
        for (j = 0; j < nb; j++) {
            CellPoint *p = (CellPoint *) malloc(sizeof(CellPoint));
            tmp = cell->points;
            sscanf(buffer, "%lf %lf%n", &p->x, &p->y, &n);

            buffer += n;
            cell->points = p;
            p->suiv = tmp;
        }
        c->chaines=cell;
        cell->suiv=tmpc;


    }
    free(initial_buffer);
    return c;
}
void libererPoints(CellPoint * p){
    CellPoint * tmp;
    while(p){
        tmp=p;
        p=p->suiv;
        free(tmp);
    }
}
void libererCell(CellChaine * cell){
    CellChaine * tmp;
    while (cell){
        libererPoints(cell->points);
        tmp = cell;
        cell=cell->suiv;
        free(tmp);
    }
}
void libererChaine( Chaines * c){
    libererCell(c->chaines);
    free(c);
}

int tailleCellPoints(CellPoint *p) { //fonction aux pour avoir le nombre de points dans une liste de points
    int res = 0;
    if (p) {
        while (p) {
            res++;
            p = p->suiv;
        }
    }

    return res;
}

void ecrireChaines(Chaines *C, FILE *f) {
    fprintf(f, "NbChains: %d\n", C->nbChaines);
    fprintf(f, "Gamma: %d\n", C->gamma);
// printf("mdr\n");
    //int i,t;
    CellChaine *cell = C->chaines;
    while (cell) {
        //t=tailleCellPoints(cell->points);
        fprintf(f, "%d ", cell->numero);
        //fprintf(f,"%d ",t);
        CellPoint *p = cell->points;
        while (p) {
            fprintf(f, "%lf %lf ", cell->points->x, cell->points->y);
            p = p->suiv;
        }
        fprintf(f, "\n");
        cell = cell->suiv;

    }

}
void afficheChainesSVG(Chaines *C, char* nomInstance){
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
        precx=pcour->x;
        precy=pcour->y;
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}
double longueurChaine(CellChaine *c){
    CellPoint * p= c->points;
    CellPoint *psuiv= p->suiv;
    double res=0;
    double x1,x2,y1,y2;
    while(psuiv){
        x1=p->x;
        y1=p->y;
        x2=psuiv->x;
        y2=psuiv->y;
        res+= sqrt(pow((y2-y1),2)+pow((x2-x1),2));
        p=psuiv;
        psuiv= p->suiv;
    }
    return res;
}
double longueurTotale(Chaines *C){
    CellChaine * cell= C->chaines;
    double res=0;
    while (cell){
        res+= longueurChaine(cell);
        cell=cell->suiv;
    }
    return res;
}
int exists(CellPoint * liste, CellPoint *p){
    CellPoint * curr=liste;
    while (curr){
        if(curr->x==p->x && curr->y==p->y){
            return 1;
        }
        curr=curr->suiv;
    }
    return 0;
}
int comptePointsTotal(Chaines *C){
    CellChaine * cell=C->chaines;
    CellPoint * p ;
    CellPoint *tmp;
    CellPoint * alrseen=NULL;
    CellPoint * aj;
    int res=0;

    while (cell){
        p = cell->points;
        while (p){
            if (!exists(alrseen,p)){
                aj= (CellPoint *)malloc(sizeof(CellPoint));
                aj->x= p->x;
                aj->y=p->y;
                tmp=alrseen;
                alrseen=aj;
                aj->suiv=tmp;
                res++;
            }
            p=p->suiv;
        }
        cell=cell->suiv;
    }
    libererPoints(alrseen);
    return res;
}
Chaines * generationAleatoire(int nbChaines,int nbPointsChaine,int xmax ,int ymax){
    Chaines *c = malloc(sizeof(Chaines));
    c->gamma= rand()/(RAND_MAX/10);
    c->nbChaines=nbChaines;
    c->chaines = NULL;
    CellChaine *cell;
    CellChaine *tmpc;
    int i,j;

    for (i = 0; i < c->nbChaines; i++) { //on crée nbChaines chaines
        cell = malloc(sizeof (CellChaine));
        cell->numero=i;
        cell->points = NULL;
        CellPoint *tmp;
        for (j = 0; j < nbPointsChaine; j++) {
            CellPoint *p = (CellPoint *) malloc(sizeof(CellPoint));
            tmp = cell->points;
            p->x=(float)rand()/(float)(RAND_MAX/xmax);
            p->y=(float)rand()/(float)(RAND_MAX/ymax);
            cell->points = p;
            p->suiv = tmp;
        }
        tmpc = c->chaines;
        c->chaines=cell;
        cell->suiv=tmpc;


    }
    return c;
}
