/*--- lista2.c ---
      operatii lista generica dublu inlantuita, circulara, cu santinela ---*/

#include "lista2.h"
#include<string.h>

#define NMAX 20
int InsDupa(TLDI a, void* x)  /* inserare dupa celula cu adresa a -> 1/0 */
{
	TLDI aux = (TLDI)malloc(sizeof(TCelula2));
	if(!aux) return 0;
	aux->info = x;
	aux->pre = a;
	aux->urm = a->urm;
	a->urm->pre = aux;
	a->urm = aux;
    return 1;
}


void ResetLDI(TLDI s)
     /* transforma lista in lista vida */
{
	TLDI p = s->urm, aux;
	while(p != s)
	{
		aux = p;
		p = p->urm;
		free(aux->info);
		free(aux);
	}
	s->urm = s->pre = s;
}

void DistrLDI(TLDI* as)
     /* elibereaza tot spatiul ocupat de lista, inclusiv santinela */
{
	ResetLDI(*as);
	free(*as);
	*as = NULL;
}

TLDI InitLDI()
    /* -> lista vida, cu info din santinela specifica aplicatiei */
{
	TLDI aux = (TLDI)malloc(sizeof(TCelula2));
    if (!aux) return NULL;

	aux->pre = aux->urm = aux;
    aux->info = NULL;

	return aux;     /* rezultatul este adresa santinelei sau NULL */
}

void AfisareLDI(TLDI s, void (*afiEl)(void *))
    /* afisare lista */
{
	TLDI p;
	printf("Lista: ");
	if(s->urm == s)
	{
		printf("vida\n");
		return;
	}
	for(p = s->urm; p != s; p = p->urm)
		afiEl(p->info);
	printf("\n");
}


void *Elimina(TLDI s, void *ae,TFCmp cmp)
{
	TLDI p = NULL;
	for( p = s->urm ; p != s; p = p->urm)
		if(!cmp(p->info,ae))
			{
				p->urm->pre = p->pre;
				p->pre->urm = p->urm;
				return p->info;
			}
	return NULL;
}

TLDI Muta(TLDI s)
{
	TLDI p,ultim = NULL,r;
	r = InitLDI();
	int poz;
	for(poz = 1,p = s->urm; p != s; p = p->urm, poz++)
	{
		if(poz % 2)
		{
			if(!ultim)
			{
				r->urm = p;
				r->pre = p;
				p->pre->urm = p->urm;
				p->urm->pre = p->pre;
				p->pre = r;
				ultim = p;
			}
			else
			{
				ultim->urm = p;
				p->pre->urm = p->urm;
				p->urm->pre = p->pre;
				p->pre = ultim;
				ultim = p;
			}
		}
	}
	if(ultim)
	{
		ultim->urm = r;
		r->pre = ultim;
	}
return r;
}
int simetrica(TLDI s)
{
	TLDI back,front;
	for(front = s->urm ,back = s->pre; ;back = back->pre, front = front->urm)
	{	
		if(back == s || front == s )
			break;

		if(*(int*)back->info != *(int*)front->info){
			return 0;
		}
	}
	return 1;
}


TLDI firstHalf(TLDI s)
{
	TLDI rez ,ultim = NULL,aux;
	int elem = 0;

	TLDI s1, s2;
	for(s1 = s->urm , s2 = s->pre; ;s1 = s1->urm , s2 = s2->pre)
	{
		if(s2->pre == s1 || s2->pre == s1->urm)
			{	elem++;
				break;
			}
			elem++;
	}
	int ok = 0 ;

	rez =InitLDI();
	if(elem == 0)
		return NULL;
	for (s1 = s->urm; ok < elem;s1 = s1->urm, ok++)
	{
		int val = *(int*)s1->info;
		if(val % 2 == 0 )
		{
			aux = malloc(sizeof(TCelula2));
			if(!aux)
				return NULL;
			aux->info = s1->info;
			if(!ultim)
			{
				rez->urm = aux;
				rez->pre = aux;

				aux->pre = rez;
				aux->urm = rez;
		
				ultim = aux;
			}
			else
			{
				ultim->urm = aux;
				aux->pre = ultim;
				
				aux->urm = rez;
				rez->pre = aux;

				ultim = aux;
			}
		}
	}

	return rez;
}

void deleteElem(TLDI s,int n)
{

	int elem = 0;

	TLDI s1, s2;
	for(s1 = s->urm , s2 = s->pre; ;s1 = s1->urm , s2 = s2->pre)
	{
		if(s2->pre == s1 || s2->pre == s1->urm)
			{	elem++;
				break;
			}
			elem++;
	}
	int ok;
	ok = 0;
	for (s1 = s->urm; ok < elem;s1 = s1->urm, ok++)
	{
		int val = *(int *)s1->info;
		if(val < n)
		{
			s1->pre->urm = s1->urm;
			s1->urm->pre = s1->pre;
			free(s1);
		}
	}

}

TLDI insert(int *lg,TFCmp cmp)
{	
	TLDI rez=NULL ,aux,s;
	rez = InitLDI();
	rez->urm = rez;
	rez->pre =rez;
	int *ax, x;
 	char ch;

 	int *elem;
 	elem = malloc(sizeof(int)*NMAX);
 	if(!elem)
 		return NULL;

	printf("\n se citesc valori numerice, terminate cu caracter nenumeric\n");
	for(*lg = 0; scanf("%i", &x) == 1; )
  	{
		elem[*lg] = x;
    		(*lg)++;
  	}
  	while((ch=getchar()) != EOF && ch != '\n');

  	int ok = 0;

  	printf("lungimea %d\n",*lg);
  	for(; ok < *lg; ok++)
  	{
  		ax = (int*)malloc(sizeof(int));
		if(!ax) return NULL;
	 	*ax = elem[ok];
  		aux = malloc(sizeof(TCelula2));
		if(!aux)
			return NULL;
		aux->info = ax;
		aux->pre = NULL;
		aux->urm = NULL;
		if(rez->urm == rez)
		{	
			rez->urm = aux;
			rez->pre = aux;
			aux->urm = rez;
			aux->pre = rez;
    	}
    	else
    	{
    		for( s = rez->urm ;s != rez; s = s->urm)
    		{	
    			if(cmp(s->info,ax) >= 0)
    			{
    				aux->pre = s;
    				aux->urm = s->urm;
    				s->urm->pre = aux;
    				s->urm = aux;
    				break;
    			}
    			else
    			{
    				aux->urm = s;
    				aux->pre = s->pre;
    				s->pre->urm = aux;
    				s->pre = aux;
    				break;
    			}
    		}
    	}
  	}

  	free(elem);
  	return rez;
}