/*-- tlista.h --- LISTA SIMPLU INLANTUITA cu elemente de tip intreg ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#ifndef _LISTA_SIMPLU_INLANTUITA_
#define _LISTA_SIMPLU_INLANTUITA_

typedef struct celula
{ int info;
  struct celula * urm;
} TCelula, *TLista; /* tipurile Celula, Lista */

#define VidaL(L) ((L) == NULL)

/*-- operatii elementare --*/

TLista AlocCelula(int);          /* adresa celulei create sau NULL */
void   DistrugeL (TLista*);       /* elimina toate celulele din lista */
TLista insertAfterRef(TLista *l,int ref);
void AfisareL (TLista L);
TLista deleteElem(TLista *l,int ref);
void perechi(TLista l);
void sortList(TLista *l);
TLista insereaza(TLista *l,int elem);
int nrElem(TLista l);
int checkHalf(TLista l);
int sameElem(TLista l1,TLista l2);
int elim(TLista *l,int *nr,int ref);
int insertCom(TLista *rez,TLista l1,TLista l2);
TLista mutare(TLista *l);
TLista copie(TLista l);
TLista ordonat(TLista *l);
void sort(TLista *l);
void swap(int *a , int *b);
void deleteAll(TLista *l,int x);
TLista CopyClosestPrime(TLista l1,TLista l2);
TLista Copie(TLista l);
int prim(int nr);
int distanceToPrime(int nr);
TLista reuniune(TLista l1,TLista l2);



#endif
