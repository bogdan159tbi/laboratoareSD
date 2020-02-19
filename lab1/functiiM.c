/*-- functiiM.c --*/
#include "multimeV.h"

/*--- functii de initializare ---*/

TMultime *InitD(size_t n, size_t d, TFComp fcmp)
     /* creeaza multime, alocand dinamic spatiu pentru descriptor
        si n elemente de dimensiune d; intoarce adr.multime sau NULL */        
{ char *sf;
  TMultime *m = (TMultime*)calloc(1,sizeof(TMultime));
  if(!m) return NULL;                      /* alocare esuata */
  m->p = calloc(n, d);
  if(!m->p) { free(m); return NULL;}       /* alocare esuata */
  m->d = d;
  m->s = m->p;
  sf = (char*)(m->p) + d * n;
  m->t = (void*)sf;
  m->cmp = fcmp;
  return m;                          /* initializare reusita */        
}


void DistrugeM(TMultime **m)
{
   free((*m)->p);
   free(*m);
   *m = NULL;
}

int Cardinal(TMultime * m)
{
  return ((char*)m->s - (char*)m->p) / m->d;
}


/*--- operatii asupra multimilor NESORTATE ---*/

int Apartine(void * x, TMultime* m)
     /* intoarce 1/0 - elementul x exista/nu exista in multimea m */ 
{
  char *pm, *sf = (char*)(m->s);
  for(pm = (char*)(m->p); pm < sf; pm += m->d)
    if(m->cmp(x, (void*)pm) == 0) return 1;
  return 0;
}


int Adauga(void *nou, TMultime *m)
   /* obiectiv: adaugarea unui nou element la sfarsitul vectorului;
      intoarce 1/0/-1 - succes/exista deja/nu exista spatiu */
{ 
  char *sf = (char*)m->s;
  if(PlinaM(m)) return -1;         /* multime plina */
  if(Apartine(nou, m)) return 0;   /* nou exista deja in m -> gata */
  memcpy(m->s, nou, m->d);         /* copiaza nou la sfarsit m */
  sf += m->d;                      /* actualizeaza sfarsit */    
  m->s = (void*)sf;
  return 1;                        /* elementul a fost adaugat */
}

int Intersectie(TMultime *a,TMultime *b, TMultime *r)
{

  char *p;
  for(p=a->p; p< (char*)a->s; p+=a->d)
      if(Apartine(p,b))
          Adauga((void*)p,r);
}


int Reuniune(TMultime *a,TMultime *b,TMultime *r)
{
 char *pa,*pb;
 int elem=0;
 for(pa=a->p, pb=b->p; pa<(char*)a->s && pb<(char*)b->s; )
  {if(a->cmp((void*)pa,(void*)pb)==0)
    {
      Adauga((void*)pa,r);
      pa+=a->d;
      pb+=b->d;
      elem++;
    }
   else 
    {if(a->cmp((void*)pa,(void*)pb)<0)
     {
      Adauga((void*)pa,r);    
      pa+=a->d;
      elem++;
     }
    else 
      if(a->cmp((void*)pa,(void*)pb)>0){
      Adauga((void*)pb,r);
      pb+=b->d;
      elem++;
       }

    }
  }
  
  if(pa<(char*)a->s)
    while(pa<(char*)a->s)
    {
      Adauga((void*)pa,r);
      pa+=a->d;
      elem++;
    }

  
        
}
int IntersectieA(TMultime *a,TMultime *b)
{


  char* start=(char*)a->p;
  char *pa,*pb;
  pa=(char*)a->p;
  pb=(char*)b->p;

  while(pa<(char*)a->s && pb < (char*)b->s)
  {
    if(a->cmp(pa,pb)==0)
    {
      start+=a->d;
      pa+=a->d;
      pb+=b->d;
   }
   else 
   {
    if(a->cmp(pa,pb)>0)
      pb+=b->d;
    else
      pa+=a->d;
   }

  }
  a->s=start;
}
