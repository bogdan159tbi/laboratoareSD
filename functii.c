#include "lista.h"

TLista alocCel(int x)
{
	TLista aux;
	aux=(TLista)malloc(sizeof(struct celula));
	aux->urm=NULL;
	aux->info=x;
	return aux;
}
TLista readList(int *len)
{
	TLista aux,ultim,L=NULL;
	*len=0;
	int x;
	while(scanf("%d",&x)==1)
	{
		aux=alocCel(x);
		if(!aux)
			return L;
		if(!L)
		{
			L=aux;
			ultim=aux;
			*len=1;
		}
		else
		{
			ultim->urm=aux;
			ultim=aux;
			*len++;
		}
	}
	return L;
}

void showList(TLista l)
{
	TLista p=l;
	while(p)
	{
		printf("%d ",p->info);
		p=p->urm;
	}
}

int insertBefore(TLista *l,int ref,int x)
{
	TLista aux,p,ant;
	for(p=*l,ant=NULL;p!=NULL;ant=p,p=p->urm)
		if(p->info==ref)
			break;
	if(!p)
		return 0;
	aux=alocCel(x);
	if(!aux)
		return 0;
	aux->info=x;
	aux->urm=p;
	if(!ant)
		*l=aux;
	else
		ant->urm=aux;
	return 1;

}
int insertStart(TLista *l,int x){

	TLista aux;
	aux=alocCel(x);
	if(!aux)
		return 0;
	if(*l==NULL)
		*l=aux;
	else{
		aux->urm=*l;
		*l=aux;
		}
}

int insertEnd(TLista *l,int x)
{ TLista aux,ultim,p;
  ultim=NULL;
  p=*l;

  for(p=*l,ultim=NULL;p!=NULL;ultim=p,p=p->urm);
  aux=alocCel(x);
  if(!ultim)
  	*l=ultim;
  else
  	ultim->urm=aux;
return 1;
}
void destroyList(TLista *l)
{
	TLista aux,p;
	p=*l;
	while(p)
	{
		aux=p;
		p=p->urm;
		free(aux);
	}
*l=NULL;
}
int deleteElem(TLista *l,int elem)
{
	TLista p,ant;
	p=*l;
	for( ;p!=NULL;ant=p,p=p->urm)
		if(p->info==elem)
		{
			if(!ant){
				*l=p->urm;
				free(p);
			}
			else{
			ant->urm=p->urm;	
			free(p);
			}
			return 1;
		}
return 1;
}