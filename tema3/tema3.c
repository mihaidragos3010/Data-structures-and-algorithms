#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct fisier{
  char *nume;
  struct director *parinte;
  struct fisier *st;
  struct fisier *dr;
}TFisier, *ArbFisier;

typedef struct director{
  char *nume;
  struct director *parinte;
  struct fisier *fisiere;    
  struct director *directoare;
  struct director *dr;
  struct director *st;
}TDirector, *ArbDirector;

void InitDirector(TDirector *director,char *nume){
  director->nume=malloc(sizeof(char)* (strlen(nume)+1) );
  if(director->nume==NULL)
    return;
  strcpy(director->nume,nume);
  director->parinte=NULL;
  director->fisiere=NULL;
  director->directoare=NULL;
  director->st=NULL;
  director->dr=NULL;
}

 void InitFisier(TFisier *fisier,char *nume){
  fisier->nume=malloc(sizeof(char)* (strlen(nume)+1) );
  if(fisier->nume==NULL)
    return;
  strcpy(fisier->nume,nume);
  fisier->parinte=NULL;
  fisier->st=NULL;
  fisier->dr=NULL;
 }

void InitFileExplorer(ArbDirector *root){            //Functia initializeaza directorul radacina "root" al strcturii 
  (*root)=malloc(sizeof(TDirector));                 //si ii aloca memorie
  if( (*root) == NULL )
    return;
  (*root)->nume=NULL;
  (*root)->nume=malloc(10*sizeof(char));
  if( (*root)->nume == NULL){
    free((*root));
    return;
  }
  char s[]="root";
  (*root)->st=NULL;
  (*root)->dr=NULL;
  (*root)->fisiere=NULL;
  (*root)->directoare=NULL;
  (*root)->parinte=NULL;
  memcpy( (*root)->nume, s,5);
}

int CautareNumeFisiere(TFisier *fisier,char *nume){  //Functia returneaza 1 daca a fost gasit numele in arborele de fisiere
  if(fisier==NULL)
    return 0;
  if( strcmp(fisier->nume,nume) == 0 )
    return 1;
  if( strcmp(fisier->nume,nume) > 0)
    return CautareNumeFisiere(fisier->st,nume);
  else
    return CautareNumeFisiere(fisier->dr,nume);
}

int CautareNumeDirectoare(TDirector *director,char *nume){  //Functia returneaza 1 daca a fost gasit numele in arborele de directoare
  if(director==NULL)
    return 0;
  if( strcmp(director->nume,nume) == 0 )
    return 1;
  if( strcmp(director->nume,nume) > 0)
    return CautareNumeDirectoare(director->st,nume);
  else
    return CautareNumeDirectoare(director->dr,nume);
}

ArbDirector CD_Directoare(TDirector *director,char *nume){  //Functia functioneaza pe principiul functiei de cautare a unui element
  if(director==NULL)                                        //dar returneaza adresa directorului cautat
    return NULL;
  if( strcmp(director->nume,nume) == 0 )
    return director;
  if( strcmp(director->nume,nume) > 0)
    return CD_Directoare(director->st,nume);
  else
    return CD_Directoare(director->dr,nume);
}

int InserareFisier( ArbFisier *ArbFisier, TFisier *fisier, void *parinte){
  if( (*ArbFisier) == NULL ){
    fisier->parinte = parinte; //retine adresa directorului parinte
    TFisier *aux=NULL;
    aux=malloc(sizeof(TFisier));
    InitFisier(aux,fisier->nume);
    aux->parinte=fisier->parinte;
    (*ArbFisier)=aux;
    return 1;
  }

  if( strcmp( (*ArbFisier)->nume , fisier->nume ) == 0 ){
    return 0;
  }

  if( strcmp( (*ArbFisier)->nume , fisier->nume ) > 0 ){      //verific lexicografic numele cautat cu numele directorului actual 
                                                              //pentru a putea parcurge arborele in direcia corecta.
    InserareFisier(&((*ArbFisier)->st),fisier,parinte);       //Functia se bazeaza pe proprietatea arborilor binari de cautare.
  }

  if( strcmp((*ArbFisier)->nume , fisier->nume ) < 0 ){
    InserareFisier(&((*ArbFisier)->dr),fisier,parinte);
  }
  return 0;
}

int InserareDirector( ArbDirector *ArbDirector, TDirector *director, void *parinte){
  if( (*ArbDirector) == NULL ){
    director->parinte = parinte; //retine adresa directorului parinte 
    TDirector *aux=NULL;
    aux=malloc(sizeof(TDirector));
    InitDirector(aux,director->nume);
    aux->parinte=director->parinte;
    (*ArbDirector)=aux;
    return 1;
  }

  if( strcmp( (*ArbDirector)->nume , director->nume ) == 0 ){ //verific daca am gasit directorul cu numele cerut
    return 0;
  }

  if( strcmp( (*ArbDirector)->nume , director->nume ) > 0 ){  //verific lexicografic numele cautat cu numele directorului actual 
                                                              //pentru a putea parcurge arborele in direcia corecta.
    InserareDirector(&((*ArbDirector)->st),director,parinte); //Functia se bazeaza pe proprietatea arborilor binari de cautare.
  }

  if( strcmp((*ArbDirector)->nume , director->nume ) < 0 ){
    InserareDirector(&((*ArbDirector)->dr),director,parinte);
  }
  return 0;
}

void AfisareDirector(TDirector *director){                //Functia afiseaza arborele de directoare in ordine lexicografica
  if(director!=NULL){                                     //bazandu-se pe metoda SRD
    if(director->st != NULL)
      AfisareDirector(director->st);
    printf("%s ",director->nume);
    if(director->dr)
      AfisareDirector(director->dr);
  }
}
void AfisareFisier(TFisier *fisier){                      //Functia afiseaza arborele de fisiere in ordine lexicografica
  if(fisier!=NULL){                                       //bazandu-se pe metoda SRD
    AfisareFisier(fisier->st);
    printf("%s ",fisier->nume);
    AfisareFisier(fisier->dr);
  }
}
void distrugeFisier(TFisier **fisier){                    //Functia distruge o celula de timp fisier.
  free((*fisier)->nume);
  free(*fisier);
  *fisier=NULL;
}

int minDrFisier(ArbFisier fisiere,TFisier **max){         //Functia intoarce minimul din subarborele drept.
  if(fisiere->st == NULL && fisiere->dr != NULL){         //Este o functia jutatoare in eliminarea unui fisier.
    *max = fisiere;                                
    return 1;
  }
  if(fisiere->dr == NULL && fisiere->st == NULL){
    *max = fisiere;
    return 0;
  }
  if(fisiere->st != NULL)
    return minDrFisier(fisiere->st,max);
  return minDrFisier(fisiere->dr,max);
}

int minDrDirector(ArbDirector director,TDirector **max){  //Functia intoarce minimul din subarborele drept.
  if(director->st == NULL && director->dr != NULL){       //Este o functia ajutatoare in eliminarea unui director.
    *max = director;                                
    return 1;
  }
  if(director->dr == NULL && director->st == NULL){
    *max = director;
    return 0;
  }
  if(director->st != NULL)
    return minDrDirector(director->st,max);
  return minDrDirector(director->dr,max);
}

ArbFisier EliminareFisier(ArbFisier *fisiere, char *nume){
  if((*fisiere)==NULL)
    return *fisiere;
  if( strcmp(nume,(*fisiere)->nume) < 0)
    (*fisiere)->st=EliminareFisier(&(*fisiere)->st, nume);
    else
      if( strcmp(nume,(*fisiere)->nume) > 0 )
      (*fisiere)->dr=EliminareFisier(&(*fisiere)->dr,nume);
      else{
        if((*fisiere)->st==NULL && (*fisiere)->dr==NULL)
          return NULL;
          else if((*fisiere)->st == NULL){
            ArbFisier aux=(*fisiere)->dr;
            free( (*fisiere) );
            return aux;
          }
          else if((*fisiere)->dr == NULL){
            ArbFisier aux=(*fisiere)->st;
            free( (*fisiere) );
            return aux;
          }
          ArbFisier aux=NULL;
          minDrFisier( (*fisiere)->dr,&aux);
          strcpy( (*fisiere)->nume, aux->nume);
          (*fisiere)->dr=EliminareFisier( &(*fisiere)->dr,aux->nume);
      }
        return (*fisiere);
}


ArbDirector EliminareDirector(ArbDirector *directoare, char *nume){
  if((*directoare)==NULL)
    return *directoare;
  if( strcmp(nume,(*directoare)->nume) < 0)
    (*directoare)->st=EliminareDirector(&(*directoare)->st, nume);
    else
      if( strcmp(nume,(*directoare)->nume) > 0 )
      (*directoare)->dr=EliminareDirector(&(*directoare)->dr,nume);
      else{
        if((*directoare)->st==NULL && (*directoare)->dr==NULL)
          return NULL;
          else if((*directoare)->st == NULL){
            ArbDirector aux=(*directoare)->dr;
            free( (*directoare) );
            while( (*directoare)->fisiere != NULL)
            (*directoare)->fisiere=EliminareFisier(&(*directoare)->fisiere,(*directoare)->fisiere->nume);
            return aux;
          }
          else if((*directoare)->dr == NULL){
            ArbDirector aux=(*directoare)->st;
            free( (*directoare) );
            while( (*directoare)->fisiere != NULL)
            (*directoare)->fisiere=EliminareFisier(&(*directoare)->fisiere,(*directoare)->fisiere->nume);
            return aux;
          }
          ArbDirector aux=NULL;
          minDrDirector( (*directoare)->dr,&aux);
          strcpy( (*directoare)->nume, aux->nume);
          (*directoare)->dr=EliminareDirector( &(*directoare)->dr,aux->nume);
      }
        return (*directoare);
}

void pwd(TDirector *director){                //Functia parcurge structura de directoare pana la radacina "root" si se intoare
                                              //prin recursivitate pentru a afisa drumul pana la fisier/directorul prezent.
  if(director->parinte != NULL){
    pwd(director->parinte);
  }

  printf("/%s",director->nume);
  return;
}

int findFisier(TDirector* root,char *nume){     //Functia primeste intotdeauna ca parametru radacina "root" a structurii de arbori
                                                //si numele fisierului cautat.
  if(root == NULL)                              //In cazul in care se respecta conditia se va intoarce o valoarea diferita de 0 
    return 0;                                   //si 0 in caz contrar.
  if(CautareNumeFisiere(root->fisiere,nume)==1){
    printf("File %s found!\n",nume);
    pwd(root);
    printf("\n");
    return 1;
  }
  //aici tratam toate cazurile de parcurgere in cautarea unui fisier
  if(root->st == NULL && root->dr ==NULL && root->directoare==NULL)
    return  0;
  if(root->st==NULL && root->dr ==NULL && root->directoare != NULL)
    return findFisier(root->directoare,nume);
  if(root->st==NULL && root->dr != NULL && root->directoare ==NULL)
    return findFisier(root->dr,nume);
  if(root->st==NULL && root->dr != NULL && root->directoare !=NULL)
    return findFisier(root->dr,nume) + findFisier(root->directoare,nume);
  if(root->st!=NULL && root->dr == NULL && root->directoare ==NULL)
    return findFisier(root->st,nume);
  if(root->st!=NULL && root->dr == NULL && root->directoare !=NULL)
    return findFisier(root->st,nume)+findFisier(root->directoare,nume);
  if(root->st!=NULL && root->dr != NULL && root->directoare ==NULL)
    return findFisier(root->st,nume)+findFisier(root->dr,nume);
  if(root->st!=NULL && root->dr != NULL && root->directoare !=NULL)
    return findFisier(root->st,nume)+findFisier(root->directoare,nume)+findFisier(root->dr,nume);
  return 0;
}


int findDirector(TDirector* root,char *nume){   //Functia primeste intotdeauna ca parametru radacina arborelui "root" si parcurge
                                                //in adancime structura de directoare pana gaseste un director cu numele cerut.   
  if(root == NULL)                              //Functia returneaza o valoare diferita de 0 daca se respecta conditia si o valoare
    return 0;                                   //diferita de 0 in caz contrar
  if(CautareNumeDirectoare(root->directoare,nume)==1){
    printf("Directory %s found!\n",nume);
    pwd(root);
    printf("/%s",nume);
    printf("\n");
    return 1;
  }
  //aici se trateaza toate cazurile de parcurgere
  if(root->st == NULL && root->dr ==NULL && root->directoare==NULL)
    return  0;
  if(root->st==NULL && root->dr ==NULL && root->directoare != NULL)
    return findDirector(root->directoare,nume);
  if(root->st==NULL && root->dr != NULL && root->directoare ==NULL)
    return findDirector(root->dr,nume);
  if(root->st==NULL && root->dr != NULL && root->directoare !=NULL)
    return findDirector(root->dr,nume) + findDirector(root->directoare,nume);
  if(root->st!=NULL && root->dr == NULL && root->directoare ==NULL)
    return findDirector(root->st,nume);
  if(root->st!=NULL && root->dr == NULL && root->directoare !=NULL)
    return findDirector(root->st,nume)+findDirector(root->directoare,nume);
  if(root->st!=NULL && root->dr != NULL && root->directoare ==NULL)
    return findDirector(root->st,nume)+findDirector(root->dr,nume);
  if(root->st!=NULL && root->dr != NULL && root->directoare !=NULL)
    return findDirector(root->st,nume)+findDirector(root->directoare,nume)+findDirector(root->dr,nume);
  return 0;
}

void disreugereFisiere(TFisier**fisiere){

  if((*fisiere)->st==NULL && (*fisiere)->dr==NULL){
    free((*fisiere)->nume);
    free(*fisiere);
    return;
  }
  distrugeFisier(&((*fisiere)->st));
  distrugeFisier(&((*fisiere)->dr));

  return ;
}

int main(){
  char *inst;
  ArbDirector root=NULL;
  ArbDirector radacina=NULL;
  InitFileExplorer(&root);
  radacina=root;
  inst=malloc(sizeof(char)*20);
  if(inst==NULL)
      return -1;
  while(scanf("%s",inst)!=EOF){
      if(strcmp(inst,"touch")==0){
        TFisier fisier;
        scanf("%s", inst);
        InitFisier(&fisier,inst);
        if(CautareNumeFisiere(root->fisiere,fisier.nume)==1){
          printf("File %s already exists!\n", fisier.nume);
          continue;
        }
        if(CautareNumeDirectoare(root->directoare,fisier.nume)==1){
          printf("Directory %s already exists!\n", fisier.nume);
          continue;
        }
        InserareFisier( &(root->fisiere),&fisier,root);
      }

      if(strcmp(inst,"mkdir")==0){
        TDirector director;
        scanf("%s", inst);
        InitDirector(&director,inst);
        if(CautareNumeFisiere(root->fisiere,director.nume)==1){
          printf("File %s already exists!\n", director.nume);
          continue;
        }
        if(CautareNumeDirectoare(root->directoare,director.nume)==1){
          printf("Directory %s already exists!\n", director.nume);
          continue;
        }
        InserareDirector( &(root->directoare),&director,root);
      }

      if(strcmp(inst,"ls")==0){
        AfisareDirector(root->directoare);
        AfisareFisier(root->fisiere);
        printf("\n");
      }

      if(strcmp(inst,"rm")==0){
        scanf("%s", inst);
        if(CautareNumeFisiere(root->fisiere,inst)==0)
          printf("File %s doesn't exist!\n",inst);
        root->fisiere=EliminareFisier(&(root->fisiere),inst);
      }

      if(strcmp(inst,"rmdir")==0){
        scanf("%s", inst);
        if(CautareNumeDirectoare(root->directoare,inst)==0)
          printf("Directory %s doesn't exist!\n",inst);
        root->directoare=EliminareDirector(&(root->directoare),inst);
      }

      if(strcmp(inst,"cd")==0){
        scanf("%s", inst);
        if(strcmp(inst,"..")==0){
          if(root->parinte != NULL)
          root=root->parinte;
        }
        else{
          if(CautareNumeDirectoare(root->directoare,inst)==0)
            printf("Directory not found!\n");
          else
            root=CD_Directoare(root->directoare,inst);
        }
      }

      if(strcmp(inst,"pwd")==0){
        pwd(root);
        printf("\n");
      }

      if(strcmp(inst,"find")==0){
        scanf("%s", inst);
        if( strcmp(inst,"-f")==0){
          scanf("%s", inst);
          if(findFisier(radacina,inst)==0)
            printf("File %s not found!\n",inst);
        }
        else{
          scanf("%s", inst);
          if(findDirector(radacina,inst)==0)
            printf("Directory %s not found!\n",inst);
        }
      }
  }
  free(root->nume);
  free(inst);
  free(root);
  return 0;
}
