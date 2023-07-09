#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "thash.h"
typedef int (*TFHash)(char *);

//structuri



//functii



int codHash(char *cuv)
{
    if(cuv[0]>='a' && cuv[0]<='z')
	    return cuv[0] - 'a';
    if(cuv[0]>='A' && cuv[0]<='Z')
	    return cuv[0] - 'A';
    return 0;
}

TH* InserareCuvant(TH *h,char *cuv){
    int cod=codHash(cuv);
    if( h->v[cod] == NULL){
        Date *date;
        TLG aux;
        TElem *element;
        date=AlocareDate(cuv);
        aux=AlocCelulaTLG((void*)date);
        element=AlocareElem(&aux);
        InsOrdElem(&(h->v[cod]),(void*)element);
    }
    else
    if(CautareOriz(h->v[cod],cuv)==1){
        Date *date;
        TLG aux;
        date=AlocareDate(cuv);
        aux=AlocCelulaTLG((void*)date);
        CautareVert(h->v[cod],aux->info);
    }
    if(CautareOriz(h->v[cod],cuv)==0){
        Date *date;
        TLG aux;
        TElem *element;
        date=AlocareDate(cuv);
        aux=AlocCelulaTLG((void*)date);
        element=AlocareElem(&aux);
        InsOrdElem(&(h->v[cod]),(void*)element);
    }
    return h;
}

char *filtrareProp(char *cuv)
{   int i;
    for (i = 0; i <= strlen(cuv); i++)
    {
        if (cuv[i] == '\n')
        {
            strcpy(cuv + i, cuv + i + 1);
            i--;
        }
        if (cuv[i] == '.')
        {
            strcpy(cuv + i, cuv + i + 1);
            i--;
        }
        if (cuv[i] == ',')
        {
            strcpy(cuv + i, cuv + i + 1);
            i--;
        }
    }
    return cuv;
}

char *filtrareCuv(char *cuv)
{   int i;
    if(cuv)
    for (i = 0; i <= strlen(cuv); i++)
    {
        if (cuv[i] == '\n')
        {
            strcpy(cuv + i, cuv + i + 1);
            i--;
        }
        if (cuv[i] == '.')
        {
            strcpy(cuv + i, cuv + i + 1);
            i--;
        }
        if (cuv[i] == ' ')
        {
            strcpy(cuv + i, cuv + i + 1);
            i--;
        }
    }
    return cuv;
}

/*
TLG citesteListaInsert(char *numefisier)
{
    FILE *f;
    char *line = NULL;
    size_t len = 0;
    TLG L = NULL; 
    f = fopen(numefisier, "rt");
    if (f == NULL)
        return NULL;
    while (getline(&line, &len, f) != -1)
    {
        char *inst = strtok(line, " ");
        if (strcmp(inst, "insert") == 0)
        {
            
            char *cuv = strtok(NULL, " ");
            while (cuv != NULL)
            {   cuv = filtrareCuv(cuv);
                if(strlen(cuv)>=3){
               Date *date = malloc(sizeof(Date));
                if (date == NULL)
                    return L;
                strcpy(date->cuv, cuv);
                    
                    if(CautareDate(L,date,compDate) == 0){
                        date->nr_ap=1;
                        Ins_IncLG(&L, (void *)date);
                    }
                //afisareDate(L->info);
                }
                cuv = strtok(NULL, " ");
            }
            //printf("\n");
        }
    }
    fclose(f);
    return L;
}
*/

TLG sortlistTLGd(TLG *L){
    TLG i,j;
    for(i=*L;i->urm;i=i->urm){
        for(j=i->urm;j;j=j->urm){
            if(compDateLung(i->info,j->info)==1){
                swichDate(&i,&j);
            }
            if(compDateLung(i->info,j->info)==0)
                if(compDateNrAp(i->info,j->info)==1)
                    swichDate(&i,&j);
        }
    }
    return *L;
}

// TLG sortlistTLG(TLG *L){
//     TLG i,j;
//     for(i=*L;i->urm;i=i->urm){
//         for(j=i->urm;j;j=j->urm){
//             if(compDateLung(i->info,j->info)==1){
//                 swichDate(&i,&j);
//             }
//             if(compDateLung(i->info,j->info)==0)
//                 if(compDateNrAp(i->info,j->info)==1)
//                     swichDate(&i,&j);
//         }
//     }
//     return *L;
// }
TH* InitializareTH(int M,int (*codHash) (char*)){
    TH *h=malloc(sizeof(TH));
    if(h==NULL)
        return NULL;
    h->M=M;
    h->fh=codHash;
    h->v=(TLG*)calloc(M,sizeof(TLG));
    if(!h->v) {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(h);
        return NULL;
    }
    
    return h;
}

int main(int argc,char **argv)
{   FILE  *f;
    f=fopen(argv[1],"rt");
    int M='Z'-'A'+1;
    TH *h=NULL;
    //char * line = NULL;
	size_t len = 0;
    h=InitializareTH(M,codHash);
    char *inst;
    inst=malloc(sizeof(char)*20);
    if(inst==NULL)
        return -1;
    while(fscanf(f,"%s",inst)!=EOF){
        if(strcmp(inst,"insert")==0){
            char *fraza;
            fraza=malloc(256*sizeof(char));
            getline(&fraza,&len,f);
            fraza=filtrareProp(fraza);
            char *cuv;
            cuv=strtok(fraza," ");
                while(cuv){
                cuv=filtrareCuv(cuv);
                if(strlen(cuv)>=3 && (cuv[0]<'0' || cuv[0]>'9') ){
                    h=InserareCuvant(h,cuv);
                }
                cuv=strtok(NULL, " ");
            }
        }

        if(strcmp(inst,"print")==0){
            char *com1,*com2;
            char *fraza=malloc(256*sizeof(char));
            getline(&fraza,&len,f);
            fraza=filtrareProp(fraza);
            com1=strtok(fraza," ");
            com2=strtok(NULL," ");
            com1=filtrareCuv(com1);
            com2=filtrareCuv(com2);
            if(com1==NULL && com2==NULL){
                AfisareTabelaHash(h,afisareElem);
            }
            if(com1!=NULL && com2==NULL){
                AfisareTabelaHashNrAp(h,afisareElemNrAp,com1);
            }
            if(com1!=NULL && com2!=NULL && (*com2-'0')>=3){
                AfisareTabelaHashSpecific(h,afisareElem,com1,com2);
            }
        }
    }
    

    return 0;
}