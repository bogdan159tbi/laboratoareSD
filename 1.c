#include "lista.h"


int main()
{
	TLista l;
	int len=0;
	l=readList(&len);
	deleteElem(&l,2);
	showList(l);

	return 0;
}