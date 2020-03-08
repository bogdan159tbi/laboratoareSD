/*  functii-tabHash.c - functii tabela hash */


#include "thash.h"

TH* IniTH(size_t M, TFHash fh)
{
    TH* h = (TH *) calloc(sizeof(TH), 1);
    if (!h) {
        printf("eroare alocare hash\n");
        return NULL;
    }

    h->v = (TLG *) calloc(M, sizeof(TLG));
    if(!h->v) {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;
    return h;
}

void DistrTH(TH** ah, TF fe)
{
    TLG * p, el, aux;
    
    //parcurgere cu pointeri
    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++) {
        //daca exista elemente corespunzatoare acestui hash
        //eliberam info din celula si apoi eliberam celula
        for(el = *p; el != NULL; ) {
            aux = el;
            el = el->urm;
            fe(aux->info);
            free(aux);
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}

void AfiTH(TH* ah, TF afiEl)
{
    TLG p, el;
    int i;
    for(i = 0; i < ah->M; i++) {
        p = ah->v[i];
        if(p) {
            printf("LISTA %d:\n",i);
            for(el = p; el != NULL; el = el->urm)
                afiEl(el->info);
            printf("\n");
        }
    }
}

//daca elementul exista functia intoarce 0
//altfel se incearca inserarea elementului si se intoarce rezultatul inserarii
int InsTH(TH*a, void* ae, TFCmp f)
{
    int cod = a->fh(ae), rez;
    TLG el;
    
    for(el = a->v[cod]; el != NULL; el = el->urm) {
        if (f(el->info, ae) == 1)
            return 0;
    }
    rez = InsLG(a->v+cod, ae); //reminder: a->v+cod <=> &a->v[cod]
    return rez;
}

void *ExistaTH(TH *a,void *ae,TFCmp f)
{
    int i;
    int cod = a->fh(ae);
    TLG el;
    for(el = a->v[cod]; el != NULL; el = el->urm)
    {
        if(f(el->info,ae) == 0)
            return el->info;
    }
    return NULL;
}

int ExtrTH(TH*a, void*ae, TFCmp f)
{
    int cod = a->fh(ae);
    TLG p,prev;

    for(prev = NULL,p = a->v[cod]; p != NULL;prev = p,p = p->urm)
    {
        if(f(p->info,ae) == 0)
        {
            prev->urm = p->urm;
            TLG aux = p;
            free(aux);
            return 1;
        }
    }
return 0;
}
