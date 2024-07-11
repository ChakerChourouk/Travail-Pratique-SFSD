#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#ifndef CREATION_H_INCLUDED
#define CREATION_H_INCLUDED



// declaration de la structure d'une date

typedef struct Date {
    char jour[3];
    char mois[3];
    char annee[5];
} Date;

typedef struct enreg{
   int Matricule;
   char Nom[31]; // le nombre de caracteres max de Nom est 30 + 1 pour le caractere de fin de chaine '\0'
   char Prenom[31]; // le nombre de caracteres max de prenom est 30 + 1 pour le caractere de fin de chaine '\0'
   Date DateNaissance;
   char WilayaNaissance[19];// le nombre de caracteres max dans wilaya est 19 ("Bordj_Bou_Arreridj")
   char GroupeSanguin[6]; // AB+ au maximum + 1 por \0
   char Grade[25];// le nombre de caracteres max dans grade est 15 ("General de corps d'armée")
   char ForceArmee[41];// le nombre de caracteres max dans ForceArmee est 40 ("DepartementDuRenseignementEtDeLaSecurite")
   char RegionMilitaire[15];// le nombre de caracteres max dans RegionMilitaire est 15 ("5RM_Constantine")
}enreg;



// declarations de la table d'index :
// on opte pour l'approche du triplet
typedef struct caseIndex {
    int Matricule;
    int nbloc;
    int dep;
} caseIndex;

typedef struct  {
    caseIndex tab[100000]; // on considere que le nombre maximale des cases dans l'index est 2000000
    int nbi;
} Index;

typedef struct  {
    caseIndex tab[1024]; // utilisé pour trier les enregistrements selon le numero de bloc
    int nbi;
} Index2;
// on utilise un index à 1 seul niveau puisque sa taille est d'odre des MO alors sa totalité peut étre maintenu en MC sans probléme


// declaration de l'entete du fichier de sauvegarde de l'index (fIndex)
typedef struct fIndexEntete {
    int nbrBlocs;
} fIndexEntete;

typedef struct BolcfIndex {
    caseIndex tab[25000];//on considere que le nombre des enregs maximale par blocs dans le fichier de sauvgarde de l'index est 25000
    int NB;
} BlocIndex;


// Structure d'un bloc dans le fichier ANP
typedef struct {
enreg tab[1024];
int nb; // nombre d'enregistrements présents dans le bloc
} tbloc,buffer,container; // le buffer a la meme structure qu'un bloc du fichier

//container est une structure qui va contenir les enregistrements contenus dans l'intervalle  en MC pour pouvoir les afficher ou les consulter

// Structure de l'entète
typedef struct {
int nbr_blocs; // nombre de blocs presents dans le fichier
int libre; // position libre dans le dernier bloc
} entet ;


// maillon contenat une clé primaire
typedef struct maillonp {
int mat;
struct maillonp *suiv;
} maillonp;
// enregistrement de l'Indexs2
typedef struct {
int age;
 maillonp *tetep;
} Aenreg;
// index par region militaire
// enregistrement de l'Indexs1
typedef struct {
int region;  // numero de la region militaire
 maillonp *tetep;
} Renreg;
typedef struct{
Renreg tab[6];
int ns1;
} Indexs1;
// index pour l'age

typedef struct{
Aenreg tab[63];
int ns2;
} Indexs2;

typedef struct {
int nbloc;
int dep;
} couple;// un maillon de la liste construite suite à la requete multicritére
typedef struct maillon {
couple cp;
struct maillon *suiv;
} maillon;
// declarations pour la 1ere question optionnelle

typedef struct {
char force[45];
maillonp * tetep;
}Fenreg;

typedef struct {
Fenreg tab[8];
int ns;
}Indexs;
// index secondaire sur les catégories des forces de l'armée
typedef struct  {
char cat[30];
maillonp * tetep;
} Cenreg;

typedef struct {
Cenreg tab[5];
int ns3;
} Indexs3;


//Declaration des modules utilisé pour le chargement initiale : ==================================================

int matricule();
char *Nom();
char *Prenom();
char is_bissextile(short int annee);
Date DateNaissance();
char *WilayaNaissance();
char *ForceArmee();
char * Grade();
char * GroupeSanguin();
char * RegionMilitaire();
enreg Personnel();


// entete des modules de la machine abstraite : ============================================================


void ouvrir ( FILE **f,char nomf[30],char mode[3]);
void fermer (FILE *f);
int entete(FILE *f,int n);
void aff_entete(FILE *f,int n,int car);
int LireDir(FILE *f,int i,buffer * buf);
int LireDirI(FILE *f,int i,BlocIndex * buf);
int EcrireDir(FILE *f,int i, buffer *buf);
int EcrireDirI(FILE *f,int i, BlocIndex *buf);
void init_entete(FILE *f);


//Declaration des modules utilisés pour les index : ======================================================

void recherche_dicho_Index( const Index *ind,int taille,int valeur,  bool *trouv, int *k);
void insertion_Index( Index *ind , int  taille ,int k,caseIndex valeur );
void suppression_Index(Index *ind, int taille, int pos);
void sauvgarde_index(Index *ind);
void Chargement_idex(Index *ind);
void Raz_index(Index * ind);


// entete des modules tobarref : ==================================================

char recherche_militaire (int matric, FILE* F ,Index *ind);
void chargement_initial(Index *ind,Indexs *inds,Indexs1 *ind1,Indexs2 *ind2,Indexs3* ind3);
void insertion( FILE* F,Index *ind,char nomf[30], enreg enr);
void suppression(FILE* F ,Index *ind,char nomf[30], int matric );
void Requete_intervalle(Index *ind,int inf,int sup,container *cont);
void modif(FILE *f,Index *ind,int matricule,char region[15]);
void tri (Index *ind);


// modules optioennels : =======================================================

// machine abstraite sur les listes
maillonp* Allouer(int n);
int valeur( maillonp *p);
maillonp * suivant(maillonp *p);
void aff_val(maillonp *p,int mat);
// modules pour les indexes secondaires
void recherche_dicho_Indexs1(const Indexs1 * ind,int taille,int valeur,  bool *trouv, int * k);
void recherche_dicho_Indexs2(const Indexs2 * ind,int taille,int valeur,  bool *trouv, int * k);
maillonp *ins_tete(maillonp * tete,int mat);
void remplir_s1(Indexs1 *ind);
void remplir_s2(Indexs2 *ind);
void insertion_Indexs1( Indexs1 *ind , int  taille, char region[15],int mat);
void insertion_Indexs2( Indexs2 *ind , int  taille, int k,int mat);
void aff_adr(maillonp *p,maillonp *q);
maillon *recherche_sec(int region,int A1, int A2,Index *ind,Indexs1 * ind1,Indexs2 * ind2 );
void remplir_s(Indexs *ind);
void insertion_Indexs( Indexs *ind , int  taille ,char force[45],int mat);
void recherche_indexs(Indexs *ind,char force[40],int *k);
void supression_Force(Index *ind,Indexs *inds,int k);

// pour la 3eme question
void remplir_s3(Indexs3 *ind3);
void insertion_Indexs3(Indexs3 *ind3,char grade[30],int mat);
int pos_dans_tab(char mot[30]);
void fragmenter( char nomf[30]);



//Declaration des modules de l'interface : ========================================================================
int menu(int max, ...);
void home();
void accueil();
void fin();
void sortir();
void retour_acceuil();
void fichierExistant();
void soldier();
void retour();
void menuPrincipale();
void accueill();
void creationFichier();
void affichageIndex();
void affichInsertion();
void affichSuppression();
void affichModification();
void affichRequete();
void affichSauvegarde();
void affichChargement();
void scanf2(long long* choix);
void getNumber(char *num);
int getkey(void);
void affichage_enreg(enreg e);
void affichge_index(Index *ind);
void affichage_bloc(FILE *F,buffer *buf,int i);
bool matricule_valide (int matric);
bool matricule_existe (int matric, FILE* F ,Index *ind);
bool fichier_existe(FILE* F,char nomf[30]);

#endif // CREATION_H_INCLUDED
