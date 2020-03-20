#include "stack.h"
#include<stdio.h>
#include<stdarg.h>
#include<string.h>
void *initStack(size_t d,...)
{
	ASt a;
	va_list ap;
	a = (ASt)malloc(sizeof(TStack));
	if(!a)
	  return NULL;
	va_start(ap,d);
	a->maxElem = va_arg(ap,size_t);
	va_end(ap);
	a->dimElem = d;

	a->base = (char*)calloc(a->maxElem,d);
	if(!a->base)
	{
		free(a);
		return NULL;
	}
	a->topStack = a->base;
	a->endStack = a->base + d*a->maxElem;
	return (void*)a;
}

/* a = stiva ae = adresa elem de inserat */
int push(void *a, void *ae)
{
	if(PLINA(a)){printf("stiva goala\n");
		return 0;
	}
	memcpy(VF(a),ae,DIME(a));
	VF(a) += DIME(a);
	return 1;
}

int pop(void *a,void *ae)
{
	if(VIDA(a)) return 0;
	VF(a) -= DIME(a);
	memcpy(ae, VF(a),DIME(a));
	return 1;
}

int top(void *a,void *ae)
{
	if(VIDA(a)){printf("nu are top\n");
		return 0;
	}
	memcpy(ae,VF(a) - DIME(a),DIME(a));
	return 1;
}

int nrElemStack(void *a)
{
	return ((VF(a)-BS(a))/DIME(a));
}

void DistrStack(void **adrA)
{
	free(BS(*adrA));
	free(*adrA);
	*adrA = NULL;
}

int mutaStack(void *adrDest, void *adrSrc)
{	
	if(DIMDIF(adrSrc,adrDest)) return -1;
	if(VIDA(adrSrc)) return 0;
	if(PLINA(adrDest)) return -2;

	/*mutare elem */
	VF(adrSrc) -= DIME(adrSrc);
	memcpy(VF(adrDest),VF(adrSrc),DIME(adrSrc));
	VF(adrDest) += DIME(adrDest);
	return 1;
}

int reverseStack(void *adrDest,void *adrSrc)
{
	size_t n = VF(adrSrc) - BS(adrSrc);
	if(DIMDIF(adrSrc,adrDest)) return -1;
	if(VIDA(adrSrc)) return 0;
	if(VF(adrDest) + n > SV(adrDest)) return -2;

	/* muta varf src la baza dest */
	
	while (VF(adrSrc) > BS(adrSrc))
	{
		VF(adrSrc) -= DIME(adrSrc);
		memcpy(VF(adrDest),VF(adrSrc),DIME(adrSrc));
		VF(adrDest) += DIME(adrSrc);
	}
	return 1;
}

int switchElem(void *a)
{
	char *temp = VF(a), *p,*q;

	if(temp >= SV(a))
		temp = (char*)malloc(DIME(a));
	if(!temp)
		return 0;
	/* inverseaza perechi de elem */
	for(p = BS(a), q = SV(a) - DIME(a); p < q ; p  += DIME(a), q -= DIME(a))
	{	
		memcpy(temp,p,DIME(a));
		memcpy(p,q,DIME(a));
		memcpy(q,p,DIME(a));
	}
	if(temp != VF(a))
		free(temp);
	return 1;
}

int deleteElements(void *a,int elem)
{
	if(VIDA(a)) {
		printf("goala\n");
		return 0;
	}
	char *base ;
	for( base = BS(a); base < VF(a); base += DIME(a))
		printf("%d\n",*(int*)base);

	return 1;
}

int inverseaza(void* stiva)
{
	TStack *stack;
	stack = initStack(sizeof(int));
	if(!stack)
		return 1;
	int nr;
	while(!VIDA(stiva))
	{
		pop(stiva,&nr);
		push(stack,&nr);
	}
	stiva = stack;
	DistrStack((void*)&stack);
}