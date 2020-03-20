#ifndef _STIVA_
#define _STIVA_
#include<stdio.h>
#include<stdlib.h>

// paranthesis for a in case it was a pointer
#define DIME(a) (((ASt)(a))->dimElem)
#define BS(a) (((ASt)(a))->base)
#define SV(a) (((ASt)(a))->endStack)
#define VF(a) (((ASt)(a))->topStack)
/*-teste*/
#define DIMDIF(src,dest) (DIME(src) != DIME(dest)) // dimensiunea unui elem din fiecare stiva difera 
#define VIDA(a) (VF(a) == BS(a))
#define PLINA(a) (VF(a) == SV(a))


typedef struct 
{
size_t maxElem ,dimElem; //nr maxim de elem ,dimensiune elem
char *base, *endStack, *topStack; // base = baza stivei
}TStack, *ASt;

void *initStack(size_t d,...);
int push(void *a, void *ae);
int pop(void *a,void *ae);
int top(void *a,void *ae);
int nrElemStack(void *a);
void DistrStack(void **adrA);
int mutaStack(void *adrDest, void *adrSrc);
int reverseStack(void *adrDest,void *adrSrc);
int switchElem(void *a);
int deleteElements(void *,int);
int inverseaza(void*);

#endif