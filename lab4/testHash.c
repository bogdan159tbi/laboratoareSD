/*-- testHash.c  */
#include <stdio.h>
#include "tlg.h"
#include "thash.h"
#include <string.h>

typedef struct {
	char titlu[50];
	char autor[30];
	char editura[30];
} TCarte;

int codHash(void * element)
{
	TCarte * carte = (TCarte *) element;
	char * autor = carte->autor;
	return *autor - 'A';
}

void afisareCarte(void * element)
{
	TCarte * carte = (TCarte *) element;
	printf("%s - %s - %s\n", carte->autor, carte->titlu, carte->editura);
}

TLG citesteListaCarti(char * numeFisier) {
	FILE *f;
	char * line = NULL;
	size_t len = 0;
	TLG L = NULL;

	f = fopen(numeFisier, "rt");
	if (f == NULL)
		return NULL;

	while (getline(&line, &len, f) != -1) {
		char * autor = strtok(line, ":");
		char * titlu = strtok(NULL, ":");
		char * editura = strtok(NULL, ":");

		if (editura[strlen(editura) - 1] == '\n')
			editura[strlen(editura) - 1] = '\0';

		TCarte * carte = malloc(sizeof(TCarte));
		if (carte == NULL)
			return L;

		strcpy(carte->autor, autor);
		strcpy(carte->titlu, titlu);
		strcpy(carte->editura, editura);
		InsLG(&L, (void *) carte);
    }
	fclose(f);
	return L;
}

int cmpCarte(void * e1, void * e2)
{
	TCarte * carte1 = (TCarte *) e1;
	TCarte * carte2 = (TCarte *) e2;

	if (strcmp(carte1->titlu, carte2->titlu) != 0)
		return 0;

	if (strcmp(carte1->autor, carte2->autor) != 0)
		return 0;

	if (strcmp(carte1->editura, carte2->editura) != 0)
		return 0;

	return 1;
}

TH * GenerareHash(TLG listaCarti)
{
    TH *h = NULL;
	TLG p;
    TCarte * carte;
	int rez;

	//calcul dimensiuni maxime pt tabela hash
	size_t M = ('Z'-'A');

	//initializare tabela hash
	h = (TH *) IniTH(M, codHash);
	if(h == NULL)
		return NULL;

	for(p = listaCarti; p != NULL; p = p->urm) {
        carte = (TCarte *) malloc(sizeof(TCarte));
        if(carte == NULL)
						return h;

        memcpy(carte, p->info, sizeof(TCarte));
	rez = InsTH(h, carte, cmpCarte);
        if(!rez) {
						free(carte);
						return h;
		}
	}

	return h;
}
int cartiScrise(TH* h,char *autor)
{
    int i;
    TLG p;
    int nr = 0;
    for(i = 0;i < h->M; i++)
    {
        p = h->v[i];
        for(;p != NULL ; p = p->urm)
            {  TCarte *c = (TCarte*)p->info;
               if(strcmp(c->autor,autor) == 0)
                nr++;
            }
    }
    return nr;
}

int main()
{
	// Citeste o lista de carti din fisier
	TLG listaCarti = citesteListaCarti("carti.txt");
	if (listaCarti == NULL) {
		printf("Lista nu a putut fi generata\n");
        return 0;
	}

	printf("=========== LISTA CARTI ===========\n");
	Afisare(&listaCarti, afisareCarte);

	TH * h = NULL;
	h = GenerareHash(listaCarti);
	if (h == NULL) {
		printf("Tabela hash nu a putut fi generata\n");
        return 0;
	}
	/*
	printf("\n\n=========== TABELA HASH ===========\n");

	printf("\n\n=========== EXERCITIUL 1 ===========\n");
	// TODO: APEL EXERCITIU 1

	printf("\n\n=========== EXERCITIUL 2 ===========\n");
	// TODO: APEL EXERCITIU 2

	printf("\n\n=========== EXERCITIUL 3 ===========\n");
	// TODO: APEL EXERCITIU 3

	printf("\n\n=========== BONUS ===========\n");
	// TODO: APEL BONUS
	*/
	AfiTH(h,afisareCarte);
  	Distruge(&listaCarti, free);
	DistrTH(&h, free);
  	return 0;
}
