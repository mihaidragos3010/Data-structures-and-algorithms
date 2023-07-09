#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "tlg.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie afisare/eliberare un element */
typedef int (*TFHash)(char*);

typedef struct
{
    int M;
    TFHash fh;
    TLG *v;
} TH;

/* functii tabela hash */
TH* InitTH(size_t M, TFHash fh);
void DistrTH(TH**aa, TF fe);
//void AfiTH(TH*a, TF afiEl);
int InsTH(TH*a, void*ae, TFCmp f);
void AfiTH(TH* ah,TF afi_elem);
int CautareElemNrAp(TLG L,char *com1);
void AfisareTabelaHash(TH *h,void(*afiElem)(TElem));
void AfisareTabelaHashNrAp(TH *h,void(*afiElemNrAp)(TElem,char*),char *com1);
void AfisareTabelaHashSpecific(TH *h,void(*afiElemSpecific)(TElem),char *com1,char *com2);
#endif