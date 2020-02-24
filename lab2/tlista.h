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
void swap(struct celula *l1,struct celula *l2);
int nrElem(TLista l);
int checkHalf(TLista l);
int sameElem(TLista l1,TLista l2);
#endif
