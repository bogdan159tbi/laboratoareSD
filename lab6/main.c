#include<stdio.h>
#include<stdlib.h>
#include "stack.h"
#include "queue.h"

int main()
{
	int n;
	scanf("%d",&n);
	int i;
	int *b;
	b = malloc(sizeof(int) * n);
	if(!b)
		return 0;
	
	TStack *stiva;
	stiva = initStack(sizeof(int),3*n);
	if(!stiva)
	{
		free(b);
		return 0;
	}
	for( i = 0 ;i < n;i++)
	{
		int x,*p;
		scanf("%d",&x);
		p = &x;
		push(stiva,p);
	}
	for( i = 0 ;i < n ;i++)
	{
		int y;
		scanf("%d",&y);
		
	}

	int *rez = calloc(n,sizeof(int));
	if(!rez)
	{
		free(b);
		DistrStack((void*)&stiva);
		return 1;
	}
	int nr ,elem = 0;
	int index = 0;
	i = 0;

	while( !VIDA(stiva) )
	{
	 int ok = 0;
	 elem = 0;
	 ok = top(stiva,&nr);
	 pop(stiva,&nr);
	 printf("%d\n",nr);
	 if(nr  == b[i])
	 	rez[i] = 1; 
	 else{
	 while(nr != b[i] && ok && !VIDA(stiva))
	 {
	 	elem++;
	 	ok = top(stiva,&nr);
	 	pop(stiva,&nr);
	 }
	 rez[index++] = elem;
	 }
	 i++;
	}

	for ( i = 0 ;i < n; i++)
		printf("%d ",rez[i]);

	free(b);
	free(rez);
	DistrStack((void*)&stiva);
	return 0;
}