#include "ANP.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "conio2.h"


// tableau des forces armées :-------------------------------------------------------------------------------------------------------------
char Tab_Force_Arme[8][45]={"ArmeeDeTerre","ArmeeDeAir","MarineNationale","DefenseAerienneDuTerritoire","GendarmerieNationale","GardeRepublicaine",
"DepartementDuRenseignementEtDeLaSecurite","SanteMilitaire"}; //Ensemble des forces armées possibles

char grad[17][19]={"GeneralCorpsArmee","General-Major","General","Colonel","Lieutenant-colonel" ,"Commandant","Capitaine","Lieutenant",
"Sous-lieutenant","Aspirant","Adjudant-chef","Adjudant","Sergent-chef","Sergent","Caporal-chef","Caporal","Djoundi"}; //Ensemble des grades possibles

//-----------------------------------------------------------------------------------------------------------------------------------------
maillonp* Allouer(int n) {

    maillonp* p = (maillonp*)malloc(n * sizeof(maillonp));

    // verification
    if (p == NULL) {
        fprintf(stderr, "Erreur\n");
        exit(EXIT_FAILURE);
    }
}
int valeur( maillonp *p){
return p->mat;
}
maillonp * suivant(maillonp *p){
return p->suiv;
}
void aff_val(maillonp *p,int mat){
p->mat = mat;
}
void aff_adr(maillonp *p,maillonp *q){
p->suiv=q;
}


// pour la liste issue de l'acces multicritere -------------------------------------------------------------------------------------------------
maillon* Allouer2(int n) {

    maillon* p = (maillon*)malloc(n * sizeof(maillon));

    // verification
    if (p == NULL) {
        fprintf(stderr, "Erreur\n");
        exit(EXIT_FAILURE);
    }
}


// generalisation de la recherche dichotomique ---------------------------------------------------------------------------------------------------

// modification des parametres pour l'indexs1
void recherche_dicho_Indexs1(const Indexs1 * ind,int taille,int valeur,  bool *trouv, int * k){
  // Initialisation des indices de la rechercheint
 int i;

  int bInf = 0, bSupp = taille - 1;
  *trouv = false ;
  // Recherche dichotomique
  while ((bInf <= bSupp) && (!(*trouv))){
    (i) = (bInf + bSupp) / 2;
    if (ind->tab[i].region == valeur){
          *trouv = true;
    }
    else{
        if(valeur < ind->tab[i].region){
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


// modification des parametres pour l'indexs2
void recherche_dicho_Indexs2( const Indexs2 *ind,int taille,int valeur,  bool *trouv, int * k){
  // Initialisation des indices de la rechercheint
 int i;

  int bInf = 0, bSupp = taille - 1;
  *trouv = false ;
  // Recherche dichotomique
  while ((bInf <= bSupp) && (!(*trouv))){
    (i) = (bInf + bSupp) / 2;
    if (ind->tab[i].age == valeur){
          *trouv = true;
    }
    else{
        if(valeur < ind->tab[i].age){
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


// insertion dans la tete de liste (utilisé durant la création de l'indexs1 et indexs2 ):-------------------------------------------------------
maillonp *ins_tete(maillonp * tete,int mat) // sert à inserer un nouveau maillon dans la liste et retourne la nouvelle téte
{
maillonp *p;
p=Allouer(1);
aff_val(p,mat);
aff_adr(p,tete);
tete=p;
return tete;
}

// comme indexs1 et indexs2 comporte peut de cases on va les remplir d'avance pour eviter les decalages durant la création:----------------------
void remplir_s1(Indexs1 *ind){
int k;
for(k=0;k<6;k++){
ind->tab[k].region=k+2;
ind->tab[k].tetep=NULL;
}
ind->ns1=6;
}
void remplir_s2(Indexs2 *ind){
int k;
for(k=0;k<62;k++){
ind->tab[k].age=k+18;
ind->tab[k].tetep=NULL;
}
ind->ns2=63;
}

// generalisation de l'insertion et de la suppression dans un index :-------------------------------------------------------------------------
void insertion_Indexs1( Indexs1 *ind , int  taille, char region[15],int mat){
    char str[2];
    str[0]=region[0];
    str[1] = '\0';
 int k = atoi(str);
 ind->tab[k-1].region=k; // par mesure de sécurité on écrase et on réercris la région
ind->tab[k-1].tetep=ins_tete(ind->tab[k-1].tetep,mat);
   }

void insertion_Indexs2( Indexs2 *ind , int  taille ,int k,int mat){

 ind->tab[k-18].age=k; // par mesure de sécurité on écrase et on réercris la région
 ind->tab[k-18].tetep=ins_tete(ind->tab[k-18].tetep,mat);
   }

// recherche de tous les enregistrements d'une region donnée dont l'age est compris entre A1 et A2
// insertion ordonnée dans une llc :---------------------------------------------------------------------------------------------------------
maillon *ins_ord(maillon * tete,couple cp){
maillon *p;
maillon *q=NULL;  // ptrs vers maillon
p=tete;
bool stop = false;
while((!stop)&&(p!=NULL))
{
if(cp.nbloc <= p->cp.nbloc ){
stop= true;
}else{
q=p;
p=p->suiv;
}
}
p=Allouer2(1);
p->cp.nbloc=cp.nbloc;
p->cp.dep=cp.dep;
if(q!=NULL){
p->suiv=q->suiv;
q->suiv=p;
}else{
p->suiv=tete;
tete=p;
}
return tete;
}

//2 eme question---------------------------------------------------------------------------------------------------------------
maillon *recherche_sec(int region,int A1, int A2,Index *ind,Indexs1 * ind1,Indexs2 * ind2 ){
int i1,i2,k,i;
maillon *tete=NULL;
couple cp;
maillonp *p1;
maillonp *p2;
bool trouve1=false,trouve2=false,trouve=false;
recherche_dicho_Indexs1(ind1,ind1->ns1,region,&trouve1,&i1); //recherche dicho dans indexs1
recherche_dicho_Indexs2(ind2,ind2->ns2,A1,&trouve2,&i2); //recherche dicho dans indexs1
if (trouve1 && trouve2)
{
 p1=ind1->tab[i1].tetep;
 while(p1!=NULL){
  for(int k =A1;k<=A2;k++){
    p2= ind2->tab[k-18].tetep;
 while ((p2!=NULL)&&(!trouve)) {
    if(p2->mat == p1->mat){
    trouve = true;
    } else{
    p2=suivant(p2);
    }
 }
 if (trouve){

 recherche_dicho_Index(ind,ind->nbi,p2->mat,&trouve,&i);
cp.nbloc=ind->tab[i].nbloc;
cp.dep=ind->tab[i].dep;
tete= ins_ord(tete,cp);
 }
 trouve=false;
  }
  p1=suivant(p1);
  }

 }
 return tete;
}


// pour la 1ere question
// sert à remplir l'index secondaire contenant les forces d'armee :--------------------------------------------------------------------------
void remplir_s(Indexs *ind){
for (int i=0;i<8;i++)
{
strcpy(ind->tab[i].force,Tab_Force_Arme[i]);
ind->tab[i].tetep=NULL;  // pas de réfernce au debut
}
ind->ns=8;
}
void recherche_indexs(Indexs *ind,char force[40],int *k){
int i=0;
while(strcmp(ind->tab[i].force,force)!=0 && i<8){
i++;
}
*k=i;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void insertion_Indexs( Indexs *ind , int  taille ,char force[45],int mat){
int k;
recherche_indexs(ind,force,&k);
ind->tab[k].tetep=ins_tete(ind->tab[k].tetep,mat);
   }


// suppression de tous les enregistrements relatives à une force donnée :--------------------------------------------------------------------
void supression_Force(Index *ind,Indexs *inds,int k){

// execution
FILE *f;
bool trouve=false;
int i=0;
int j=1;
maillonp *tete=inds->tab[k-1].tetep;

if(tete == NULL){
  textcolor(RED);
  printf("\n\n      ! aucun enregistrement correspondant a la force armee choisie ! \n");
}

while(tete!=NULL ){
recherche_dicho_Index(ind,ind->nbi,tete->mat,&trouve,&i);
textcolor(YELLOW);
printf("\n\n        > suppression de l'enregistrement nemuro %d en cours.......\n",j);
suppression(f,ind,"PERSONNEL-ANP_DZ.dat",tete->mat);
tete=tete->suiv;
j++;
}
textcolor(YELLOW);
printf("\n\n\n       >> le traitement fait avec succes \n");
}

//module d'affichage pour la 2 eme question :-----------------------------------------------------------------------------------------------
void afficherListe(maillon * tete) {

    int i , j;
    int cpt=1;
    if (tete == NULL){
        printf("\n\n ! pas d'enregistrement a afficher !\n\n");
    }
    // Parcours de la liste jusqu'à la fin
    while (tete != NULL) {
        printf("\n\n >> l'enregistrement nemuro : %d \n\n",cpt);
        i = tete->cp.nbloc;
        printf("\t > le nemuro du bloc -> %d \n", i);
        j = tete->cp.dep;
        printf("\t > la position de l'enregistrement dans le bloc -> %d \n\n", j);


        // Déplacement vers le prochain nœud
        tete = tete->suiv;
        cpt++;
    }

}



// 3eme question:--------------------------------------------------------------------------------------------------------------------------
// construction de l'indexs3
// initialisation de l'indexs3
void remplir_s3(Indexs3 *ind3){
strcpy(ind3->tab[0].cat,"Officiers-generaux");
strcpy(ind3->tab[1].cat,"Officiers-superieurs");
strcpy(ind3->tab[2].cat,"Officiers");
strcpy(ind3->tab[3].cat,"Sous-officiers");
strcpy(ind3->tab[4].cat,"Hommes de troupes");
for(int k=0;k<5;k++){
ind3->tab[k].tetep =NULL;
}
ind3->ns3 =5;
}
// insertion dans l'index s3
void insertion_Indexs3(Indexs3 *ind3,char grade[30],int mat){
if(strcmp(grade,grad[0]) == 0 || strcmp(grade,grad[1]) == 0 || strcmp(grade,grad[2])== 0){ // cat des généraux
 ind3->tab[0].tetep = ins_tete(ind3->tab[0].tetep,mat);
}
if(strcmp(grade,grad[3]) == 0 || strcmp(grade,grad[4]) == 0 || strcmp(grade,grad[5])== 0){ // cat des généraux
 ind3->tab[1].tetep = ins_tete(ind3->tab[1].tetep,mat);
}
if(strcmp(grade,grad[6]) == 0 || strcmp(grade,grad[7]) == 0 || strcmp(grade,grad[8])== 0){ // cat des généraux
 ind3->tab[2].tetep = ins_tete(ind3->tab[2].tetep,mat);
}
if(strcmp(grade,grad[9]) == 0 || strcmp(grade,grad[10]) == 0 || strcmp(grade,grad[11])== 0 || strcmp(grade,grad[12])== 0 || strcmp(grade,grad[13])== 0){ // cat des généraux
 ind3->tab[3].tetep = ins_tete(ind3->tab[3].tetep,mat);
}
if(strcmp(grade,grad[14]) == 0 || strcmp(grade,grad[15]) == 0 || strcmp(grade,grad[16])== 0){ // cat des généraux
 ind3->tab[4].tetep = ins_tete(ind3->tab[4].tetep,mat);
}


}


//module d'affichage pour la 3eme question :
void afficherListeGrade( maillonp* tete, FILE* F ,Index *ind) {
    int p ;
    int i , j,d ,c;
    int cpt=1;
    if (tete == NULL){
        printf("\n\n ! pas d'enregistrement a afficher !\n\n");
    }
    // Parcours de la liste jusqu'à la fin
    while (tete != NULL) {
        printf("\n\n >> l'enregistrement nemuro : %d \n\n",cpt);
        i = tete->mat;
        printf("\t > le matricule de cet enregistrement -> %d \n", i);

        // Déplacement vers le prochain nœud
        tete = tete->suiv;
        cpt++;
    }

}
// fragmentation

int pos_dans_tab(char mot[30]) {
    char Tableau[6][16]={"1RM_Blida","2RM_Oran","3RM_Bechar","4RM_Ouargla","5RM_Constantine","6RM_Tamanrasset"};
    for (int i = 1; i < 7; i++) {
        if (strcmp(mot, Tableau[i-1]) == 0) {
            return i; // Mot trouve, retourne l'indice de la case
        }
    }

    return -1; // Mot non trouve, retourne -1
}



void fragmenter( char nomf[30]){


   int j = 0, j1 = 0, j2 = 0, j3 = 0, j4 = 0, j5 = 0, j6 = 0;// decalaration des compteurs
   int n_region;
   // on utilise 7 buffer pour la fragmentation
   buffer * buf;
   buffer *buf1, *buf2, *buf3, *buf4, *buf5, *buf6; // on declare six pointeurs (buf1 � buf6) de type buffer qu'on utilsera pour l'allocation dynamique
   buf = malloc(sizeof(buffer));
   buf1 = malloc(sizeof(buffer)); // on alloue dynamiquement de la memoire pour buf1 en utilisant "malloc"
   buf2 = malloc(sizeof(buffer)); // on alloue dynamiquement de la memoire pour buf2 en utilisant "malloc"
   buf3 = malloc(sizeof(buffer)); // on alloue dynamiquement de la memoire pour buf3 en utilisant "malloc"
   buf4 = malloc(sizeof(buffer)); // on alloue dynamiquement de la memoire pour buf4 en utilisant "malloc"
   buf5 = malloc(sizeof(buffer)); // on alloue dynamiquement de la memoire pour buf5 en utilisant "malloc"
   buf6 = malloc(sizeof(buffer)); // on alloue dynamiquement de la memoire pour buf6 en utilisant "malloc"

   FILE *F,*F1, *F2, *F3, *F4, *F5, *F6; //decalaration des fichiers utilis�s pour la fragmentation


   ouvrir(&F, nomf, "rb"); //ouverture en mode A
   ouvrir(&F1, "F1.bin", "wb+"); //ouverture en mode N
   ouvrir(&F2, "F2.bin", "wb+"); // ouverture en mode N
   ouvrir(&F3, "F3.bin", "wb+"); // ouverture en mode N
   ouvrir(&F4, "F4.bin", "wb+"); // ouverture en mode N
   ouvrir(&F5, "F5.bin", "wb+"); // ouverture en mode N
   ouvrir(&F6, "F6.bin", "wb+"); // ouverture en mode N


   int i=1;

           init_entete(F1);
int           temp =entete(F1,1);
           init_entete(F2);
           init_entete(F3);
           init_entete(F4);
           init_entete(F5);
           init_entete(F6);
            int  i1,i2,i3,i4,i5,i6=0;

   if (F == NULL){
        printf("Erreur dans l'ouverture du fichier");
        return;
   }
   else{
       //printf("%d  \n",entete(F, 1));
       while(i <= entete(F, 1)){ // check it i commence de 0 /1 (< ou <=)


          LireDir(F, i , buf);// tant qu'on est pas arriv�es a la fin du fichier F on lit le bloc i dans buf
          temp = buf->nb;
          j = 0;// premiere position dans le bloc i

          while(j < buf->nb){ //tant qu'on est pas arriv� a la fin du bloc i

             n_region=pos_dans_tab(buf->tab[j].RegionMilitaire);
             switch(n_region) // on cherche la pos de "buf.tab[j].RegionMilitaire" dans tableau , pos est entre 1 et 6
             {
             // Cas ou la region militaire est 1
             case 1:
                 if ((j1 < 1024) ){ // check the number

                        //printf("%s \n",buf->tab[j].RegionMilitaire);
                        buf1->tab[j1] = buf->tab[j];
                        //printf("%s \n\n",buf1->tab[j1].RegionMilitaire);
                        j1++;

                 }
                 else{

                        buf1->nb = 1024;
                        EcrireDir(F1, entete(F1,1)+1, buf1);
                         aff_entete(F1,1, entete(F1,1)+1);
                          temp= entete(F1,1);
                        i1++;//Alloc_Bloc(F1)
                        buf1->tab[0] = buf->tab[j];
                        j1 = 1;
                 }
                 break;

             // Cas ou la region militaire est 2
             case 2:
                 if (j2 < 1024){

                        //printf("%s \n",buf->tab[j].RegionMilitaire);
                        buf2->tab[j2] = buf->tab[j];
                        //printf("%s \n\n",buf2->tab[j2].RegionMilitaire);
                        j2++;

                 }
                 else{

                        buf2->nb = 1024;
                     EcrireDir(F2, entete(F2,1)+1, buf2);
                         aff_entete(F2,1, entete(F2,1)+1);
                          temp= entete(F2,1);
                        i2++;//Alloc_Bloc(F2)
                        buf2->tab[0] = buf->tab[j];
                        j2 = 1;
                 }
                 break;

             // Cas ou la region militaire est 3
             case 3:
                 if (j3 < 1024){ // check the number

                        //printf("%s \n",buf->tab[j].RegionMilitaire);
                        buf3->tab[j3] = buf->tab[j];
                        //printf("%s \n\n",buf3->tab[j3].RegionMilitaire);
                        j3++;

                 }
                 else{

                        buf3->nb = 1024;
                          EcrireDir(F3, entete(F3,1)+1, buf3);
                         aff_entete(F3,1, entete(F3,1)+1);
                        temp= entete(F3,1);
                        i3++;//Alloc_Bloc(F3)
                        buf3->tab[0] = buf->tab[j];
                        j3 = 1;
                 }
                 break;

             // Cas ou la region militaire est 4
             case 4:
                 if (j4 < 1024){ // check the number

                        //printf("%s \n",buf->tab[j].RegionMilitaire);
                        buf4->tab[j4] = buf->tab[j];
                        //printf("%s \n\n",buf4->tab[j4].RegionMilitaire);
                        j4++;

                 }
                 else{

                        buf4->nb = 1024;
                         EcrireDir(F4, entete(F4,1)+1, buf4);
                         aff_entete(F4, 1,entete(F4,1)+1);
                          temp= entete(F4,1);
                        i4++;//Alloc_Bloc(F4)
                        buf4->tab[0] = buf->tab[j];
                        j4 = 1;
                 }
                 break;

             // Cas ou la region militaire est 5
             case 5:
                 if (j5 < 1024){

                        //printf("%s \n",buf->tab[j].RegionMilitaire);
                        buf5->tab[j5] = buf->tab[j];
                        //printf("%s \n\n",buf5->tab[j5].RegionMilitaire);
                        j5++;

                 }
                 else{

                        buf5->nb = 1024;
                          EcrireDir(F5, entete(F5,1)+1, buf5);
                          int s=entete(F5,1);
                         aff_entete(F5,1, entete(F5,1)+1);
                          temp= entete(F5,1);
                        i5++;//Alloc_Bloc(F5)
                        buf5->tab[0] = buf->tab[j];
                        j5 = 1;
                 }
                 break;

             // Cas ou la region militaire est 6
             case 6:
                 if (j6 < 1024){

                        //printf("%s \n",buf->tab[j].RegionMilitaire);
                        buf6->tab[j6] = buf->tab[j];
                        //printf("%s \n\n\n",buf6->tab[j6].RegionMilitaire);
                        j6++;
                 }
                 else{
                        buf6->nb = 1024;
                         EcrireDir(F6, entete(F6,1)+1, buf6);
                         aff_entete(F6,1, entete(F6,1)+1);
                         temp= entete(F6,1);
                        i6++;//Alloc_Bloc(F6)
                        buf6->tab[0] = buf->tab[j];
                        j6 = 1;
                 }
                 break;

             }

             j++;

          }
          i++;
       }

   }

   //ecriture du dernier buffer de F1
   buf1->nb = j1;//j1 commence de 0
 temp =entete(F1,1);
aff_entete(F1,1, entete(F1,1)+1);
temp =entete(F1,1);
   EcrireDir(F1, entete(F1,1), buf1);

   //ecriture du dernier buffer de F2
   buf2->nb = j2;
    temp =entete(F2,1);
    aff_entete(F2,1, entete(F2,1)+1);
   EcrireDir(F2, entete(F2,1), buf2);
   //ecriture du dernier buffer de F3S   buf3->nb = j3;
   aff_entete(F3,1, entete(F3,1)+1);
   EcrireDir(F3,entete(F3,1), buf3);
   //ecriture du dernier buffer de F4
   buf4->nb = j4;
   aff_entete(F4,1, entete(F4,1)+1);
   EcrireDir(F4, entete(F4,1), buf4);
   //ecriture du dernier buffer de F5
   buf5->nb = j5;
   temp =entete(F5,1);
   aff_entete(F5,1, entete(F5,1)+1);
   EcrireDir(F5, entete(F5,1), buf5);
   //ecriture du dernier buffer de F6
   buf6->nb = j6;
aff_entete(F6,1, entete(F6,1)+1);

   EcrireDir(F6,entete(F6,1), buf6);


   //fermeture des 7 fichiers
   fermer(F);
   fermer(F1);
   fermer(F2);
   fermer(F3);
   fermer(F4);
   fermer(F5);
   fermer(F6);

   //liberation de la memoire allou�e dynamiquement pour les 6 buffers
   free(buf1);
   free(buf2);
   free(buf3);
   free(buf4);
   free(buf5);
   free(buf6);

   //system("cls");
}

