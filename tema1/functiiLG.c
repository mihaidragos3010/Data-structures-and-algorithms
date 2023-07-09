/*--- functiiLG.c -- operatii de baza pentru lista simplu inlantuita generica---*/
#include "tlg.h"
#include "thash.h"

Date* AlocareDate(char *cuv){
    Date *date;
    date=malloc(sizeof(Date));
    if(!date)
        return NULL;
    strcpy(date->cuv,cuv);
    date->nr_ap=1;
    return date;
}

TElem* AlocareElem(TLG *aux){
    TElem *element;
    element=malloc(sizeof(TElem));
    if(!element)
        return NULL;
    element->L= (*aux);
    element->lung= strlen( ((Date*)(*aux)->info)->cuv );
    return element;
}

TLG AlocCelulaTLG(void *x){
    TLG aux=(TLG)malloc(sizeof(TLG));
    if(!aux)
        return NULL;
    aux->info=x;
    aux->urm=NULL;
    return aux;
}

void swichDate(TLG *x,TLG *y){
    char aux[20];
    strcpy( aux, ((Date*)( (*x)->info))->cuv);
    strcpy( ((Date*)( (*x)->info))->cuv, ((Date*)( (*y)->info))->cuv);
    strcpy( ((Date*)( (*y)->info))->cuv, aux);
    int AUX;
    AUX=((Date*)( (*x)->info))->nr_ap;
    ((Date*)( (*x)->info))->nr_ap=((Date*)( (*y)->info))->nr_ap;
    ((Date*)( (*y)->info))->nr_ap=AUX;
}

int compDate(void* x,void* y){
    Date *date1=(Date*)x;
    Date *date2=(Date*)y;
    if(strcmp(date1->cuv,date2->cuv)==0)
        return 1;
    return 0;
}

int compDateLexico(void* x,void* y){
    Date *date1=(Date*)x;
    Date *date2=(Date*)y;
    int i;
	for(i=0; i<strlen(date1->cuv) && i<strlen(date2->cuv);i++){
		if(date1->cuv[i] > date2->cuv[i])
			return 1;
		if(date1->cuv[i] < date2->cuv[i])
			return -1;
	}
    return 0;
}
int compDateNrAp(void* x,void* y){
    Date *date1=(Date*)x;
    Date *date2=(Date*)y;
    if(date1->nr_ap > date2->nr_ap)
        return 1;
    if(date1->nr_ap == date2->nr_ap)
        return 0;
    if(date1->nr_ap < date2->nr_ap)
        return -1;
    return 0;
}
int compDateLung(void* x,void* y){
    Date *date1=(Date*)x;
    Date *date2=(Date*)y;
    if(strlen(date1->cuv) > strlen(date2->cuv))
        return 1;
    if(strlen(date1->cuv) == strlen(date2->cuv))
        return 0;
    if(strlen(date1->cuv) < strlen(date2->cuv))
        return -1;
    return 0;
}

TLG sortlistTLG(TLG *L){
    TLG i,j;
    for(i=*L;i->urm;i=i->urm){
        for(j=i->urm;j;j=j->urm){
                if(compDateNrAp(i->info,j->info)==-1)
                    swichDate(&i,&j);
				if(compDateNrAp(i->info,j->info)==0 && compDateLexico(i->info,j->info)==1)
                    swichDate(&i,&j);
        }
    }
    return *L;
}

void afisareDate(void *element)
{
    Date *date = (Date *)element;
    printf(", %s/%d", date->cuv, date->nr_ap);
}

void afisareDate1(void *element)
{
    Date *date = (Date *)element;
    printf("%s/%d", date->cuv, date->nr_ap);
}

void afisareDateNrAp(void *element,char* com1)
{
    Date *date = (Date *)element;
    if(date->nr_ap<=(*com1)-'0'  && date!=NULL)
    printf(", %s/%d", date->cuv, date->nr_ap);
}

int afisareDate1NrAp(void *element,char *com1)
{   if(element!=NULL){
        Date *date = (Date *)element;
        if(date->nr_ap<=(*com1)-'0' && date!=NULL){
            printf(" %s/%d", date->cuv, date->nr_ap);
            return 1;
        }
    }
    return 0;
}

void afisareElem(TElem el)
{
    printf("(%d:", el.lung);
	afisareDate1( el.L->info );
	el.L=el.L->urm;
	for(;el.L;el.L=el.L->urm)
		afisareDate( el.L->info );
	printf(")");
}
int CautareDateNrAp(TElem el,char *com1){
    for(;el.L;el.L=el.L->urm)
        if( ((Date*)(el.L->info))->nr_ap<=(*com1)-'0' )
            return 1;
    return 0;
}

void afisareElemNrAp(TElem el,char *com1)
{   int ok=CautareDateNrAp(el,com1);
    if(ok==1)
    printf("(%d:", el.lung);
    for(;el.L;el.L=el.L->urm){
	    
        if(afisareDate1NrAp( el.L->info ,com1)==1)
            break;
        
    }
    //el.L=el.L->urm;
    if(el.L==NULL) 
         return;
    el.L=el.L->urm;
	for(;el.L;el.L=el.L->urm){
		afisareDateNrAp( el.L->info ,com1);
        }
    if(ok==1)
	printf(")");
}

int FcompElem(void *x,void *y){
	TElem *el1,*el2;
	el1= (TElem*)(x);
	el2= (TElem*)(y);
	int a=el1->lung;
	int b=el2->lung;
	return a-b;
}

int InsOrdElem(TLG *L,void* element){
	TLG p,ant,aux;
	for(ant=NULL,p=*L;p&&(FcompElem(p->info,element))<0;ant=p,p=p->urm);
	aux=AlocCelulaTLG(element);
	if(aux==NULL){
		return 0;
		printf("Nu s-a reusit alocarea aux\n");
	}
	if(ant!=NULL){
		aux->urm=p;
		ant->urm=aux;
	}
	else{
		aux->urm=p;
		*L=aux;
	}
	return 1;
}
int numar_elementeTLG(TLG L){
    int nr;
    nr=0;
    for(;L;L=L->urm){
        nr++;
    }
    return nr;
}

int CautareOriz(TLG L,char *cuv){
	
	if(L!=NULL)
		for(;L;L=L->urm)
			if(strlen(cuv)==((TElem*)(L->info))->lung)
				return 1;
	return 0;
}

int CautareDate(TLG L,Date *date,int (*comp)(void*,void*)){
	if(L != NULL)
	for(;L != NULL;L=L->urm){
		if( comp( L->info , date )==1){
			((Date*)( L->info))->nr_ap++;
			return 1;
		}
	}
	return 0;
}

int CautareVert(TLG L,void *element){
	Date *date=(Date *)element;
	if(L!=NULL)
		for(;L;L=L->urm)
			if(strlen(date->cuv)==((TElem*)(L->info))->lung){
				if(CautareDate(((TElem*)(L->info))->L,date,compDate)==0){
					InsOrdElem( &(((TElem*)(L->info))->L), element);
                    ((TElem*)(L->info))->L=sortlistTLG(&(((TElem*)(L->info))->L));
					return 0;
				}
				else{
					((TElem*)(L->info))->L=sortlistTLG(&(((TElem*)(L->info))->L));
					return 1;
				}
				
			}
	return 0;
}
int Ins_IncLG(TLG* aL, void* ae)
{
	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0;

	aux->info = ae;
	aux->urm = *aL;
	*aL = aux;

	return 1;
}

void DistrugeLG(TLG* aL, TF free_elem) /* distruge lista */
{
	while(*aL != NULL)
    {
        TLG aux = *aL;     /* adresa celulei eliminate */
        if (!aux)
            return;

        free_elem(aux->info);  /* elib.spatiul ocupat de element*/
        *aL = aux->urm;    /* deconecteaza celula din lista */
        free(aux);   /* elibereaza spatiul ocupat de celula */
    }
}

size_t LungimeLG(TLG* a)      /* numarul de elemente din lista */
{
	size_t lg = 0;
	TLG p = *a; 

     /* parcurge lista, numarand celulele */
	for (; p != NULL; p = p->urm)
        lg++;

	return lg;
}

void Afisare(void* L)
{	TLG *aL = (TLG*)L;
	if(!*aL) {
        printf("Lista vida\n");
        return;
    }

	printf("[\n");
	for(; *aL; aL = &(*aL)->urm) {
		afisareDate((*aL)->info);
    }
	printf("]\n");
}
