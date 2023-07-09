/*-- tlg.h --- LISTA SIMPLU INLANTUITA GENERICA ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct
{
    char cuv[20];
    int nr_ap;
} Date;

typedef struct celulag
{
  void* info;           /* adresa informatie */
  struct celulag *urm;   /* adresa urmatoarei celule */
} TCelulaG, *TLG; /* tipurile Celula, Lista  */

typedef struct
{
    int lung;
    TLG L;
} TElem;

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie afisare/eliberare un element */

/* functii lista generica */
int Ins_IncLG(TLG*, void*);  /*- inserare la inceput reusita sau nu (1/0) -*/
void DistrugeLG(TLG* aL, TF fe); /* distruge lista */
/* afiseaza elementele din lista, folosind o functie de tip TFAfi */
void Afisare(void*);

Date* AlocareDate(char *cuv);
TElem* AlocareElem(TLG *aux);
TLG AlocCelulaTLG(void *x);
int compDate(void* x,void* y);
int compDateNrAp(void* x,void* y);
int compDateLung(void* x,void* y);

int numar_elementeTLG(TLG L);
int CautareOriz(TLG L,char *cuv);
int CautareVert(TLG L,void *element);

void swichDate(TLG *x,TLG *y);
int CautareDate(TLG,Date*,int (*comp)(void*,void*));
int compDate(void* x,void* y);
void afisareDate(void *element);
void afisareElem(TElem el);
int FcompElem(void *x,void *y);
int InsOrdElem(TLG *L,void* element);
TLG sortlistTLG(TLG *L);
int compDateLexico(void* x,void* y);
int CautareDateNrAp(TElem el,char *com1);

void afisareElemNrAp(TElem el,char *com1);
void afisareDateNrAp(void *element,char* com1);
int afisareDate1NrAp(void *element,char *com1);
#endif
