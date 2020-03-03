/*--- testLista.c ---*/
#include <ctype.h>
#include <stdio.h>
#include "tlista.h"

TLista CitireL(int *lg)     /* construieste lista cu elemente citite */
{ TLista L = NULL, u, aux;
  int x;
  char ch;
  for(*lg = 0; scanf("%i", &x) == 1; )
  {
    aux = AlocCelula(x);           /* incearca inserarea valorii citite */
    if(!aux) return L;              /* alocare esuata => sfarsit citire */
    if(L == NULL) L = aux;
    else u->urm = aux;
    u = aux;
    (*lg)++;
  }
  while((ch=getchar()) != EOF && ch != '\n');
  return L;                     /* intoarce lista rezultat */
}

int main ()
{ TLista x = NULL,y=NULL,z=NULL;     /* Lista prelucrata */
  int lx;           /* lungime lista */
  int app=0;
  int ly;
  TLista rez;
  for (;;)
  {
    /* citeste si afiseaza lista */
    printf("\nIntroduceti valori elemente terminate cu valoare nenumerica:\n");
    
    printf("task1\n");
    x = CitireL(&lx);

    if(!x) continue;
   
    rez = mutare(&x);
    AfisareL(rez);
    printf("\n");
    AfisareL(x);
    
    
    
    printf("task2\n");

    x = CitireL(&ly);
    if(!x )
      continue;

    rez = Copie(x);
    AfisareL(rez);



    printf("task3\n");

    x = CitireL(&lx);
    y = CitireL(&ly);

    if(!x) continue;
    if(!y) continue;
    rez = CopyClosestPrime(x,y);
    AfisareL(rez);

    printf("task4\n");
    x = CitireL(&lx);
    y = CitireL(&ly);

    if(!x) continue;
    if(!y) continue;

    rez = reuniune(x,y);
    AfisareL(rez);
    DistrugeL(&rez);
    DistrugeL(&x);
    DistrugeL(&y);
    printf ("\n  Inca un test ? [d/n]");
    if (getchar() == 'n') break;
  }
}