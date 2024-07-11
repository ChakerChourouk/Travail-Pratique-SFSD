#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ANP.h"
#include <string.h>
#include <stdbool.h>
#include "conio2.h"

/*void recherche_sequentielle(FILE* F ,char nomf[30], bool* trouv, int* i, int* j, int matric){
  *trouv = false;
   buffer *buf;// check it
  *j = 0;// le j commence de 0
  *i = 1;
  ouvrir(F, nomf,"rb+");// mode A
   while (*i <= entete(F,1) && !(*trouv)){
        LireDir(F,*i,buf);
        *j = 0;
        for (*j ; *j < buf->nb ; (*j)++) {
            if (buf->tab[*j].Matricule == matric) {
                *trouv = true;
                break;
            }
        }
        (*i)++;
    }

    if (!(*trouv)) {
        *i = entete(F , 1);
        *j = buf->nb;
    } else {
        (*i)--;
    }
    fermer(F);
}
*/

// recherche :-------------------------------------------------------------------------------------------------------------------------------
char recherche_militaire (int matric, FILE* F ,Index *ind){
    int nombreLireDir = 0 ;
    int nombreEcrireDir = 0;
    bool x;
    int pos;
    recherche_dicho_Index( ind, ind->nbi,matric,  &x, &pos);
    if(x){
        textcolor(YELLOW);
        printf("\n              le militaire existe dans le fichier PERSONNEL-ANP_DZ.dat\n\n");
    }else{
        textcolor(RED);
        printf("\n              ! le militaire n'existe pas dans le fichier PERSONNEL-ANP_DZ.dat !\n\n");
    }
    textcolor(WHITE);
    printf("\n\n                >> le cout de la recherceh d'un militaire par son matricule est :%d lectures et %d ecritures. \n\n",nombreLireDir,nombreEcrireDir);
    return x;
}

// procedure de chargement initial et la création de l'index se fait simultanément :------------------------------------------------------------------
void chargement_initial(Index *ind,Indexs *inds,Indexs1 *ind1,Indexs2 *ind2,Indexs3* ind3){
remplir_s(inds);
remplir_s1(ind1);
remplir_s2(ind2);
remplir_s3(ind3);
int nombreEcrireDir = 0;
FILE *f;
tbloc buf;  // buffer dans l mc
bool trouve=false;   // variable booléenne
caseIndex valeur;
int nbi=0;    // nombre effectif d'enregistrement dans l'index
enreg e;
int n=0,i,j,l,k=0;
printf("\n\n                >> veuillez saisir le nombre total d'enregistrement dans le fichier :");
scanf(" %d",&n);
i=1;j=0;l=0;
ouvrir(&f,"PERSONNEL-ANP_DZ.dat","wb"); // ouverture du fichier en mode nouveau 'N'
if(f!=NULL){
init_entete(f);   // initialization de l'entete;
srand(time(NULL));
while(k < n){
e=Personnel();  // generation d'un enregistrement aléatoire
// construction du triplet à partir de l'enregistrement generé

valeur.Matricule=e.Matricule;
valeur.nbloc=i;                     // valeur est la structure qui va ètre insérée dans l'index
valeur.dep=j;
if(valeur.dep==1024){
valeur.dep=0;
}
recherche_dicho_Index(ind,ind->nbi,valeur.Matricule,&trouve,&l);
if (!trouve) {
if (j<=1023) // le bloc n'est pas encore rempli
{
 buf.tab[j]=e;
 j++;
}else{
buf.nb=1024;      // nombre d'enregistrements présents dans un bloc
EcrireDir(f,i,&buf); // ecriture d'un bloc
nombreEcrireDir++;
buf.tab[0]=e;
j=1;
i++;
}
insertion_Index(ind,ind->nbi,l,valeur);       //mise a jour de l'index
insertion_Indexs1(ind1,ind1->ns1,e.RegionMilitaire,e.Matricule);
int temp=2023- atoi(e.DateNaissance.annee);
insertion_Indexs2(ind2,ind2->ns2,temp,e.Matricule);
insertion_Indexs(inds,inds->ns,e.ForceArmee,e.Matricule);
insertion_Indexs3(ind3,e.Grade,e.Matricule);
ind->nbi++;
k++;
}
}

// traitement du dernier bloc
buf.nb=j    ; //seul le dernier bloc pouurait ne pas étre remplie à 100%
EcrireDir(f,i,&buf);
nombreEcrireDir++;

nbi++;
aff_entete(f,1,i);           // Sauvgarder le nombre de blocs présents dans le fichier ANP
aff_entete(f,2,j);           // sauvgarder la premiére position libre dans le dernier bloc
printf("\n\n");//pour l'affichage
printf("                 >> le cout du chargement initial est : %d ecritures \n\n",nombreEcrireDir);
fermer(f);
}
}


// procedure permettant d'inserer :---------------------------------------------------------------------------------------------
void insertion( FILE* F,Index *ind,char nomf[30], enreg enr){
  int nombreLireDir = 0 ;
  int nombreEcrireDir = 0;
  bool trouv ;
  int pos;
  buffer buf;
  caseIndex valeur;
  ouvrir(&F,"PERSONNEL-ANP_DZ.dat","rb+");// mode A
  if( F == NULL ){
    printf("erreur dans l'ouverture du fichier");

  }
  recherche_dicho_Index( ind, ind->nbi ,enr.Matricule, &trouv, &pos);
  if(trouv){
    fermer(F);
     return 1;// la donnee existe deja
  }

  int i = entete(F,1); // numero du dernier bloc
  int j = entete(F,2); // premiere position libre dans le dernier bloc
  LireDir(F, i, &buf);
  nombreLireDir++;

  if (buf.nb == 1024){  // le dernier bloc est plein bloc
    i++;// allocation d'un nouveau bloc
    buf.tab[0] = enr;
    buf.nb = 1;
    EcrireDir(F, i, &buf);
    nombreEcrireDir++;
    // mise à jour de l'index
    valeur.nbloc = entete(F,1);
    valeur.dep = 0;
    valeur.Matricule = enr.Matricule ;
    insertion_Index(ind , ind->nbi , pos , valeur);
    ind->nbi++;
  }
  else{ // le dernier bloc n'est pas rempli à 100%
    buf.nb++;
    buf.tab[j] = enr;
    EcrireDir(F, i, &buf);
    nombreEcrireDir++;
    // mise à jour de l'index
    valeur.nbloc = entete(F,1);
    valeur.dep = j;
    valeur.Matricule = enr.Matricule ;
    insertion_Index(ind , ind->nbi , pos , valeur);
    ind->nbi++;
  }

  aff_entete(F,1,i); // mise à jour de nombre de bloc en cas d'allocation d'un nouveau bloc
  aff_entete(F,2,(buf.nb)+1); //mettre a jour la premiere position libre(chek it )
  textcolor(WHITE);
  printf("\n\n         >> le cout d'insertion d'un enregistrement generee aleatoirement est :%d lectures et %d ecritures. \n\n",nombreLireDir,nombreEcrireDir);
  fermer(F);
  return 0; //insertion avec succes
}

// procedure permettant de supprimer :---------------------------------------------------------------------------------------------------
void suppression(FILE* F ,Index *ind,char nomf[30], int matric ){//la suppression est physique
  int nombreLireDir = 0 ;
  int nombreEcrireDir = 0;
  bool trouv ;
  int i,j,pos;
  int dernier_Matricule;
  enreg dernier_enr;
  Index *index;
  buffer buf;
  caseIndex valeur;
  ouvrir(&F, nomf,"rb+");// mode A
  if( F == NULL ){
    printf("erreur dans l'ouverture du fichier");
    return 1;
  }
  recherche_dicho_Index( ind, ind->nbi ,matric, &trouv, &pos);
  if(!trouv){
     textcolor(RED);
     printf("\n             ! cette matricule n'existe pas !  [veuillez ressayer]\n\n");
     textcolor(WHITE);
     printf("         >> le cout de la suppression d'un enregistrement est :%d lectures et %d ecritures \n\n",nombreLireDir,nombreEcrireDir);
    return 2;// la matricule n'exite pas dans le fichier
  }

  valeur = ind->tab[pos]; // l'enregistrement trouvé est mis dans valeur
  i = valeur.nbloc; // bloc ou il se trouve
  j = valeur.dep;  // dep  dans le bloc

  if(i == entete(F,1)){ //cas ou l'enregistrement se trouve au dernier bloc
     LireDir(F, i, &buf);
     nombreLireDir++;
     buf.tab[j] = buf.tab[buf.nb - 1]; //on va ecraser l'enregistrement qu'on veut supprimer dans le dernier bloc par le dernier enregistrement du dernier bloc ( j commence de 0 au lieu de 1 donc buf.nb-1)
     dernier_Matricule = buf.tab[buf.nb - 1].Matricule;// on sauvegarde le dernier matricule car on aura besoin de le supprimer dans la table d'index
     buf.nb--;  // suppression du dernier enregistrement
     if(buf.nb == 0){//si aprés la suppression le bloc devient vide
        aff_entete(F, 1, entete(F,1) - 1); // modification d'indice du dernier bloc dans l'entete
     }
     else{
        EcrireDir(F, entete(F,1), &buf);   // ecriture du dernier bloc
        nombreEcrireDir++;
        aff_entete(F,entete(F,2),j-1);    // mise à jour de la premiére position libre dans le dernier bloc
     }

  }
  else{//cas ou l'enregistrement ne se trouve pas au dernier bloc
     LireDir(F, entete(F,1), &buf);//lecture de dernier bloc
     nombreLireDir++;
     dernier_enr = buf.tab[buf.nb - 1];//sauvgarde du dernier enreg
     dernier_Matricule = buf.tab[buf.nb - 1].Matricule;// on sauvegarde le dernier matricule du dernier enreg car on aura besoin de le supprimer dans la table d'index
     buf.nb--;// suppression du dernier enreg du dernier bloc
     if(buf.nb == 0){//si aprés la suppression le bloc devient vide
        int temp=entete(F,1) - 1;
       aff_entete(F,1,temp); // le nombre de bloc diminue de 1 bloc
       printf("%d",entete(F,1));

     }
     else{
        EcrireDir(F, entete(F,1), &buf);
        nombreEcrireDir++;
        aff_entete(F,entete(F,2),j-1);    // mise à jour de la premiére position libre dans le dernier bloc
     }

     LireDir(F, i, &buf); //on lit le bloc nemuro (i) ou se trouve l'enreg qu'on veut supprimer a supprime
     nombreLireDir++;
     buf.tab[j] = dernier_enr; //ecraser l'enregistrement a supprimer par le dernier enregistrement du dernier bloc
     EcrireDir(F,i,&buf);
     nombreEcrireDir++;
  }
  //changement sur la table d'index:
  //1-suppression dans la table d'index
   suppression_Index(ind ,ind->nbi, pos);
  //2- modification des coordonnees du dernier enregistrement dans la table d'index
   recherche_dicho_Index( ind, ind->nbi ,dernier_Matricule, &trouv, &pos);
   if(trouv){
      ind->tab[pos].Matricule = dernier_Matricule;
      ind->tab[pos].nbloc = i;
      ind->tab[pos].dep = j;
      ind->nbi--;
   }
   fermer(F);
   textcolor(WHITE);
   printf("\n\n         >> le cout de la suppression d'un enregistrement est :%d lectures et %d ecritures. \n\n",nombreLireDir,nombreEcrireDir);
   printf("\n\n         >> suppression d'un enregistrement faite avec succes ");
}
