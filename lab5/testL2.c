#include "lista2.h"
#include<string.h>


void AfiInt(void * ax)
{
	printf("%d ", *(int*)ax);
}


int cmpInt(void *a,void *b)
{
	if(*(int*)a == *(int*)b)
		return 0;
	return 1;
}
void CitireLDI(TLDI s, int* lg)
{
	int *ax, x;
 	char ch;

  	printf("se citesc valori numerice, terminate cu caracter nenumeric\n");
	for(*lg = 0; scanf("%i", &x) == 1; )
  	{
        ax = (int*)malloc(sizeof(int));
		if(!ax) return;
	 	*ax = x;
		InsDupa(s->pre, ax);
    		(*lg)++;
  	}
  	while((ch=getchar()) != EOF && ch != '\n');
}

int cmpIncreasing(void *a,void *b)
{
	int x1,x2;
	x1 = *(int*)a;
	x2 = *(int*)b;
	if(x1 < x2)
		return 1;
	if(x1 > x2)
		return -1;
	return 0;

}
int cmpDecreasing(void *a,void *b)
{
	int x1,x2;
	x1 = *(int*)a;
	x2 = *(int*)b;
	if(x1 < x2)
		return -1;
	if(x1 > x2)
		return 1;
	return 0;

}

int main()
{
	TLDI s,new;
	int lg,len2;
	int inf = 2;
	int *p = &inf;
	for(; ; )
	{
		s = InitLDI();
		CitireLDI(s, &lg);
		/* apeluri functii */
		printf("task1\n");
		new = firstHalf(s);
		AfisareLDI(new,AfiInt);
		printf("\n task 2 \n");

		printf("lista inainte de eliminare\n");
		AfisareLDI(s,AfiInt);
		deleteElem(s,3);
		AfisareLDI(s,AfiInt);
		printf("\nbonus\n");
		new = insert(&len2,cmpIncreasing);
		AfisareLDI(new,AfiInt);
		printf("\n");

		DistrLDI(&new);
		DistrLDI(&s);
		printf ("\n  Inca un test ? [d/n]");
		if (getchar() == 'n') break;
	}
    return 1;
}
