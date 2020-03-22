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
// return medium age for the pers in the queue
float FC1(void *q)
{
	float age = 0;
	float nr = 0;
	TPersoana *p;
	while (!VidaQ(q))
	{
		ExtrQ(q,p);
		nr++;
		age += p->varsta;
	}
	return age/nr;
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
	AfiQ("",AfiPers,queue);
	printf("stiva are %d elem\n",lenSt);
	AfiStack("\nstiva cu elem:\n",AfiPers,stack);

	DistrS(&stack);
	DistrQ(&queue);

	return 0;
}