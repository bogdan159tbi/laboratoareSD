#include<stdio.h>
#include<stdlib.h>


typedef struct celula
{
	int info;
	struct celula *urm;
}TCel,*TLista;

int insertBefore(TLista *l, int ref, int x);
int insertStart(TLista *l,int x);
int insertEnd(TLista *l,int x);
TLista readList(int *len);
void destroyList(TLista *l);
int deleteElem(TLista *l,int x);
TLista alocCel(int x);
void showList(TLista l);
