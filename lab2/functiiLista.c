/*-- functiiLista.c --*/
#include <ctype.h>
#include "tlista.h"

/*--- operatii de baza pentru lista simplu inlantuita ---*/

TLista AlocCelula(int e)          /* adresa celulei create sau NULL */
{ TLista aux = (TLista)malloc(sizeof(TCelula));  /* (1) incearca alocare */
  if (aux)                            /* aux contine adresa noii celule */
  { aux->info = e;                   /* (2,3) completeaza noua celula */
    aux->urm = NULL;
  }
  return aux;             /* rezultatul este adresa noii celule sau NULL */
}

void AfisareL(TLista L)
       /* afiseaza valorile elementelor din lista */
{
  printf("Lista: [");                      /* marcheaza inceput lista */
  for (; L != NULL; L = L->urm)       /* pentru fiecare celula */
    printf("%d ", L->info);              /* afiseaza informatie */
  printf("]");                               /* marcheaza sfarsit lista */
}

void DistrugeL(TLista* aL)
{
  TLista aux;
  while(*aL)
  {
    aux = *aL;
    *aL = aux->urm;
    free(aux);
  }
}
TLista insertAfterRef(TLista *l,int ref)
{
  TLista prev,aux,p;
  p=*l;
  
  for(;  p!=NULL;p=p->urm)
  {
    if(p->info == ref)
    {
      aux=AlocCelula(ref);
      if(!aux)
        return 0;
      aux->urm=p->urm;
      p->urm=aux;
      p=p->urm;
    }
  }

return *l;
}
int prim(int nr)
{
  int i=2;
  if(nr==1 || nr==0)
    return 0;
  while(i<nr)
  {
    if(nr%i==0)
      return 0;
    i++;
  }
  return 1;
}
void perechi(TLista l)
{

  for( ;l->urm != NULL ;l=l->urm)
  {
    if(prim(l->info) && prim(l->urm->info))
      printf("%d %d\n",l->info,l->urm->info);
  }
}

int nrElem(TLista l)
{ 
  int nr=0;
  while(l!=NULL)
  {
    nr++;
    l=l->urm;
  }
  return nr;
}
int checkHalf(TLista l)
{
  int nr=nrElem(l);
  int first=0,sec=0;
  int nr1=0,nr2=0;
  while(first<nr/2)
  {
    if(l->info%2==1)
      nr1++;
    l=l->urm;
    first++;
  }
  while(l!=NULL)
  {
    if(l->info%2==1)
      nr2++;
    l=l->urm;
  }
  if(nr1==nr2)
    return 1;
  return 0;
}

int sameElem(TLista l1,TLista l2)
{
  int nr1=nrElem(l1);
  int nr2=nrElem(l2);
  if(nr1!=nr2)
    return 0;
  while(l1!=NULL)
  {
    TLista p=l2;
    int ok=0;
    while(p!=NULL)
    {
      if(l1->info == p->info)
        ok=1;
      p=p->urm;
    }
    if(!ok)
      return 0;
    l1=l1->urm;
  }
  return 1;
}

int elim(TLista *l,int *nr,int ref)
{
  TLista p,aux=NULL,prev;
  *nr=0;
  int elem=nrElem(*l);
  for(p=*l,prev=NULL;p!=NULL;p=p->urm)
  {
    if(p->info >= ref)
    {
      if(prev==NULL)
        {*l=p->urm;
          aux=p;
          free(aux);
        }
      else
      {
        prev->urm=p->urm;
        aux=p;
        free(aux);
      }
      *nr++;
    }
    else
      prev=p;

  }
return 1;
}

