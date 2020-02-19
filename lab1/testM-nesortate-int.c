/*-- testM-nesortate-int.c --*/
#include "multimeV.h"

/*-- functie de afisare multime intregi --*/
void AfisareMultime_int(TMultime *m)
{ int *x = (int*)(m->p), n = Cardinal(m), i = 0;
  printf("[");
  for( ; i < n; i++) 
	if(i != n-1) printf(" %i,", x[i]);
	else printf(" %i ]", x[i]);
}

int compI(const void *a, const void *b) /*-- functie de comparare --*/
{ return *(int*)a - *(int*)b; }

int main()
{ int va[20] = {-1, 23, 4, 6, -9, 4, 10}, nva = 7,
      vb[10] = {2, 4, -9, 12, 10, 1, 11}, nvb = 7; 
  TMultime *a, *b;
  int i, rez;
  
  qsort((void*)va,nva,sizeof(int),compI);
  qsort((void*)vb,nvb,sizeof(int),compI);
  /* constructie multime a */
  a = InitD(7, sizeof(int), compI);
  if(!a) {printf("eroare initializare\n"); return 1;}
  printf("\nConstructie multime a, cu elementele: ");
  for(i = 0; i < nva; i++) printf("%i ", va[i]);
  printf("\n");
  for(i = 0; i < nva; i++) 
  { 
    rez = Adauga((void*)(va+i), a);
    printf("%i %s\n", va[i], rez? "adaugat" : "exista deja");
  }
  printf("Cardinal(a) = %d,  ", Cardinal(a)); 
  printf("a: "); AfisareMultime_int(a);

  
  /* constructie multime b */
  b=InitD(10, sizeof(int), compI); 
  printf("\nConstructie multime b, cu elementele: ");
  for(i = 0; i < nvb; i++) printf("%i ", vb[i]);
  printf("\n");
  for(i = 0; i < nvb; i++) 
  { rez = Adauga((void*)(vb+i), b);
    printf("%i %s\n", vb[i], rez? "adaugat" : "exista deja");
  }
  printf("Cardinal(b) = %d, ", Cardinal(b)); 
  printf("b: "); AfisareMultime_int(b);
  
  /* apeluri functii implementate */
  TMultime *r;
  int nvr;
  if(Cardinal(a)>Cardinal(b))
    nvr=Cardinal(b);
  else
    nvr=Cardinal(a);

  r=InitD(nvr,sizeof(int),compI);
  if(!r)
    {
      DistrugeM(&a);
      DistrugeM(&b);
      return 1;
    }
  Intersectie(a,b,r);
  printf("\n Afisare intersectie a si b:\n");
  AfisareMultime_int(r);

  TMultime *reu;
  int nvre;
  
  nvre=Cardinal(a)+Cardinal(b);
  reu=InitD(nvre,sizeof(int),compI);
  if(!reu)
  {
    DistrugeM(&a);
    DistrugeM(&b); 
    DistrugeM(&r);
    return 1; 
  }

  
  printf("\nAfisare reuniune a si b:\n");
  Reuniune(a,b,reu);
  AfisareMultime_int(reu); 
  printf("\n");
  printf("Avem a si b:\n");
  AfisareMultime_int(a);
  printf("\n");
  AfisareMultime_int(b);

  IntersectieA(a,b);
  printf("Rezultat in a\n");
  AfisareMultime_int(a);
  // la bonus a = a intersectat b cu a si b ordonate
  DistrugeM(&reu);
  DistrugeM(&a);
  DistrugeM(&b); 
  DistrugeM(&r);
  return 0;
}
