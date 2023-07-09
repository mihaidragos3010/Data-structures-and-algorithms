//Mihai Dragos-Andrei Grupa312CB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct celst
{   struct celst *urm; /* adr.urmatoarei celule */
    void* info; /* adresa informatie */
} TCelSt, *ACelSt;

typedef struct stiva
{   int dime; /* dim.element */
    ACelSt vf; /* adresa celulei din varf */
} TStiva, *ASt;

typedef struct cel /* dimensiune variabila */
{   struct cel * urm;
    void* info;
} TCelC, *ACelC;

typedef struct coada
{   int dime; /* dim.element */
    ACelC ic, sf; /* adr.prima, ultima celula */
} TCoada, *AC;
//Stiva
void* InitS(int d);
int Pop(void* s, void* ae);
int Push(void* s,void* ae);
void distrugereS(TStiva *s);
//Coada
void* InitC(int d);
int InserareC(void *c,void* ae);
int ExtragereC(void *c,void* ae);
void distrugereC(TCoada *c);