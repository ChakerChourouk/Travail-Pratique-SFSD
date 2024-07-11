#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <windows.h>
#include"ANP.h"
#include "conio2.h"

int couleurPrincipale = 10;

int main(){

maillon *tete;
Indexs inds;
Indexs1 ind1;
Indexs2 ind2;
Indexs3 ind3;
maillon *m;
enreg enr ;
maillonp* listeMat;
int ageMin, ageMax;
int i=0;
buffer buf;
enreg e;
enreg e2;
FILE *f;
Index ind;
container cont;
int matricule;
char region[30];
 bool arret=false;

    int c,c1,x,y, c2 ,inf ,sup ,n;
    long long cle ;
    ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);//taille maximale du console
    home();
    int menu_creation,  menuChamp , menue1 , menu_supression ,menu_grade, menu_region;
debut:

    system("cls");
    accueil();
    textcolor(couleurPrincipale);
    printf("\n\n\n\tVeuillez saisir votre choix\n\n");
    textcolor(YELLOW);
    menu_creation = menu(4, "\t\t\t[1]- Exploitation d'un fichier existant.", " \t\t\t[2]- Creer un nouveau fichier.", "\t\t\t[3]- Modifier la couleur principale du programme.",
                         "\t\t\t[4]- Quitter.");
    clrscr();
    switch (menu_creation)
    {
    case 1:
         if(!fichier_existe(f,"PERSONNEL-ANP_DZ.dat")){
             textcolor(RED);
             printf("\n\n! le fichier PERSONNEL-ANP_DZ.dat n'existe pas [vous devez le creer] !\n\n");
             textcolor(WHITE);
             retour_acceuil();
             getch();
             goto debut;
          }else{
             fichierExistant();
             textcolor(couleurPrincipale);
             printf("\n\n         >> le fichier PERSONNEL-ANP_DZ.dat existe deja\n\n");
             textcolor(YELLOW);
             printf("\n\n         >> chargement de l'index en cours ............ \n\n");
             Chargement_idex(&ind);//l'utilsateur doit sauvegrder l'index avant la fermeture du programme sinon ce choix ne marchera pas
             textcolor(WHITE);
             retour();
             getch();
             goto menu_principale;
          }
        break;
    case 2:
         creationFichier();
         textcolor(couleurPrincipale);
         printf("\n\n\tCreation du fichier PERSONNEL-ANP_DZ.dat :\n");
         textcolor(YELLOW);
         printf("\n\t\t Creation en cours  ");
         textcolor(15);
         for(int l=0;l<2;l++) //animation
         {
            int x=wherex();
            y=wherey();
            textcolor(15);
            delay(150);
            printf("%c ",254);
            gotoxy(65,y);
            printf("%d %c",(100/14)*l,37);
            gotoxy(x+2,y);
        }
        Raz_index(&ind);  // reinitialiser la table d'index
        chargement_initial(&ind,&inds,&ind1,&ind2,&ind3);//appel de chargement_initial


        for(int l=2;l<14;l++)//animation
        {
            int x=wherex();
            y=wherey();
            textcolor(15);
            delay(150);
            printf("%c ",254);
            gotoxy(65,y);
            printf("%d %c",(100/14)*l,37);
            gotoxy(x+2,y);
        }
        gotoxy(65,y);
        textcolor(YELLOW);
        printf("100 %c\n\n",37);
        textcolor(15);
        printf("\n                 >> Fichier cree avec succes\n");
        textcolor(WHITE);
        retour();
        getch();
        goto menu_principale;
        break;
    case 3:
        menuChamp = 1;
        while( menuChamp != 7){
            clrscr();
            textcolor(YELLOW);
            printf("\n\n\t\tVeuillez saisir la nouvelle couleur :\n\n\n");
            textcolor(WHITE);
            menuChamp=menu(7,"\t\t\t[1]-  Vert","\t\t\t[2]-  Jaune","\t\t\t[3]-  Marron","\t\t\t[4]-  Rouge","\t\t\t[5]-  Bleu","\t\t\t[6]-  Rose"  , "\t\t\t[7]-  Retour");
            switch(menuChamp){
            case 1:
                couleurPrincipale = 10;

                break;
            case 2:
                couleurPrincipale = 14;

                break;
            case 3:
                couleurPrincipale = 6 ;

                break;
            case 4:
                couleurPrincipale = 12;

                break;
            case 5:
                couleurPrincipale = 9;

                break;
            case 6:
                couleurPrincipale = 13;

                break;
            case 7:
                break;

           }
        }
        goto debut;
        break;
    case 4:
        goto end;
        break;

    }
    retour();
    getch();
    goto menu_principale;

menu_principale:
    system("cls");
    menuPrincipale();
    textcolor(couleurPrincipale);
    gotoxy(1,14);
    printf("\tVeuillez saisir votre choix :\n\n");
    textcolor(WHITE);
    menuChamp = menu(12, "\t\t\t[1]- revenir a l'acceuil du programme.","\t\t\t[2]- Affichage.","\t\t\t[3]- Recherche d'un militaire par son matricule." ,
                     "\t\t\t[4]- Insertion d'un nouvel enregistrement au fichier PERSONNEL-ANP_DZ.dat",
                     "\t\t\t[5]- Suppression d'un enregistrement donne par le matricule.","\t\t\t[6]- Modification de la region militaire de un enregistrement donne.",
                     "\t\t\t[7]- Requete A Intervalle.","\t\t\t[8]- sauvegarde d'index.",
                     "\t\t\t[9]- chargement d'index.","\t\t\t[10]- modules optionnels.","\t\t\t[11]- changer la couleur principale du programme.","\t\t\t[12]- Quitter.");
    system("cls");
    switch (menuChamp)
    {
    case 1:
        textcolor(WHITE);
        retour_acceuil();
        getch();
        goto debut;
        break;
    case 2://affichage
        textcolor(couleurPrincipale);
        printf("\n\n\n\tVeuillez saisir votre choix :\n\n\n");
        textcolor(WHITE);
        menuChamp = menu(4, "\t\t\t[1]- Affichage de l'index", "\t\t\t[2]- Affichage d'un enregistremet","\t\t\t[3]- Affichage d'un bloc",
                         "\t\t\t[4]- Retour");
        system("cls");
        switch (menuChamp)
        {
        case 1:
            affichageIndex();
            affichge_index(&ind);
            textcolor(WHITE);
            retour();
            getch();
            goto menu_principale;
            break;
        case 2:
            affichage_enreg(Personnel());
            textcolor(WHITE);
            retour();
            getch();
            goto menu_principale;
            break;
        case 3:
            ouvrir(&f,"PERSONNEL-ANP_DZ.dat","rb");
            printf("\n\n\tVeuillez saisir le numero de bloc a afficher:\n\t\t>  ");
            scanf(" %d",&n);
            LireDir(f,n,&buf);
            affichage_bloc(f,&buf,n);
            textcolor(WHITE);
            retour();
            getch();
            goto menu_principale;
            break;
        case 4:
            goto menu_principale;
            break;
        }
        break;
    case 3:
        textcolor(couleurPrincipale);
        printf("\n\n\n\tVeuillez saisir votre choix :\n\n\n");
        textcolor(WHITE);
        menuChamp = menu(3, "\t\t\t[2]- Recherche d'une matricule generee aleatoirement ","\t\t\t[1]- Recherche manuelle",
                         "\t\t\t[3]- Retour");
        system("cls");
        switch (menuChamp)
        {
        case 1:
            textcolor(couleurPrincipale);
            printf(" \n\n               Recherche d'un militaire par son matricule ( le matricule est genere aleatoirement ):\n\n\n\n ");
            recherche_militaire (e.Matricule, f ,&ind);
            retour();
            getch();
            goto menu_principale;
            break;
        case 2:
            textcolor(couleurPrincipale);
            printf("\n\n\t> Saisir le Matricule cible : ");
            textcolor(WHITE);
            scanf(" %d",&matricule);
            while (!matricule_valide(matricule))
            {
                textcolor(RED);
                printf("\n             ! Matricule non valid !  [veuillez ressayer]\n");
                textcolor(couleurPrincipale);
                printf("\n\n\t> Saisir le Matricule cible : ");
                textcolor(WHITE);
                scanf(" %d",&matricule );
            }
            recherche_militaire (matricule, f ,&ind);
            retour();
            getch();
            goto menu_principale;
            break;
        case 3:
            goto menu_principale;
            break;
        }
         break;
    case 4:
        textcolor(couleurPrincipale);
        printf("\n\n\n\tVeuillez choisir le mode d'insertion:\n\n\n");
        textcolor(WHITE);
        menuChamp = menu(3, "\t\t\t[1]- Manuelle", "\t\t\t[2]- Aleatoire", "\t\t\t[3]- Retour");
        clrscr();
        switch (menuChamp)
        {
        case 1:
           affichInsertion();
           textcolor(couleurPrincipale);
           printf("\n\t>Matricule : ");
           textcolor(WHITE);
           scanf(" %d",&matricule );
           while (!matricule_valide(matricule))
            {
                textcolor(RED);
                printf("\n             ! Matricule non valid !  [veuillez ressayer]\n");
                textcolor(couleurPrincipale);
                printf("\n\t>Matricule : ");
                textcolor(WHITE);
                scanf(" %d",&matricule );
            }
           e2.Matricule = matricule;
           //printf("%d",e2.Matricule);

          textcolor(couleurPrincipale);
           printf("\n\t>Nom : ");
           textcolor(WHITE);
           scanf("%s", e2.Nom);
           //printf("%s",e2.Nom);

           textcolor(couleurPrincipale);
           printf("\n\t>Prenom : ");
           textcolor(WHITE);
           scanf("%s", e2.Prenom);
           //printf("%s",e2.Prenom);

           textcolor(couleurPrincipale);
           printf("\n\t>Date de naissance :\n");

           printf("\t\t>>Annee (format AAAA):");
           textcolor(WHITE);
           scanf("%4s", &e2.DateNaissance.annee);
           //printf("%s",e2.DateNaissance.annee);

           textcolor(couleurPrincipale);
           printf("\t\t>>Mois de naissance (format MM):");
           textcolor(WHITE);
           scanf("%2s", &e2.DateNaissance.mois);
          //printf("%s",e2.DateNaissance.mois);

           textcolor(couleurPrincipale);
           printf("\t\t>>Jour de naissance (format JJ): ");
           textcolor(WHITE);
           scanf("%2s", &e2.DateNaissance.jour);
           //printf("%s",e2.DateNaissance.jour);

           textcolor(couleurPrincipale);
           printf("\n\t> la wilaya de Naissance (Adrar,Chlef ,Laghouat,Oum_El_Bouaghi,Batna,Bejaia,Biskra,Bechar,Blida,Bouira,Tamanrasset, Tebessa,Tlemcen,\n");
           printf("                                 Tiaret,Tizi_Ouzou,Alger,Djelfa,Jijel,Setif,Saida,Skikda,Sidi_Bel_Abbes,Annaba,Guelma,\n");
           printf("                                 Constantine, Medea,Mostaganem,Msila,Mascara,Ouargla,Oran,El_Bayadh,Illizi,Bordj_Bou_Arreridj,Boumerdes,El_Taref,\n");
           printf("                                 Tindouf,Tissemsilt ,El_Oued,Khenchela,Souk_Ahras,Tipaza,Mila,Ain_Defla,Naama,Ain_Temouchent,Ghardaia,Relizane,\n");
           printf("                                 Timimoun,Bordj_Badji_Mokhtar,Ouled_Djellal,Beni_Abbes,In_Salah,In_Guezzam,Touggourt,Djanet,El_Megaier,El_Meniaa) : ");
           textcolor(WHITE);
           scanf("%18s", e2.WilayaNaissance);
          //printf("%s",e2.WilayaNaissance);


           textcolor(couleurPrincipale);
           printf("\n\t>Groupe sanguin (O+, A+, B+, O-, A-, AB+, B-, AB-) : ");
           textcolor(WHITE);
           scanf("%5s", e2.GroupeSanguin);
           //printf("%s",e2.GroupeSanguin);

           textcolor(couleurPrincipale);
           printf("\n\t>Grade ( GeneralCorpsArmee,General-Major,General,Colonel,Lieutenant-colonel,Commandant,Capitaine,Lieutenant,\n");
           printf("                 Sous-lieutenant,Aspirant,Adjudant-chef,Adjudant,Sergent-chef,Sergent,Caporal-chef,Caporal,Djoundi ) : ");
           textcolor(WHITE);
           scanf("%24s", e2.Grade);
           //printf("%s", e2.Grade);

           textcolor(couleurPrincipale);
           printf("\n\t>Force armee( ArmeeDeTerre,ArmeeDeAir,MarineNationale,DefenseAerienneDuTerritoire,GendarmerieNationale,GardeRepublicaine,\n");
           printf("                      DepartementDuRenseignementEtDeLaSecurite,SanteMilitaire ) :");
           textcolor(WHITE);
           scanf("%40s", e2.ForceArmee);
           //printf("%s", e2.ForceArmee);

           textcolor(couleurPrincipale);
           printf("\n\t>Region militaire ( 1RM_Blida  2RM_Oran  3RM_Bechar  4RM_Ouargla  5RM_Constantine  6RM_Tamanrasset ): ");
           textcolor(WHITE);
           scanf("%14s", e2.RegionMilitaire);
           //printf("%s", e2.RegionMilitaire);

           textcolor(YELLOW);
           printf("\n          affichage de l'enregistrement a inserer: \n\n");
           textcolor(YELLOW);
           affichage_enreg(e2);
           insertion(f,&ind,"PERSONNEL-ANP_DZ.dat",e2);


           textcolor(YELLOW);
           printf("\n\n         >>Insertion avec succes .\n");
           textcolor(WHITE);
           retour();
           getch();
           goto menu_principale;
            break;
        case 2:
             affichInsertion();// affichage
             textcolor(couleurPrincipale);
             printf(" \n\n        Insertion d'un enregistrement genere aleatoirement (recommande pour un bon affichage) \n\n\n\n ");
             while(!arret){
                textcolor(YELLOW);
                 printf("           *---  Taper un touche  ---*\n\n\n");
                 delay(500);
                 if(getch()){
                    arret=true;
                  }
                  system("cls");
               }

             e =Personnel();
             system("cls");
             textcolor(couleurPrincipale);
             affichage_enreg(e);
             textcolor(YELLOW);
             printf("\n\n\n       *---  Taper un touche pour avnacer  ---*\n\n\n");
             getch();
             system("cls");
             textcolor(couleurPrincipale);
             insertion(f,&ind,"PERSONNEL-ANP_DZ.dat",e);
             textcolor(YELLOW);
             printf("         >>Insertion avec succes .\n");
             textcolor(WHITE);
             retour();
             getch();
             goto menu_principale;
            break;
        case 3:
            goto menu_principale;
            break;
        }
        //break;
    case 5:
        textcolor(couleurPrincipale);
        printf("\n\n\n\tVeuillez choisir le mode de suppression:\n\n\n");
        textcolor(WHITE);
        menuChamp = menu(3, "\t\t\t[1]- Manuelle", "\t\t\t[2]- Aleatoire", "\t\t\t[3]- Retour");
        clrscr();
        switch (menuChamp)
        {
        case 1:
             affichSuppression();//affichage
             textcolor(couleurPrincipale);
             printf("\n\n\t>Saisir le matricule d'enregistrement a supprimer :\n\t\t> ");
             textcolor(WHITE);
             scanf(" %d",&matricule);
             while (!matricule_valide(matricule))
                  {
                      textcolor(RED);
                      printf("\n             ! Matricule non valid !  [veuillez ressayer]\n");
                      textcolor(couleurPrincipale);
                      printf("\n\t>Matricule : ");
                      textcolor(WHITE);
                      scanf(" %d",&matricule );
                 }
            suppression(f,&ind,"PERSONNEL-ANP_DZ.dat",matricule);
            textcolor(WHITE);
            retour();
            getch();
            goto menu_principale;
            break;
        case 2:
            affichSuppression();//affichage
            textcolor(couleurPrincipale);
            printf(" \n\n         suppression d'un enregistrement donne par un matricule genere aleatoirement :\n\n\n\n ");
            suppression(f,&ind,"PERSONNEL-ANP_DZ.dat",e.Matricule);
            textcolor(WHITE);
            retour();
            getch();
            goto menu_principale;
            break;
        case 3:
            goto menu_principale;
            break;
        }
        break;
    case 6://Modification
        affichModification();//affichage
        textcolor(couleurPrincipale);
        printf(" \n\n modification de la region militaire d'un enregistrement \n\n ");
        textcolor(couleurPrincipale);
        printf("\n\n\t> Saisir le Matricule cible : ");
        textcolor(WHITE);
        scanf(" %d",&matricule);
        while (!matricule_valide(matricule))
            {
                textcolor(RED);
                printf("\n             ! Matricule non valid !  [veuillez ressayer]\n");
                textcolor(couleurPrincipale);
                printf("\n\n\t> Saisir le Matricule cible : ");
                textcolor(WHITE);
                scanf(" %d",&matricule );
            }
        textcolor(couleurPrincipale);
        printf("\n\n\t> saisissez la nouvelle region :\n\n");
        printf(" ( 1RM_Blida  2RM_Oran  3RM_Bechar  4RM_Ouargla  5RM_Constantine  6RM_Tamanrasset ): ");
        scanf(" %s",region);
        system("cls");
        modif(f,&ind,matricule,region);
        retour();
        getch();
        goto menu_principale;
        break;
    case 7:
        affichRequete();
        textcolor(couleurPrincipale);
        printf("\n\n\t>Saisir le matricule inf (M1) :\n\t\t> ");
        textcolor(WHITE);
        scanf(" %d",&inf);

        while (!matricule_valide(inf))
            {
                textcolor(RED);
                printf("\n             ! Matricule non valid !  [veuillez ressayer]\n");
                textcolor(couleurPrincipale);
                printf("\n\n\t>Saisir le matricule inf (M1) :\n\t\t> ");
                textcolor(WHITE);
                scanf(" %d",&inf );
            }
        while (!matricule_existe(inf, f ,&ind)){
                textcolor(RED);
                printf("\n             ! ce matricule n'existe pas dans le fichier !  [veuillez ressayer]\n");
                textcolor(couleurPrincipale);
                printf("\n\n\t>Saisir le matricule inf (M1) :\n\t\t> ");
                textcolor(WHITE);
                scanf(" %d",&inf);
        }

        textcolor(couleurPrincipale);
        printf("\n\n\t>Saisir le matricule sup (M2) :\n\t\t> ");
        textcolor(WHITE);
        scanf(" %d",&sup);
        while (!matricule_valide(sup))
            {
                textcolor(RED);
                printf("\n             ! Matricule non valid !  [veuillez ressayer]\n");
                textcolor(couleurPrincipale);
                printf("\n\n\t>Saisir le matricule sup (M2) :\n\t\t> ");
                textcolor(WHITE);
                scanf(" %d",&sup );
            }

        while (!matricule_existe(sup, f ,&ind)){
                textcolor(RED);
                printf("\n             ! ce matricule n'existe pas dans le fichier !  [veuillez ressayer]\n");
                textcolor(couleurPrincipale);
                printf("\n\n\t>Saisir le matricule sup (M2) :\n\t\t> ");
                textcolor(WHITE);
                scanf(" %d",&sup);
        }
        //inf=ind.tab[10].Matricule;
        //sup=ind.tab[11].Matricule;

        Requete_intervalle(&ind,inf,sup,&cont);
        affichage_bloc(f,&cont,0);
        retour();
        getch();
       goto menu_principale;
       break;
     case 8:
        affichSauvegarde();//affichage
        sauvgarde_index(&ind);
        retour();
        getch();
        goto menu_principale;
        break;
    case 9:
        affichChargement();//affichage
        Chargement_idex(&ind);
        retour();
        getch();
        goto menu_principale;
        break;
    case 10:
        textcolor(couleurPrincipale);
        printf("\n\n\n\tVeuillez saisir votre choix\n\n");
        textcolor(YELLOW);
        menu_creation = menu(5,"\t\t\t[1]- Suppression de tous les enregistrements relatifs a une force armee donnee .",
                              "\t\t\t[2]-  Affichage de tous les enregistrements relatifs a region militaire donnee ayant un age entre A1 et A2.",
                               "\t\t\t[3]- Affichage de tous les enregistrements appartenant a une categorie de grades donnee .",
                             "\t\t\t[4]- fragmentation.","\t\t\t[5]- retour.");
        system("cls");
        switch (menu_creation)
        {
        case 1:
            textcolor(couleurPrincipale);
            printf("\n\n\n\tVeuillez choisir la force Armee cible\n\n");
            textcolor(YELLOW);
            menu_supression = menu(8,"\t\t\t[1]- Armee De Terre.", "\t\t\t[2]- Armee De l'Air.","\t\t\t[3]- MarineNationale.",
                                    "\t\t\t[4]- Defense Aerienne Du Territoire.","\t\t\t[5]- GendarmerieNationale.",
                                    "\t\t\t[6]- GardeRepublicaine.","\t\t\t[7]- DepartementDuRenseignementEtDeLaSecurite.",
                                    "\t\t\t[8]- SanteMilitaire .");
            supression_Force(&ind,&inds,menu_supression);
            textcolor(WHITE);
            retour();
            getch();
            goto menu_principale;
            break;
        case 2:

             textcolor(couleurPrincipale);
             printf("\n\n\n\tVeuillez choisir la region militaire  cible\n\n");
             textcolor(YELLOW);
             menu_region = menu(6,"\t\t\t[1]- 1RM_Blida.", "\t\t\t[2]- 2RM_Oran.","\t\t\t[3]- 3RM_Bechar.",
                                    "\t\t\t[4]- 4RM_Ouargla.","\t\t\t[5]- 5RM_Constantine.", "\t\t\t[6]- 6RM_Tamanrasset.");

             textcolor(couleurPrincipale);
             printf("\n\n\n\tEntrez l'age minimale :\n\t\t> ");
             textcolor(WHITE);
             scanf(" %d",&ageMin);

             textcolor(couleurPrincipale);
             printf("\n\n\n\tEntrez l'age maximale :\n\t\t> ");
             textcolor(WHITE);
             scanf(" %d",&ageMax);

             m = recherche_sec(menu_region ,ageMin,ageMax,&ind,&ind1,&ind2 );
             printf("\n\n\n\tAfichage ( par nemuro de bloc et deplacement ) de tous les enregistrements correspondants: \n\n");
             afficherListe(m);
             textcolor(WHITE);
             retour();
             getch();
             goto menu_principale;
            break;
        case 3:

             textcolor(couleurPrincipale);
             printf("\n\n\n\tVeuillez choisir la categorie de grades des enregsitrements que vous voulez afficher \n\n");
             textcolor(YELLOW);
             menu_grade = menu(5,"\t\t\t[1]- Officiers-generaux.", "\t\t\t[2]- officiers-superieurs.","\t\t\t[3]- officiers.",
                                    "\t\t\t[4]- sous-officiers.","\t\t\t[5]- hommes de troupes.");
             listeMat = ind3.tab[menu_grade-1].tetep;// de o a 4 et pas de 1 a 5

             printf("\n>>> Afichage ( par matricules ) de tous les enregistrements appartenant a la categorie choisie: \n\n");
             afficherListeGrade( listeMat, f ,&ind);

             textcolor(WHITE);
             retour();
             getch();
             goto menu_principale;
            break;
        case 4:
            textcolor(couleurPrincipale);
            printf("\n\n                 fragmentation de PERSONNEL-ANP_DZ.dat en cours ................... \n\n");
            fragmenter("PERSONNEL-ANP_DZ.dat");
            textcolor(WHITE);
            printf("\n\n                  >>> le fichier est fragmente avec succes \n");

            textcolor(WHITE);
            retour();
            getch();
            goto menu_principale;
            break;
        case 5:
            goto menu_principale;
            break;
        }
        break;
    case 11:
        menuChamp = 1;
        while( menuChamp != 7){
            clrscr();
            textcolor(YELLOW);
            printf("\n\n\t\tVeuillez saisir la nouvelle couleur :\n\n\n");
            textcolor(WHITE);
            menuChamp=menu(7,"\t\t\t[1]-  Vert","\t\t\t[2]-  Jaune","\t\t\t[3]-  Marron","\t\t\t[4]-  Rouge","\t\t\t[5]-  Bleu","\t\t\t[6]-  Rose"  , "\t\t\t[7]-  Retour");
            switch(menuChamp){
            case 1:
                couleurPrincipale = 10;

                break;
            case 2:
                couleurPrincipale = 14;

                break;
            case 3:
                couleurPrincipale = 6 ;

                break;
            case 4:
                couleurPrincipale = 12;

                break;
            case 5:
                couleurPrincipale = 9;

                break;
            case 6:
                couleurPrincipale = 13;

                break;
            case 7:
                break;

           }
        }
        goto menu_principale;
        break;
    case 12://quitter le programme
       goto end;
        break;
    }

end:
    clrscr();
    fin();
    sortir();
    getch();
    goto closing;

closing:
    clrscr();
    soldier();

}


