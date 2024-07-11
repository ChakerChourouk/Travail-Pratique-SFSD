#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "conio2.h"
#include "ANP.h"
#include<string.h>


//===============================================================================================================================================
// modules pour l'index qui contient la clé (Matricule) et les coordonnées (n° de bloc et déplacement) de chaque nouvel enregistrement inséré :
//===============================================================================================================================================

// - recherche dichotomique dans la table d'index selon un matricule :---------------------------------------------------------------------------

void recherche_dicho_Index( const Index *ind,int taille,int valeur,  bool *trouv, int * k){
  // Initialisation des indices de la rechercheint
 int i;
  int bInf = 0, bSupp = taille - 1;
  *trouv = false ;
  // Recherche dichotomique
  while ((bInf <= bSupp) && (!(*trouv))){
    (i) = (bInf + bSupp) / 2;
    if (ind->tab[i].Matricule == valeur){
          *trouv = true;
    }
    else{
        if(valeur < ind->tab[i].Matricule){
             bSupp = i - 1;
        }
        else{
             bInf = i + 1;
        }
    }
  }
  if (!(*trouv)){
    i = bInf;// si on ne trouve pas la valeur recherchée on retourne la position ou elle devrait se trouver
  }
  *k=i;
}

// - insertion par decalage dans la table d'index ::-------------------------------------------------------------------------------------------

void insertion_Index( Index *ind , int  taille ,int k,caseIndex valeur ){


   int i=taille-1;
   // k est la postion ou doit se trouver le triplet
   while ( i>=k ){
      ind->tab[i+1].Matricule=ind->tab[i].Matricule;
      ind->tab[i+1].nbloc=ind->tab[i].nbloc;
      ind->tab[i+1].dep=ind->tab[i].dep;
      i--;
     }
     ind->tab[k].Matricule=valeur.Matricule;
      ind->tab[k].nbloc=valeur.nbloc;
      ind->tab[k].dep=valeur.dep;
       taille --;
   }

// 3.2- sauvegarde de l'index en memoire secondaire (MS) :---------------------------------------------------------------------------------------

// Vu la taille reduite de l'index ,il peur étre cotenu en MC, alors la sauvgarde ne sera que pour le garder en MS en cas de fermueture du programme                                                                                                                                                  ------//
void sauvgarde_index(Index *ind){
 int k=0,i=1,j=0;
 int nombreEcrireDir = 0;
 FILE *f;
 BlocIndex buf; // buffer
 ouvrir(&f,"MATRICULE_INDEX.idx","wb");
 if(f!=NULL){
    init_entete(f);
    for(k=0;k<ind->nbi;k++){
       if(j<=24999){ // on suppose que la taille d'un bloc du fichier index est de 25000 enregistrement d'index(triplet)
          buf.tab[j].Matricule=ind->tab[k].Matricule;
          buf.tab[j].nbloc=ind->tab[k].nbloc;
          buf.tab[j].dep=ind->tab[k].dep;
          j++;
       } else  {// j > 24900
            EcrireDirI(f,i,&buf);
          buf.tab[0].Matricule=ind->tab[k].Matricule;
          buf.tab[0].nbloc=ind->tab[k].nbloc;
          buf.tab[0].dep=ind->tab[k].dep;
          j=1;
          i++;
          nombreEcrireDir++;
       }
    // gestion du dernier bloc
    }
    buf.NB=j;
    EcrireDirI(f,i,&buf);
    nombreEcrireDir++;
    aff_entete(f,1,1);   // nombre de bloc dans le fichier index
    aff_entete(f,2,ind->nbi);  // sauvgarde de ind.nbi
    fermer(f);
 }
 printf("\n\n         >>   le cout du sauvegarde de l'index en memoire secondaire (MS) est :%d ecritures\n\n",nombreEcrireDir);
 printf("\n\n         >>   sauvegarde d'index fait avec succes ");
}

// 3.1- chargement du contenu du fichier index dans la mémoire centrale(MC) :---------------------------------------------------------------------

void Chargement_idex(Index *ind){
 int k=0,i=1,j=0;
 int nombreLireDir =0 ;
 FILE *f;
 int nb=0;
 ind->nbi = 0;
 BlocIndex buf;    // buffer
 ouvrir(&f,"MATRICULE_INDEX.idx","rb");   //ouvrir le fichier en mode lecture
 if(f!=NULL){
   nb=entete(f,2) ; // recupération du nombre total de triplet via l'index
   LireDirI(f,i,&buf);
   nombreLireDir++;
   for(k=0;k<buf.NB;k++){
     if(j<=24999){  // on suppose que la taille d'un bloc du fichier index est de 25000 enregistrement d'index(triplet)
         ind->tab[k].Matricule=buf.tab[j].Matricule;
         ind->tab[k].nbloc=buf.tab[j].nbloc;
         ind->tab[k].dep=buf.tab[j].dep;
         j++;
     }else{ //j > 24999
         i++;
         LireDirI(f,i,&buf);
         nombreLireDir++;
         ind->tab[0].Matricule=buf.tab[j].Matricule;
         ind->tab[0].nbloc=buf.tab[j].nbloc;
         ind->tab[0].dep=buf.tab[j].dep;
         j=1;
     }
     ind->nbi++;   // taille effective de l'index dans la MC
  }
  fermer(f);
 }
 printf("\n\n         >>   le cout du chargement du contenu du fichier index dans la memoire centrale(MC) est :%d lectures\n\n",nombreLireDir);
 printf("\n\n         >>   chargement d'index fait avec succes ");
}

// - supression par decalage d'une case dans la table d'index :--------------------------------------------------------------------------------

void suppression_Index(Index *ind, int taille, int pos){
     while (pos < taille - 1){
        ind->tab[pos]=ind->tab[pos+1];// on décale tous les éléments d'une position vers la gauche à partir de la position spécifiée pos
        pos++;
     }
}


// 3.7- Affichage ou consultation de tous militaires dont les matricules appartiennent à l’intervalle [M1, M2]:-----------------------------------

//********ALgorithme de tri**********
void tri (Index *ind){
    caseIndex temp ;
    for (int i = 0; i <  ind->nbi- 1; i++) {
        for (int j = 0; j < ind->nbi - i - 1; j++) {
            if (ind->tab[j].nbloc > ind->tab[j+1].nbloc ) {
                temp= ind->tab[j]; // permutation des elements
               ind->tab[j] = ind->tab[j+1];
                ind->tab[j+1]= temp;
            }
        }
    }
}

//***procedure renvoie un pointeur vers container contenant les enregistrements de matricule compris entre inf et sup*******
void Requete_intervalle(Index *ind,int inf,int sup,container *cont){
int nombreLireDir =0;
int nombreEcrireDir = 0;
FILE *f;
ouvrir(&f,"PERSONNEL-ANP_DZ.dat","rb");
buffer buf;
Index2 ind2; // tableau similaire à l'index mais dd taille réduite pour trier les enregistrements selon le numéro de bloc afin de ne pas lire un blocs plusieurs fois
ind2.nbi=0;
bool trouve=false;
int k;
if (f!=NULL){
 recherche_dicho_Index(ind,ind->nbi,inf,&trouve,&k);
 if (trouve){
int i=0;
 while (ind->tab[k].Matricule!=sup ){
ind2.tab[i]=ind->tab[k];
ind2.nbi++;
k++;
i++;
}
ind2.nbi++;
ind2.tab[i]=ind->tab[k]; // derniére case appartenant à l'intervalle
tri(&ind2);   // tri selon le numero du bloc pour éviter de lire le méme bloc plusieurs fois

// construction du tableau contenant les enregistrements en MC
int check=ind2.tab[0].nbloc; // on l'utilise pour garder le numéro du   bloc deja lu
LireDir(f,check,&buf);
nombreLireDir++;
int k=0; // utilisée pour construire le tableau en MC
for(i=0;i<ind2.nbi;i++){
if(ind2.tab[i].nbloc != check){
check=ind2.tab[i].nbloc ;
LireDir(f,check,&buf);            // lire un nouveau bloc
nombreLireDir++;
}
int j=ind2.tab[i].dep; //utilisée pour le deplacement
cont->tab[k]=buf.tab[j];
k++;
}
cont->nb=ind2.nbi;  // nombre d'enregistrements lus
 }
}

 printf( "\n\n                          >>  requete a intervalle faite avec succes  \n\n");
 printf("\n\n                           >> le cout de la requete a intervalle est :%d lectures \n\n\n\n",nombreLireDir);
 fermer(f);
}


// 3.6- Modification de la région militaire d’un enregistrement donné( d'un matricule donné ) :-------------------------------------------------
void modif(FILE *f,Index *ind,int matricule,char region[15]){
   ouvrir(&f,"PERSONNEL-ANP_DZ.dat","rb+");
   bool trouve=false;
   int k=0;
   int nombreLireDir =0;
   int nombreEcrireDir = 0;
   caseIndex valeur;// declaration
   buffer buf;
   if (f!=NULL){
     recherche_dicho_Index(ind,ind->nbi,matricule,&trouve,&k);// recherche par matricule dans le table d'index
     if(!trouve){
        textcolor(RED);
        printf("\n\t\t            ! cette matricule n'existe pas !\n\n");
        textcolor(YELLOW);
        printf("\n\t\t            >> aucune modification n'est faite \n\n");
     }
     if (trouve){
        valeur=ind->tab[k];
        LireDir(f,valeur.nbloc,&buf);// lecture du bloc
        nombreLireDir++;
        strcpy(buf.tab[valeur.dep].RegionMilitaire,region);// modification de la region
        EcrireDir(f,valeur.nbloc,&buf);// ecriture du bloc
        nombreEcrireDir++;
        printf( "\n\n                     Region modifiee avec succes  \n\n");
    }
    fermer(f);
   }
   textcolor(WHITE);
   printf("\n\n                           >> le cout de modification de la region militaire d'un enregistrement donne est :%d lectures et %d ecritures \n\n",nombreLireDir,nombreEcrireDir);
}


// remettre à zero toutes les cases index en vue d'un chargement initial imminent :-------------------------------------------------
void Raz_index(Index * ind){
ind ->nbi=0;
}
