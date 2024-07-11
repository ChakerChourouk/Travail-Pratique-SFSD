#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ANP.h"
#include <string.h>

//=========================================================================================================================================
// declaration des tableaux de données :
//=========================================================================================================================================
char Tab_Force_Armee[8][45]={"ArmeeDeTerre","ArmeeDeAir","MarineNationale","DefenseAerienneDuTerritoire","GendarmerieNationale","GardeRepublicaine",
"DepartementDuRenseignementEtDeLaSecurite","SanteMilitaire"}; //Ensemble des forces armées possibles

// tableau des wilayas de naissance :------------------------------------------------------------------------------------------------------
char Tab_Wilaya_Naissance[58][20]={"Adrar","Chlef","Laghouat","Oum_El_Bouaghi","Batna","Bejaia","Biskra","Bechar","Blida","Bouira","Tamanrasset",
"Tebessa","Tlemcen","Tiaret","Tizi_Ouzou","Alger","Djelfa","Jijel","Setif","Saida","Skikda","Sidi_Bel_Abbes","Annaba","Guelma",
"Constantine","Medea","Mostaganem","Msila","Mascara","Ouargla","Oran","El_Bayadh","Illizi","Bordj_Bou_Arreridj","Boumerdes","El_Taref",
"Tindouf","Tissemsilt","El_Oued","Khenchela","Souk_Ahras","Tipaza","Mila","Ain_Defla","Naama","Ain_Temouchent","Ghardaia","Relizane",
"Timimoun","Bordj_Badji_Mokhtar","Ouled_Djellal","Beni_Abbes","In_Salah","In_Guezzam","Touggourt","Djanet","El_Megaier","El_Meniaa"};//Ensemble des wilayas possibles

// tableau des grades :--------------------------------------------------------------------------------------------------------------------
char Tab_Grade[17][19]={"GeneralCorpsArmee","General-Major","General","Colonel","Lieutenant-colonel" ,"Commandant","Capitaine","Lieutenant",
"Sous-lieutenant","Aspirant","Adjudant-chef","Adjudant","Sergent-chef","Sergent","Caporal-chef","Caporal","Djoundi"}; //Ensemble des grades possibles


// tableau des regions militaires :--------------------------------------------------------------------------------------------------------
char Tab_Region_militaire[6][16]={"1RM_Blida","2RM_Oran","3RM_Bechar","4RM_Ouargla","5RM_Constantine","6RM_Tamanrasset"}; //Ensemble des regions militaires possibles

// tableau des groupes sanguins
char Tab_Groupe_Sanguin[8][5] = {"O+", "A+", "B+", "O-", "A-", "AB+", "B-", "AB-"};//Ensemble des groupes sanguins possibles


//=========================================================================================================================================
// modules pour la generation aleatoires des champs d'un enregistrements :
//=========================================================================================================================================

// - generation d'un matricule ( clé d'un enregistrement ) aleatoire :----------------------------------------------------------------------
int Matricule(){
   return (rand() % (889) + 111) * 1000 + (rand() % (889) + 111);//génère un nombre aléatoire entre 111 et 999 on le multiplie par 1000 et on lui ajoute un autre nombre aleatoire entre 111 et 999
}

// - generation d'un nom aleatoire :--------------------------------------------------------------------------------------------------------

char *Nom(){
    int longueur_Nom = rand() % (30 - 4 + 1) + 4; //on genere un nombre aleatoire "longueur_Nom" entre 4 et 30
    char *Nom = malloc((longueur_Nom +1)* sizeof(char));// allocation dynamique du tableau de caractères "Nom" qui va stocker le Nom
    char nombreAlea ; //variable qui va stocker le nombre aléatoire généré pour chaque caractère du Nom.
    if(Nom){
        for(int i = 0; i<longueur_Nom ; i++){
           nombreAlea = rand() % (26) + 1; //on génère un nombre aléatoire entre 1 et 26 , ce nombre représente la position d'une lettre de l'alphabet
           Nom[i] = nombreAlea + 64; //on transforme chaque caractere du nom en majescule( un nom est en majescule)
        }
        Nom[longueur_Nom] = '\0';//on ajoute le caractère nul à la fin de la chaîne pour la terminer correctement
    }
    return Nom; //on retourne le pointeur vers le tableau de caractères "Nom" qui représente le nom généré
}

// - generation d'un prenom aleatoire :-----------------------------------------------------------------------------------------------------

char *Prenom(){
   int longueur_Prenom = rand() % (30 - 4 + 1) + 4; //on genere un nombre aleatoire "longueur_Prenom" entre 4 et 30
   char *Prenom = malloc((longueur_Prenom +1)* sizeof(char));// allocation dynamique du tableau de caractères "Prenom" qui va stocker le Prenom
   char nombreAlea ; //variable qui va stocker le nombre aléatoire généré pour chaque caractère du Prenom.
   if(Prenom){
        Prenom[0] = rand() % (26) + 65;// on met la premiere lettre du prenom a majescule
        for(int i = 1; i<longueur_Prenom ; i++){
           nombreAlea = rand() % (26) + 1; //on génère un nombre aléatoire entre 1 et 26 , ce nombre représente la position d'une lettre de l'alphabet
           Prenom[i] = nombreAlea + 96; // on met le reste des lettre a minuscule
        }
        Prenom[longueur_Prenom] = '\0';//on ajoute le caractère nul à la fin de la chaîne pour la terminer correctement
    }
    return Prenom; //on retourne le pointeur vers le tableau de caractères "Prenom" qui représente le Prenom généré
}

// - generation d'une date naissance aleatoire :----------------------------------------------------------------------------------------------

//********verification si l'année generée est bissextile********

char is_bissextile(short int annee){
   if ((annee % 4) == 0) //on vérifie si l'année est divisible par 4
    {
        if ((annee % 100) == 0) //on vérifie si l'année est divisible par 100
        {
            if ((annee % 400) == 0) //on vérifie si l'année est divisible par 400
            {
                return 1;//année bissextile(divisible par 4 et 100 et 400)
            }
            else
            {
                return 0;//année non bissextile( car n'est pas divisible par 400)
            }
        }
        else
        {
            return 1;//année bissextile(n'est pas divisible par 100,mais elle est divisible par 4)
        }
    }
    else
    {
        return 0;//année non bissextile (car n'est pas divisible par 4)
    };
}

//********genration d'une date de naissance aleatoire******


Date DateNaissance() {
    char maximum_jours[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    Date DateNaissance;
    short int Annee_min = 1942;
    short int Annee_max = 2005;
    char Jour_max;

    DateNaissance.annee[0] = '\0';

    //convertir l'anee
    sprintf(DateNaissance.annee, "%d", rand() % (Annee_max - Annee_min + 1) + Annee_min);

    // generation d'un mois aléatoires
    sprintf(DateNaissance.mois, "%d", rand() % 12 + 1);

    if (is_bissextile(atoi(DateNaissance.annee)) && (atoi(DateNaissance.mois) == 2)) {
        Jour_max = 29;
    } else {
        Jour_max = maximum_jours[atoi(DateNaissance.mois) - 1];
    }

    // Generation d'un jour
    sprintf(DateNaissance.jour, "%d", rand() % Jour_max + 1);

    return DateNaissance;
}

// - generation d'une wilaya de maniére aléatoire :---------------------------------------------------------------------------------------------

char * WilayaNaissance(){
    int n;
     n=(rand() % (58) );
    return  Tab_Wilaya_Naissance[n];


}

// - generation d'un groupe sanguin de maniére aléatoire :--------------------------------------------------------------------------------------

char * GroupeSanguin(){
    int n;
     n=(rand() % (8) );
     return Tab_Groupe_Sanguin[n];
}

// - generation d'un grade de maniére aléatoire :-----------------------------------------------------------------------------------------------

char * Grade(){
    int n;
     n= (rand() % (17));
      return Tab_Grade[n];
}

// - generation d'une Force Armée de maniére aléatoire :----------------------------------------------------------------------------------------

char * ForceArmee(){
    int n;
     n=(rand() % (8) );
     return Tab_Force_Armee[n];
}

// - generation d'une Region militaire de maniére aléatoire :------------------------------------------------------------------------------------

char * RegionMilitaire(){
    int n;

    n=(rand() % (6) );
    return Tab_Region_militaire[n];

}

// - generation d'un enregistrement aleatoire (Personnel) :--------------------------------------------------------------------------------------

enreg  Personnel(){

enreg e;
e.Matricule = Matricule();
strcpy(e.Nom,Nom());
strcpy(e.Prenom,Prenom());
strcpy(e.WilayaNaissance,WilayaNaissance());
strcpy(e.GroupeSanguin,GroupeSanguin());
e.DateNaissance=DateNaissance();
strcpy(e.Grade,Grade());
strcpy(e.RegionMilitaire,RegionMilitaire());
strcpy(e.ForceArmee,ForceArmee());
return e;
}


