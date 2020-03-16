/*--- lista2.c ---
      operatii lista generica dublu inlantuita, circulara, cu santinela ---*/

#include "lista2.h"

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