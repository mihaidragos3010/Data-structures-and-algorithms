/*  functii-tabHash.c - functii tabela hash */


#include "thash.h"

TH* InitTH(size_t M, TFHash fh)
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

void DistrTH(TH** ah, TF elib_elem)
{
    TLG * p, el, aux;

    /* parcurgere cu pointeri */
    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++) {
        /* daca exista elemente corespunzatoare acestui hash
         * eliberam info din celula si apoi eliberam celula */
        for(el = *p; el != NULL; ) {
            aux = el;
            el = el->urm;
            elib_elem(aux->info);
            free(aux);
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}

void AfiTH(TH* ah,TF afi_elem)
{
    TLG p, el;
    int i;
    for(i = 0; i < ah->M; i++) {
        p = ah->v[i];
        if(p) {
            printf("LISTA %d:\n",i);
            for(el = p; el != NULL; el = el->urm){
                printf("cuv de lung %d", ((TElem*)(el->info))->lung );
                afi_elem(el->info);
            }
                
            printf("\n");
        }
    }
}

/* daca elementul exista functia intoarce 0
 *altfel se incearca inserarea elementului si se intoarce rezultatul inserarii */
int InsTH(TH*a, void* ae, TFCmp fcmp)
{
    int cod = a->fh(ae), rez;
    TLG el;

    for(el = a->v[cod]; el != NULL; el = el->urm) {
        if (fcmp(el->info, ae) == 1)
            return 1;
    }
    rez = Ins_IncLG(a->v+cod, ae); /* reminder: a->v+cod <=> &a->v[cod] */
    return rez;
}

void AfisareTabelaHash(TH *h,void(*afiElem)(TElem)){
    int cod;
    TLG p;
    for(cod=0;cod<h->M;cod++)
        if(h->v[cod]){
            printf("pos %d: ",cod);
            for(p=h->v[cod];p!=NULL;p=p->urm)
                afiElem( (*((TElem*) (p->info) )));
            printf("\n");
        }
}
int CautareElemNrAp(TLG L,char *com1){
    TLG p;
    for(p=L;p!=NULL;p=p->urm)
        if(CautareDateNrAp ((*((TElem*) (p->info) )),com1) == 1)
            return 1;
    return 0;
}

void AfisareTabelaHashNrAp(TH *h,void(*afiElemNrAp)(TElem,char*),char *com1){
    int cod;
    TLG p;
    for(cod=0;cod<h->M;cod++)
        if(h->v[cod] && CautareElemNrAp (h->v[cod],com1)==1 ){
            printf("pos%d: ",cod);
            for(p=h->v[cod];p!=NULL;p=p->urm)
                afiElemNrAp( (*((TElem*) (p->info) )),com1);
            printf("\n");
        }
}

void AfisareTabelaHashSpecific(TH *h,void(*afiElemSpecific)(TElem),char *com1,char *com2){
    int cod;
    TLG p;
    cod=h->fh(com1);
    if(h->v[cod]){
        for(p=h->v[cod];p!=NULL && ((TElem*)p->info)->lung!=((*com2)-'0');p=p->urm);
        afiElemSpecific( (*((TElem*) (p->info) )) );
        printf("\n");
    }
}