//Mihai Dragos-Andrei Grupa312CB
#include "functiiStiveSiCozi.h"

// Functii Stiva
void* InitS(int d) {
  TStiva* s;
  s = (ASt)malloc(sizeof(TStiva));
  if (!s) return NULL;
  s->dime = d;
  s->vf = NULL;
  // TStiva aux=*s;
  // free(s->vf);
  // free(s);
  return s;
}

int Push(void* s, void* ae) {
  ACelSt aux = (ACelSt)malloc(sizeof(TCelSt));
  if (!aux) return 0;
  aux->info = malloc(sizeof(((TStiva*)s)->dime + 16));
  if (aux->info == NULL) return 0;
  memcpy(aux->info, ae, ((TStiva*)s)->dime);
  aux->urm = ((TStiva*)s)->vf;
  ((TStiva*)s)->vf = aux;
  // free(aux->info);
  // free(aux);
  return 1;
}

int Pop(void* s, void* ae) {
  if (((TStiva*)s)->vf == NULL) return 0;
  memcpy(ae, ((TStiva*)s)->vf->info, ((TStiva*)s)->dime);
  ACelSt aux = ((TStiva*)s)->vf;
  ((TStiva*)s)->vf = aux->urm;
  ////free(aux->info);
  ////free(aux);
  return 1;
}

// Functii Coada

void* InitC(int d) {
  AC c;
  c = (AC)malloc(sizeof(TCoada));
  if (!c) return NULL;
  c->dime = d;
  c->ic = NULL;
  c->sf = NULL;
  return c;
}

int InserareC(void* c, void* ae) {
  ACelC aux = malloc(sizeof(TCelC));
  if (!aux) return 0;
  aux->info = malloc(sizeof(((TCoada*)c)->dime));
  if (aux->info == NULL) return 0;
  memcpy(aux->info, ae, ((TCoada*)c)->dime);
  aux->urm = NULL;

  if (((TCoada*)c)->ic == NULL) {
    ((TCoada*)c)->ic = aux;
    ((TCoada*)c)->sf = aux;
    return 1;
  }
  if (((TCoada*)c)->ic != NULL) {
    ((TCoada*)c)->sf->urm = aux;
    ((TCoada*)c)->sf = aux;
    return 1;
  }
  return 1;
}

int ExtragereC(void* c, void* ae) {
  ACelC aux;
  int ok = 0;
  TCoada* a = (TCoada*)c;
  if (a->ic == a->sf) ok = 1;
  aux = a->ic;
  a->ic = aux->urm;
  memcpy(ae, aux->info, a->dime);
  //// free(aux->info);
  //// free(aux);
  if (ok == 1) {
    a->ic = NULL;
    a->sf = NULL;
  }
  return 1;
}