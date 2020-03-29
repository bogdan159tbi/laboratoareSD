#include "TCoada.h"
#include "TStiva.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 256

typedef struct 
{
	int id,varsta;
}TPersoana;
typedef struct 
{
	int id,diametru;
}TDisc;

//return number of elem introduced in the queue;
int GenereazaCoadaPers(void *c,size_t N,int v1 ,int v2)
{
	int n = 0;
	TPersoana p;
	srand(time(NULL));
	for(int i = 0; N > 0; N--, i++)
	{
		p.id = i;
		p.varsta = rand() % (v2 - v1 + 1) +v1;

		if(!IntrQ(c,&p))
			return n;
		n++;
	}

return n;
}

int GenereazaStivaPers(void *stack, size_t N , int v1, int v2)
{
	int n = 0;
	TPersoana p;
	srand(time(NULL));
	for(int i = 0; N > 0; N--, i++)
	{
		p.id = i;
		p.varsta = rand() % (v2 - v1 + 1) +v1;
		if(!Push(stack, &p))
			return n;
		n++;
	}
	return n;
}

int AfiPers(void *p)
{
	printf("[%d %d] ",(*(TPersoana*)p).id , (*(TPersoana*)p).varsta);
	return 1;
}

void AfiQ(char antet[] , TF1 AfiElem, void *queue)
{
	printf("%s",antet);
	if(VidaQ(queue))
		printf("coada vida!");
	else
		PrelQ(queue,AfiElem);
	printf("\n");
}

void AfiStack(char antet[] ,TF1 AfiElem , void *stack)
{
	printf("%s\n",antet);
	if( VidaS(stack))
		printf("stiva goala\n");
	else
		Prel_B_V(stack,AfiElem);
	printf("\n");
}

//copy of a queue

// return medium age for the pers in the queue
float FC1(void *q)
{
	void *qaux = InitQ(sizeof(TPersoana),MAX);
	if(qaux == NULL)
	{
		printf("aux queue not allocated \n");
		return 0;
	}
	float age = 0;
	float nr = 0;
	TPersoana *p = malloc(sizeof(TPersoana));
	if(!p)
	{	printf("pers neaocata\n");
		return 0;;
	}
	while (!VidaQ(q))
	{
		ExtrQ(q,p);
		IntrQ(qaux,p);
		nr++;
		age += p->varsta;
	}
	free(p);
	ConcatQ(q,qaux);
	free(qaux);
	if(nr)
	return age/nr;
	return 0;
}
float FS1(void *stack)
{
	void *stAux = InitS(DimES(stack),MAX);
	float med = 0 , disc = 0;

	if(stAux == NULL)
	{
		printf("stack not allocated\n");
		return 0;
	}
	
	void *p = (TDisc*)malloc(sizeof(DimES(stack)));
	if(!p)
	{
		free(stAux);
		return 0;
	}
	while (!VidaS(stack))
	{
		Pop(stack,p);
		Push(stAux,p);
		med += (*(TDisc*)p).diametru;
		disc++;
	}
	Suprapune(stack,stAux);
	free(stAux);
	return med/disc;
}

int cmpQE(void *adrElem,int ref)
{
	if((*(TPersoana*)adrElem).varsta > ref)
		return 1;
	return 0;
}

void *copyOlder(void *qSrc, int age,TFCmp cmp)
{
	void *older,*qaux;
	older = InitQ(DimEQ(qSrc),MAX);
	if(!older)
		return NULL;
	qaux = InitQ(DimEQ(qSrc),MAX);
	if (!qaux)
	{
		free(older);
		return NULL;
	}
	void *adrElem = malloc(DimEQ(qSrc));
	if(!adrElem)
	{
		free(older);
		free(qaux);
		return NULL;
	}

	while (!VidaQ(qSrc))
	{
		ExtrQ(qSrc,adrElem);
		if(cmp(adrElem,age) == 1)
			IntrQ(older,adrElem);
		else
			IntrQ(qaux,adrElem);
	}
	ConcatQ(qSrc,qaux);
	free(adrElem);
	return older;
}
int cmpSE(void *adrElem,int ref)
{
	TDisc *disc = (TDisc*)adrElem;
	if(disc->diametru > ref)
		return 1;
	return 0;
}
int AfiDisc(void *d)
{
	TDisc *disc = (TDisc *)d;
	printf("[%d %d] ",disc->id,disc->diametru);
	return 1;
}
int par(void *p)
{
	TPersoana *pers = (TPersoana*)p;
	if(pers->id %2 == 0)
		return 1;
	return 0;
}
int parIDDisc(void *disc)
{
	TDisc *d = (TDisc*)disc;
	if(d->id % 2 == 0 )
		return 1;
	return 0;
}

int main()
{
	void *queue,*stack;
	int lenSt,lenQ;

	queue = InitQ(sizeof(TPersoana),MAX);
	if (!queue)
		return 1;
	stack = InitS(sizeof(TPersoana),MAX);
	if (!stack)
	{
		free(queue);
		return 1;
	}
	lenSt = GenereazaStivaPers(stack, 5 , 0 , 10);
	lenQ = GenereazaCoadaPers(queue, 5, 5 ,30);
	printf("coada cu %d elem:\n",lenQ);
	AfiQ("coada cu elem",AfiPers,queue);
	printf("stiva are %d elem",lenSt);
	AfiStack("stiva cu elem:\n",AfiDisc,stack);
	printf("diametru mediu %f\n",FS1(stack));

	printf("varsta medie %f\n",FC1(queue));
	AfiQ("\ncoada de dupa aflarea mediei\n",AfiPers,queue);

	void *qaux = copyOlder(queue,22,cmpQE);
	AfiQ("coada cu cei batrani de 22 de ani \n",AfiPers,qaux);

	void *stackGreaterDiam = copyLower(stack,1,cmpSE);
	AfiStack("stiva cu diametrele mai mari de 1",AfiDisc,stackGreaterDiam);

	void *queueOddID = oddID(queue,par);
	AfiQ("\ncoada cu id par = ",AfiPers,queueOddID);
	AfiQ("coada initiala cu id impar ramas\n",AfiPers,queue);

	void *stackOddID = copyOddID(stack,parIDDisc);
	AfiStack("stiva cu id par = ",AfiDisc,stackOddID);
	AfiStack("stiva ramasa cu id impar",AfiDisc,stack);

	void *q = InitQ(sizeof(TPersoana),MAX);
	GenereazaCoadaPers(q,4,0,10);
	AfiQ("coada neinversata\n",AfiPers,q);
	invC(q);
	AfiQ("coda inversata\n",AfiPers,q);

	DistrS(&stackOddID);
	DistrQ(&q);
	DistrQ(&queueOddID);
	DistrS(&stack);
	DistrQ(&queue);
	DistrQ(&qaux);
	DistrS(&stackGreaterDiam);

	return 0;
}