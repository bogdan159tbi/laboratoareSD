#include "lista2.h"
#include<string.h>
#include "stud.h"


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



int main()
{
	TLDI s,new;
	int lg;
	int inf = 2;
	int *p = &inf;
	for(; ; )
	{
		s = InitLDI();
		CitireLDI(s, &lg);

		/* apeluri functii */
		DistrLDI(&s);
		printf ("\n  Inca un test ? [d/n]");
		if (getchar() == 'n') break;
	}
    return 1;
}
