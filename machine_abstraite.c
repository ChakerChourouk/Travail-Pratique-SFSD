#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "ANP.h"

//=========================================================================================================================================
// machine abstraite :
//=========================================================================================================================================

// - proceédure qui renvoie le descripteur vers le fichier ouvert selon mode :-------------------------------------------------------------
void ouvrir ( FILE **f,char nomf[30],char mode[3]) {
  *f=fopen(nomf,mode);
}

// - proceédure qui ferme un fichier déja ouvert :-----------------------------------------------------------------------------------------
void fermer (FILE *f) {
  fclose(f);
}

// - fonction qui permet de renvoyer la n'eme caracteristique de l'entete du fichier f :---------------------------------------------------
int entete(FILE *f,int n){
  entet ent;
  if (f!=NULL){
     fseek(f,0,SEEK_SET);
     fread(&ent,sizeof(entet),1,f);

     switch (n){
       case 1 :
         return (ent.nbr_blocs);
       case 2:
         return (ent.libre);
       default :
          printf("caractérestique non existante\n\n");
       return 0;
    }
  }else{
     printf("erreur dans l'ouverture du fichier \n\n");
     return 1;
   }
}

// - procedure permettant d'affecter car à la n'ieme caracteristique du fichier f :----------------------------------------------------------
void aff_entete(FILE *f,int n,int car){
entet ent;
if (f!=NULL){
fseek(f,0,SEEK_SET);
fread(&ent,sizeof(ent),1,f);
switch (n){
 case 1 :
(ent.nbr_blocs=car);
fseek(f,0,SEEK_SET);
fwrite(&ent,sizeof(ent),1,f);
break;
case 2:
(ent.libre=car);
fseek(f,0,SEEK_SET);
fwrite(&ent,sizeof(ent),1,f);
break;
}
}else {
printf("erreur dans l'ouverture du fichier \n\n");
}
}

// - fonction qui permet de copier le contenu du  i'éme bloc du fichier pointé par f dans buf :-----------------------------------------------

int LireDir(FILE *f,int i,buffer * buf){
   if (f!=NULL){
      fseek(f,sizeof(entet)+(i-1)*sizeof(tbloc),SEEK_SET);
      if(fread(buf,sizeof(buffer),1,f));
      return 0;
   } else {
     return 1;
   }
}

// - fonction qui permet d'ecrire le contenu du buffer buf dans le i'éme bloc du fichier pointé par f :---------------------------------------

int EcrireDir(FILE *f,int i, buffer *buf){
  if (f!=NULL){
      fseek(f,sizeof(entet)+(i-1)*sizeof(tbloc),SEEK_SET);
      fwrite(buf,sizeof(buffer),1,f);
      return 0;
  } else {
     return 1;
  }
}
// fonction permettant d'allouer un nouveau bloc (comme l'allocation se fait d'une maniére automatique,son role se restreint à rendre le numero du bloc alloué)
int Alloc_Bloc(FILE *f){
    int numero_dernier_Bloc = entete(f, 1) + 1;
    aff_entete(f, 1, numero_dernier_Bloc);
    return numero_dernier_Bloc;
}

// pour l'index --------------------------------------------------------------------------------------------------------------------------
int LireDirI(FILE *f,int i,BlocIndex* buf){
   if (f!=NULL){
      fseek(f,sizeof(entet)+(i-1)*sizeof(BlocIndex),SEEK_SET);
      if(fread(buf,sizeof(BlocIndex),1,f));
      return 0;
   } else {
     return 1;
   }
}

// pour l'index --------------------------------------------------------------------------------------------------------------------------
int EcrireDirI(FILE *f,int i, BlocIndex *buf){
   if (f!=NULL){
       fseek(f,sizeof(entet)+(i-1)*sizeof(BlocIndex),SEEK_SET);
       fwrite(buf,sizeof(BlocIndex),1,f);
       return 0;
   } else {
      return 1;
   }
}

// modules complémentaires pour la création  du fichier T/OF :--------------------------------------------------------------------------------
//**************procedure qui initialize l'entete du fichier**************
void init_entete(FILE *f){
   entet ent;
   if (f!= NULL){
     ent.nbr_blocs=0;
     ent.libre=1;
     fseek(f,0,SEEK_SET);
     fwrite(&ent,sizeof(ent),1,f);
   }else{
      printf("erreur\n\n");
   }
}



