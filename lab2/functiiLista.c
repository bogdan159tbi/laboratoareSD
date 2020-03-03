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
}
TLista insereaza(TLista *l,int elem)
{
  TLista p=*l,aux;
  if(*l == NULL)
  {
     aux=AlocCelula(elem);
     if(!aux)
      return 0;
    *l=aux;
    return *l;
  }
  for(;p->urm != NULL;p = p->urm);

  aux=AlocCelula(elem);
  if(!aux)
    return 0;
  p->urm = aux;
  aux ->urm = NULL;
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

int insertCom(TLista *rez,TLista l1,TLista l2)
{ 
  *rez=NULL;
  TLista p=NULL,aux,last=NULL;

  for(; l1!=NULL || l2!=NULL;)
  {
    if(l1->info < l2->info)
      l1=l1->urm;
    else
      {
        if(l1->info > l2->info)
        l2=l2->urm;
        else if(l1->info == l2->info)
        {
        aux=AlocCelula(l1->info);
        if(!aux)
        return 0;

        if(!*rez)
        {
         last=aux;
        *rez=aux;
        }
        else
        last->urm = aux;

        l1=l1->urm;
        l2=l2->urm;
      }
   }
}
  return 0;
}

TLista copie(TLista l)
{
  TLista p,ultim,aux,r;
  r=NULL;
  for(p=l;p!=NULL; p=p->urm)
  {
    aux=AlocCelula(p->info);
    if(!aux)
      return r;
    if(!r)
      {r=aux;
      ultim = aux;
      }
    else
    {
      ultim->urm=aux;
      ultim=aux;
    }

  }
return r;
}
void swap(int *a, int *b)
{
  int aux;
  aux = *a;
  *a = *b;
  *b=aux;
}

void sort(TLista *l)
{
  TLista l2=NULL,aux;

  l2=*l;

  while(l2 != NULL)
  {
    aux=l2->urm;
    while(aux)
    {
      if(l2->info > aux->info)
        swap(&l2->info , &aux->info);
      aux = aux->urm;
    }
    l2 = l2->urm;
  }

}

TLista mutare(TLista *l)
{
 TLista p,ant,aux,r,ultim;
 int poz = 1;

 for(p = *l,ant = NULL,r = NULL ; p != NULL ;poz++ )
 {
  if( p->info % 2 == 1 )
  {
    ant = p;
    p = p->urm;
  }
  else if( poz % 2 && p->info % 2 ==0)
  { 
    if(ant){
      ant->urm = p->urm;
    }
    else
      {
        *l = (*l)->urm;
        ant = *l;
      }

    if(!r)
    {
      r=p;
      ultim=p;
      ultim->urm = NULL;
    }
    else
    {
      ultim->urm = p;
      ultim = p;
      ultim->urm = NULL;
    }
     p = ant->urm;
     

  }
 
 }
 return r;

}

void deleteAll(TLista *l,int x)
{
  TLista prev,aux,l2;

  for( prev = NULL, l2 = *l;l2 != NULL; )
  {
    if(!prev && l2->info == x)
    {
      aux=l2;
      *l = (*l)->urm;
      free(aux);
    }
    else if( l2->info == x)
      {
        aux = l2;
        prev->urm = l2->urm;
        free(aux);
      }
    else if( l2->info != x)
      prev=l2;
    
    l2 = l2->urm;
  }

}


TLista Copie(TLista l)
{
  TLista new=NULL,aux;
  for( ; l != NULL; l = l->urm)
  {
    if(prim(l->info))
      insereaza(&new,l->info);
  }
  return new;
}

int distanceToPrime(int nr)
{
  int left,right;
  left = nr-1;
  right = nr + 1;
  while(left > 1)
  {
    if(prim(left))
      break;
    left--;
  }
  while( !prim(right) )
    right++;
  int d1,d2;
  d1 = nr - left;
  d2 = right - nr;

  if(d1<d2)
    d1 = d1;
  else if(d1 > d2)
    d1 = d2;
  return d1;
}

TLista CopyClosestPrime(TLista l1,TLista l2)
{

  TLista rez=NULL,aux,ultim;

  while(l1 != NULL || l2 != NULL) 
  {
    if(!l1 || !l2)
      break;
    if(prim(l1->info) || prim(l2->info)){
      if(prim(l1->info))
      {
        aux = AlocCelula(l1->info);
        if(!aux)
          return 0;
        if(!rez)
        {rez = aux;
         ultim = rez; 
        }
        else
        {
          ultim->urm = aux;
          ultim = ultim->urm;
        }
      }
      else if(prim(l2->info))
      {
         aux = AlocCelula(l2->info);
        if(!aux)
          return 0;
        if(!rez)
        {rez = aux;
         ultim = rez; 
        }
        else
        {
          ultim->urm = aux;
          ultim = ultim->urm;
        }
        
      }

    }
      else
      {
        int nr;
        int d1 = distanceToPrime(l1->info);
        int d2 = distanceToPrime(l2->info);
        if(d1 < d2)
          nr = l1->info;
        else
          nr = l2->info;

         aux = AlocCelula(nr);
        if(!aux)
          return 0;
        if(!rez)
        {rez = aux;
         ultim = rez; 
        }
        else
        {
          ultim->urm = aux;
          ultim = ultim->urm;
        }
      }
      l1 = l1->urm;
      l2 = l2->urm;
  }


  
  if(l1){
    printf("lista l1 nu e gata\n");
  while(l1 != NULL){
    int nr = l1->info;
     

    l1 = l1->urm;
  }
}
  if(l2){
    printf("l2 nu e gata\n");
  while(l2 != NULL)
    {
    int nr = l2->info;
     aux = AlocCelula(nr);
        if(!aux)
          return 0;
        if(!rez)
        {rez = aux;
         ultim = rez; 
        }
        else
        {
          ultim->urm = aux;
          ultim = ultim->urm;
        }
     l2 = l2->urm;
    }

  }

  return rez;
}

TLista reuniune(TLista l1,TLista l2)
{
  TLista aux,rez = NULL,ultim;
  int nr;

  while( l1 != NULL || l2 != NULL)
  {

    if(!l1 || !l2)
      break;
    if(l1->info < l2->info)
    {
      nr = l1->info;
      aux = AlocCelula(nr);
        if(!aux)
          return 0;
        if(!rez)
        {rez = aux;
         ultim = rez; 
        }
        else
        {
          ultim->urm = aux;
          ultim = ultim->urm;
        }
      l1 = l1->urm;
      }
    else
    { 
      nr = l2->info;
      aux = AlocCelula(nr);
        if(!aux)
          return 0;
        if(!rez)
        {rez = aux;
         ultim = rez; 
        }
        else
        {
          ultim->urm = aux;
          ultim = ultim->urm;
        }
      if(l1->info == l2->info)
      {
        l1 = l1->urm;
        l2 = l2->urm;
      }
      else
        l2 = l2->urm;
    }

  }
  
  while( l1 != NULL)
  {

     nr = l1->info;
     aux = AlocCelula(nr);
        if(!aux)
          return 0;
        if(!rez)
        {rez = aux;
         ultim = rez; 
        }
        else
        {
          ultim->urm = aux;
          ultim = ultim->urm;
        }

      l1 = l1->urm;
  }
  while( l2 != NULL)
  {
    nr = l2->info;
    int nr = l2->info;
     aux = AlocCelula(nr);
        if(!aux)
          return 0;
        if(!rez)
        {rez = aux;
         ultim = rez; 
        }
        else
        {
          ultim->urm = aux;
          ultim = ultim->urm;
        }
    l2 = l2->urm;
  }

  return rez;

}