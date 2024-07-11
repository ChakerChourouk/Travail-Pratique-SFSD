#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdarg.h>
#include "ANP.h"
#include <stdbool.h>
#include "conio2.h"
#include <dirent.h>

#define selected_color 0
#define not_selected_color 15
#define not_selected_background 0

int couleurPrincipale ;

// Fonction pour afficher un menu et obtenir l'entrée de l'utilisateur :----------------------------------------------------------------
int menu(int max, ...)
{
    // Vérifier s'il y a des éléments de menu
    if (max > 0)
    {
        int choi, a, i, b, d, y; // Variables pour l'entrée utilisateur et la navigation dans le menu
        char p[50]; // Tampon temporaire pour la lecture des éléments de menu
        char **choix = NULL; // Tableau pour stocker les éléments de menu
        choix = malloc(max * sizeof(p)); // Allouer de la mémoire pour les éléments de menu
        va_list marker;
        va_start(marker, max); // Initialiser les arguments variables.

        // Lire les éléments de menu des arguments variables et les stocker dans le tableau
        for (i = 0; i < max; i++)
        {
            choix[i] = va_arg(marker, char *);
        }

        va_end(marker); // Fin des arguments variables

        d = wherey(); // Obtenir la position y actuelle
        y = d; // Initialiser la position y

        textcolor(selected_color); // Définir la couleur du texte pour l'élément sélectionné
        textbackground(couleurPrincipale); // Définir la couleur de fond pour les éléments non sélectionnés
        printf("%s\n", choix[0]); // Afficher le premier élément du menu

        textbackground(not_selected_background); // Réinitialiser la couleur de fond pour les éléments non sélectionnés
        textcolor(not_selected_color); // Définir la couleur du texte pour les éléments non sélectionnés

        // Afficher le reste des éléments du menu
        for (i = 1; i < max; i++)
        {
            printf("%s\n", choix[i]);
        }

    eticette: // Étiquette pour la continuation de la boucle

        // Attendre l'entrée de l'utilisateur
        while ((a = getch()) == 224)
        {
            b = getch(); // Lire le deuxième octet du code de touche étendu

            // Vérifier si la touche de flèche vers le bas est pressée et que ce n'est pas le dernier élément du menu
            if ((b == 80) && (y < d + max - 1))
            {
                gotoxy(1, y); // Se déplacer à la position actuelle
                textcolor(not_selected_color); // Définir la couleur du texte pour l'élément non sélectionné
                i = y - d; // Calculer l'indice de l'élément actuel
                textbackground(not_selected_background); // Définir la couleur de fond pour l'élément non sélectionné
                printf("%s", choix[i]); // Redessiner l'élément actuel
                y++; // Se déplacer vers l'élément suivant
                textcolor(selected_color); // Définir la couleur du texte pour l'élément sélectionné
                gotoxy(1, y); // Se déplacer vers la nouvelle position
                textbackground(couleurPrincipale); // Réinitialiser la couleur de fond pour l'élément non sélectionné
                printf("%s", choix[i + 1]); // Redessiner le nouvel élément
            }

            // Vérifier si la touche de flèche vers le haut est pressée et que ce n'est pas le premier élément du menu
            if (b == 72 && y > d)
            {
                gotoxy(1, y); // Se déplacer à la position actuelle
                textcolor(not_selected_color); // Définir la couleur du texte pour l'élément non sélectionné
                i = y - d; // Calculer l'indice de l'élément actuel
                textbackground(not_selected_background); // Définir la couleur de fond pour l'élément non sélectionné
                printf("%s", choix[i]); // Redessiner l'élément actuel
                y--; // Se déplacer vers l'élément précédent
                textcolor(selected_color); // Définir la couleur du texte pour l'élément sélectionné
                gotoxy(1, y); // Se déplacer vers la nouvelle position
                textbackground(couleurPrincipale); // Réinitialiser la couleur de fond pour l'élément non sélectionné
                printf("%s", choix[i - 1]); // Redessiner le nouvel élément
            }
        }

        // Vérifier si la touche Entrée est pressée
        if (a != 13)
            goto eticette; // Continuer la boucle si la touche Entrée n'est pas pressée

        choi = y - d; // Calculer l'indice de l'élément sélectionné
        textbackground(not_selected_background); // Réinitialiser la couleur de fond pour les éléments non sélectionnés
        textcolor(not_selected_color); // Définir la couleur du texte pour les éléments non sélectionnés
        gotoxy(1, d + max); // Se déplacer à une nouvelle ligne
        return choi + 1; // Retourner l'indice de l'élément sélectionné (incrémenté de 1)

    }
    else
        return -1; // Retourner -1 s'il n'y a pas d'éléments de menu
}



// page home :------------------------------------------------------------------------------------------------------------------------------------
void home()
{

printf("\n\n\n\n");
textcolor(RED);
printf("\t\t\t\t   ___________________________________________________________________________________________________________________________\n\t\t\t\t");
printf(" / \                                                                                                                           \\.\n\t\t\t\t");
printf("|   |                                                                                                                         |.\n\t\t\t\t");
printf("\\__ |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |");
textcolor(WHITE);
printf("          ___  ___ _                                                                                                     ");
textcolor(RED);
printf("|.\n\t\t\t\t");
printf("    |");
textcolor(WHITE);
printf("         / _ \\/ __| |                                                                                                    ");
textcolor(RED);
printf("|.\n\t\t\t\t");
printf("    |");
textcolor(YELLOW);
printf("        |  __/\\__ \\ |                 Ecole Nationale Superieure d'informatique   (ex INI)                               ");
textcolor(RED);
printf("|.\n\t\t\t\t");
printf("    |");
textcolor(YELLOW);
printf("         \\___||___/_|                 Cycle preparatoire integre (2CPI)                                                 ");
textcolor(RED);
printf(" |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t ");
printf("   |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |");
textcolor(couleurPrincipale);
printf("                  Travail Pratique - SFSD :");
textcolor(WHITE);
printf("         Ficher de donnees non ordonne TObarreF avec un                       ");
textcolor(RED);
printf("|.\n\t\t\t\t");
printf("    |");
textcolor(WHITE);
printf("                                                    Index dense en MC et un fichier index TOF                            ");
textcolor(RED);
printf("|.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |");
textcolor(couleurPrincipale);
printf("                  Realise par :");
textcolor(WHITE);
printf("         Chaker Chourouk    Aouni Nazim Abdeerhmane");
textcolor(WHITE);
printf("        section B Groupe 05            ");
textcolor(RED);
printf("|.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |");
textcolor(couleurPrincipale);
printf("                  Encadre par :");
textcolor(WHITE);
printf("         Mr. Kermi Adel                                                                   ");
textcolor(RED);
printf("|.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");

printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |");
textcolor(YELLOW);
printf("                                     Appuyer Sur La Touche Entree Pour Continuer                                         ");
textcolor(RED);
printf("|.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |                                                                                                                         |.\n\t\t\t\t");
printf("    |   ______________________________________________________________________________________________________________________|__.\n\t\t\t\t");
printf("    |  /                                                                                                                         /.\n\t\t\t\t");
printf("    \\_/_________________________________________________________________________________________________________________________/.\n\t\t\t\t");
gotoxy(1, 1);
getch();

}


// page acceuil :---------------------------------------------------------------------------------------------------------------------------------
void accueil()
{
textcolor(couleurPrincipale);
printf("\n\n");
printf("                               ##                                        #                                                                                                     \n");
printf("                                 #                                        #                                                                                                     \n");
printf("                 #   #   ###     #     ###    ###   ## #    ###          ####    ###           ###   #   #  # ##          # ##   # ##    ###    ## #  # ##    ###   ## #        \n");
printf("                 #   #  #   #    #    #   #  #   #  # # #  #   #          #     #   #         #   #  #   #  ##  #         ##  #  ##  #  #   #  #  #   ##  #      #  # # #       \n");
printf("                 # # #  #####    #    #      #   #  # # #  #####          #     #   #         #   #  #   #  #             ##  #  #      #   #   ##    #       ####  # # #        \n");
printf("                 # # #  #        #    #   #  #   #  # # #  #              #  #  #   #         #   #  #  ##  #             # ##   #      #   #  #      #      #   #  # # #        \n");
printf("                  # #    ###    ###    ###    ###   #   #   ###            ##    ###           ###    ## #  #             #      #       ###    ###   #       ####  #   #        \n");
printf("                                                                                                                          #                    #   #                             \n");
printf("                                                                                                                          #                     ###                              \n\n");
textcolor(WHITE);
}



// page avant fin :-------------------------------------------------------------------------------------------------------------------------------
void fin()
{
char AsciiCode = 219;
    textcolor(WHITE);
    printf ("\n\n\tSauvgrade des fichiers en cour  [");
    for  (int i=0; i<=40; i++)
    {
        textcolor(couleurPrincipale);
        printf ("%c",219);Sleep(18);

    }
    textcolor(WHITE);
    printf ("] TERMINE \n\n\n\n");
    Sleep(300);


    textcolor(couleurPrincipale);
    Sleep(150);
     printf("\t\t\t %c%c%c%c%c      %c%c%c%c%c%c  %c%c %c%c%c%c%c%c%c %c%c%c    %c%c %c%c%c%c%c%c%c%c  %c%c%c%c%c%c  %c%c%c%c%c%c%c%c  \n",AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode);Sleep(150);
    printf("\t\t\t%c%c   %c%c     %c%c   %c%c %c%c %c%c      %c%c%c%c   %c%c    %c%c    %c%c    %c%c    %c%c     \n",AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode);Sleep(150);
    printf("\t\t\t%c%c%c%c%c%c%c     %c%c%c%c%c%c  %c%c %c%c%c%c%c   %c%c %c%c  %c%c    %c%c    %c%c    %c%c    %c%c     \n",AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode);Sleep(150);
    printf("\t\t\t%c%c   %c%c     %c%c   %c%c %c%c %c%c      %c%c  %c%c %c%c    %c%c    %c%c    %c%c    %c%c     \n",AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode);Sleep(150);
    printf("\t\t\t%c%c   %c%c     %c%c%c%c%c%c  %c%c %c%c%c%c%c%c%c %c%c   %c%c%c%c    %c%c     %c%c%c%c%c%c     %c%c     \n\n\n\n",AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode,AsciiCode);Sleep(150);

}


// appuyer pour sortir du programme : -------------------------------------------------------------------------------------------------------------
void sortir()
{
    textcolor(couleurPrincipale);
    printf("\n\n\t\t _____________________________________________________\n");
    printf("\t\t|                                                     |\n");
    printf("\t\t|   ");
    textcolor(YELLOW);
    printf("Appuyer ENTRER pour sortir du programme");
    textcolor(couleurPrincipale);
    printf("           |\n");
    printf("\t\t|_____________________________________________________|\n");

    textcolor(WHITE);
}


//--------------------------------------------------------------------------------------------------------------------------------------------
void retour_acceuil()
{
    textcolor(couleurPrincipale);
    printf("\n\n\t\t _____________________________________________________\n");
    printf("\t\t|                                                     |\n");
    printf("\t\t|   ");
    textcolor(YELLOW);
    printf("Appuyer ENTRER pour revenir a l'acceuil ");
    textcolor(couleurPrincipale);
    printf("          |\n");
    printf("\t\t|_____________________________________________________|\n");

    textcolor(WHITE);
}


//-------------------------------------------------------------------------------------------------------------------------------------------
void fichierExistant()
{
    textcolor(couleurPrincipale);
    printf("\n\n");
    printf("     _____ _      _     _                           _     _              _       \n");
    printf("    |  ___(_) ___| |__ (_) ___ _ __ ___    _____  _(_)___| |_ __ _ _ __ | |_ ___ \n");
    printf("    | |_  | |/ __| '_ \\| |/ _ \\ '__/ __|  / _ \\ \\/ / / __| __/ _` | '_ \\| __/ __|\n");
    printf("    |  _| | | (__| | | | |  __/ |  \\__ \\ |  __/>  <| \\__ \\ || (_| | | | | |_\\__ \\ \n");
    printf("    |_|   |_|\\___|_| |_|_|\\___|_|  |___/  \\___/_/\\_\\_|___/\\__\\__,_|_| |_|\\__|___/\n\n");

    textcolor(WHITE);
}

//-------------------------------------------------------------------------------------------------------------------------------------------
void soldier(){
textcolor(couleurPrincipale);
printf("\n\n");
printf("                                              .......::.:                                                               #           \n");
printf("                                           .:::           .:::                               ## #    ##   # #    ###   ##          \n");
printf("                                          -.                  --                             # # #  # ##  ## #  #       #          \n");
printf("                                        .=                      =                            # # #  ##    #     #       #         \n");
printf("                                        =     ..::..........    .+                           #   #   ###  #      ###   ###          \n");
printf("                 --                    +. :::.  .:::::::::::..::.:-                                                                            \n");
printf("                 *.+                  -=::::::::.           .--=-:+                                                                           \n");
printf("                 :-=:               .-::+*                    :- =--:                            #   ##                                           \n");
printf("                  + +              := =:-=                    :+..+.=-                           #   #                    #                     \n");
printf("                  --=               -:+:=*                     =    *.                         ###  #   ###  # #   ##    ##   ###                                \n");
printf("                   #:*               =:                             =                         #  #     #  #  # #  #  #    #   #  #                                 \n");
printf("                   .+#-:+:.           +   :                    ::.:-.                         #  #     # ##  # #  #  #    #   #                                 \n");
printf("                   *+-=   +            ::-=                    #                               ###      # #   #    ##    ###  #                        \n");
printf("                    + -- --               --                 :=                                                                            \n");
printf("                    :*:#: -                :=:            :-+.                                                                                     \n");
printf("                     :-:* -                 :-*::--:--::::  +::.:..                                                                               \n");
printf("                        +--=              :-  *  :===::   .+:      :-                                 #         ##                                    \n");
printf("                      --  .*.            .=   -=+.-   :+:=-          +.                               #     #    #    #                           \n");
printf("                       -=:. =            *.:    : =    ..     ..      +.                       #  #  ###   ##    #   ##    ###   ##   ###                                 \n");
printf("                        =   -           .*:: .  . =   :      ..*       #.                      #  #   #     #    #    #   ##    # ##  #  #                           \n");
printf("                        .-   +          * =   ... =   .  .. . .-:      .+                      #  #   #     #    #    #     ##  ##    #                               \n");
printf("                         *   -:        +- +     . =   .       . +       +                       ###    ##  ###  ###  ###  ###    ##   #                                      \n");
printf("                         .-  --::::----.  =.   .  +    ..   ..  +       :+                                                                              \n");
printf("                          +.+ .. .*       +       +             =:       =                                                                              \n");
printf("                        .*  *-+*. *       =:      -:            :+       =:                                  #                                      \n");
printf("                         #:-:#.=::+:      :=.::=-::-::==::::::::-*        +                                  #                           \n");
printf("                         =-::*..- +*    .-=-:::+-:::::=+:::::::::        +                      ###    ##   ###   ###    ##                                                 \n");
printf("                          -=:=- :*.-::-:. +                      @        +                     #  #  #  #   #    #  #  # ##                    \n");
printf("                            =:   *=       *      +               @        +                     #  #  #  #   #    #     ##                                   \n");
printf("                             +   *:-     .+      :-::            .+:::::+:                      #  #   ##     ##  #      ##                                  \n");
printf("                             -.  * +     -=         =            *      :.                                                                           \n");
printf("                              =  -.*     -=         --           +-     :.                                                                            \n");
printf("                              = .:+-=+   :=         :+            =-::::-                       ###    ###    ##    ###   ###    ###   # #   # #    ##                         \n");
printf("                            .:+ -:===:   .+          =            --                            #  #   #  #  #  #  #  #   #  #  #  #   ####  ####  # ##          \n");
printf("                           .:-+     +     *          #.           +.                            #  #   #     #  #   ##    #     # ##   #  #  #  #  ##                          \n");
printf("                           ::=+    -.     .*.        :+           #                             ###    #      ##   #      #      # #   #  #  #  #   ##                     \n");
printf("                            -:=    +        :=-.   ..:#.         +-                             #                   ###                                      \n");
printf("                              =    -.         :+..... #=+-.    .+=                                                                                        \n");
printf("                              -     =          =      * + :::::.*                          \n");
printf("                             =.     -         .+.     # :=      +                          \n");
printf("                            .-       +    .--:        * =      +                          \n");
printf("                            =        +   +-         .:* =.      +.                         \n");
printf("                            =:::..:::=   .---------:.  *.        ==                        \n");
printf("                                                       +=:.     :=-                        \n\n");

textcolor(WHITE);
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void retour()
{
    textcolor(couleurPrincipale);
    printf("\n\n\t\t _____________________________________________________\n");
    printf("\t\t|                                                     |\n");
    printf("\t\t|   ");
    textcolor(YELLOW);
    printf("Appuyer ENTRER pour aller au MENU PRINCIPAL");
    textcolor(couleurPrincipale);
    printf("       |\n");
    printf("\t\t|_____________________________________________________|\n");

    textcolor(WHITE);
}

//--------------------------------------------------------------------------------------------------------------------------------------------

void menuPrincipale()
{

    textcolor(couleurPrincipale);
    printf("\n\n");
    printf("     __  __                    _____      _            _             _ \n");
    printf("    |  \\/  |                  |  __ \\    (_)          (_)           | |\n");
    printf("    | \\  / | ___ _ __  _   _  | |__) | __ _ _ __   ___ _ _ __   __ _| |\n");
    printf("    | |\\/| |/ _ \\ '_ \\| | | | |  ___/ '__| | '_ \\ / __| | '_ \\ / _` | |\n");
    printf("    | |  | |  __/ | | | |_| | | |   | |  | | | | | (__| | |_) | (_| | |\n");
    printf("    |_|  |_|\\___|_| |_|\\__,_| |_|   |_|  |_|_| |_|\\___|_| .__/ \\__,_|_|\n");
    printf("                                                        | |            \n");
    printf("                                                        |_|            \n\n");

    textcolor(WHITE);
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void accueill()
{

    textcolor(couleurPrincipale);
    printf("\n\n");
    printf("     ____                                               _ _ \n");
    printf("    |  _ \\ __ _  __ _  ___     __ _  ___ ___ _   _  ___(_) |\n");
    printf("    | |_) / _` |/ _` |/ _ \\   / _` |/ __/ __| | | |/ _ \\ | |\n");
    printf("    |  __/ (_| | (_| |  __/  | (_| | (_| (__| |_| |  __/ | |    \n");
    printf("    |_|   \\__,_|\\__, |\\___|   \\__,_|\\___\\___|\\__,_|\\___|_|_|\n");
    printf("                |___/                                       \n\n");
    textcolor(WHITE);
}


//-------------------------------------------------------------------------------------------------------------------------------------------
void creationFichier()
{
    textcolor(couleurPrincipale);
    printf("\n\n");
    printf("       ____       __       _   _               _____ _      _     _           \n");
    printf("      / ___|_ __ /_/  __ _| |_(_) ___  _ __   |  ___(_) ___| |__ (_) ___ _ __ \n");
    printf("     | |   | '__/ _ \\/ _` | __| |/ _ \\| '_ \\  | |_  | |/ __| '_ \\| |/ _ \\ '__|\n");
    printf("     | |___| | |  __/ (_| | |_| | (_) | | | | |  _| | | (__| | | | |  __/ |   \n");
    printf("      \\____|_|  \\___|\\__,_|\\__|_|\\___/|_| |_| |_|   |_|\\___|_| |_|_|\\___|_|   \n\n");
    textcolor(WHITE);
}

//-------------------------------------------------------------------------------------------------------------------------------------------
void affichageIndex(){

    textcolor(couleurPrincipale);
    printf("\n\n");
    printf("         _      __   __  _        _                           ___             _           \n");
    printf("        / \\    / _| / _|(_)  ___ | |__    __ _   __ _   ___  |_ _| _ __    __| |  ___  __  __  \n");
    printf("       / _ \\  | |_ | |_ | | / __|| '_ \\ /  _` | / _` | / _ \\  | | | '_ \\  / _` | / _ \\ \\ \\/ /   \n");
    printf("      / ___ \\ |  _||  _|| || (__ | | | || (_| || (_| ||  __/  | | | | | || (_| ||  __/  >  <    \n");
    printf("     /_/   \\_\\|_|  |_|  |_| \\___||_| |_||\__,_ | \\ __,| \\___| |___||_| |_| \\__,_| \\___| /_/\\_\\    \n");
    printf("                                                |___/                                      \n\n");
   textcolor(WHITE);
}

//-------------------------------------------------------------------------------------------------------------------------------------------
void affichInsertion(){
    textcolor(couleurPrincipale);
    printf("\n\n");
    printf("    ___                     _   _             \n");
    printf("   |_ _|_ __  ___  ___ _ __| |_(_) ___  _ __  \n");
    printf("    | || '_ \\/ __|/ _ \\ '__| __| |/ _ \\| '_ \\  \n");
    printf("    | || | | \\__ \\  __/ |  | |_| | (_) | | | |   \n");
    printf("   |___|_| |_|___/\\___|_|   \\__|_|\\___/|_| |_|    \n\n");
    textcolor(WHITE);
}

//-------------------------------------------------------------------------------------------------------------------------------------------
void affichSuppression(){
    textcolor(couleurPrincipale);
    printf("\n\n");
    printf("    ____                                      _              \n");
    printf("   / ___| _   _ _ __  _ __  _ __ ___  ___ ___(_) ___  _ __    \n");
    printf("   \\___ \\| | | | '_ \\| '_ \\| '__/ _ \\/ __/ __| |/ _ \\| '_ \\     \n");
    printf("    ___) | |_| | |_) | |_) | | |  __/\\__ \\__ \\ | (_) | | | |     \n");
    printf("   |____/ \\__,_| .__/| .__/|_|  \\___||___/___/_|\\___/|_| |_|     \n");
    printf("               |_|   |_|                                                \n\n");
    textcolor(WHITE);
}

//-------------------------------------------------------------------------------------------------------------------------------------------
void affichModification(){
    textcolor(couleurPrincipale);
    printf("\n\n");
    printf("    __  __           _ _  __ _           _   _             \n");
    printf("   |  \\/  | ___   __| (_)/ _(_) ___ __ _| |_(_) ___  _ __  \n");
    printf("   | |\\/| |/ _ \\ / _` | | |_| |/ __/ _` | __| |/ _ \\| '_ \\   \n");
    printf("   | |  | | (_) | (_| | |  _| | (_| (_| | |_| | (_) | | | |   \n");
    printf("   |_|  |_|\\___/ \\__,_|_|_| |_|\\___\\__,_|\\__|_|\\___/|_| |_|    \n\n");
    textcolor(WHITE);
}

//-------------------------------------------------------------------------------------------------------------------------------------------
void affichRequete(){
    textcolor(couleurPrincipale);
    printf("\n\n");
printf("     ____                       _         \n");
printf("    |  _ \\ ___  __ _ _   _  ___| |_ ___     \n");
printf("    | |_) / _ \\/ _` | | | |/ _ \\ __/ _ \\    \n");
printf("    |  _ <  __/ (_| | |_| |  __/ ||  __/    \n");
printf("    |_| \\_\\___|\\__, |\\__,_|\\___|\\__\\___|     \n");
printf("              |_|                        \n\n");
    textcolor(WHITE);
}

//-------------------------------------------------------------------------------------------------------------------------------------------
void affichSauvegarde(){
    textcolor(couleurPrincipale);
    printf("\n\n");
printf("                                              _        _           _              \n");
printf("     ___  __ _ _   ___   ____ _  __ _ _ __ __| | ___  (_)_ __   __| | _____  __     \n");
printf("    / __|/ _` | | | \\ \\ / / _` |/ _` | '__/ _` |/ _ \\ | | '_ \\ / _` |/ _ \\ \\/ /      \n");
printf("    \\__ \\ (_| | |_| |\\ V / (_| | (_| | | | (_| |  __/ | | | | | (_| |  __/>  <        \n");
printf("    |___/\\__,_|\\__,_| \\_/ \\__, |\\__,_|_|  \\__,_|\\___| |_|_| |_|\\__,_|\\___/_/\\_\\      \n");
printf("                          |___/                                                       \n\n");
    textcolor(WHITE);
}

//-------------------------------------------------------------------------------------------------------------------------------------------
void affichChargement(){
    textcolor(couleurPrincipale);
    printf("\n\n");
printf("      ____ _                                               _     ___           _              \n");
printf("     / ___| |__   __ _ _ __ __ _  ___ _ __ ___   ___ _ __ | |_  |_ _|_ __   __| | _____  __    \n");
printf("    | |   | '_ \\ / _` | '__/ _` |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __|  | || '_ \\ / _` |/ _ \\ \\/ /    \n");
printf("    | |___| | | | (_| | | | (_| |  __/ | | | | |  __/ | | | |_   | || | | | (_| |  __/>  <      \n");
printf("     \\____|_| |_|\\__,_|_|  \\__, |\\___|_| |_| |_|\\___|_| |_|\\__| |___|_| |_|\\__,_|\\___/_/\\_\\     \n");
printf("                           |___/                                                                  \n\n");
    textcolor(WHITE);
}


// modules d'affichage :---------------------------------------------------------------------------------------------------------------

void affichage_bloc(FILE *F,buffer *buf,int i) // i est le numero de bloc à afficher
{
    if( i > entete(F,1)){
       textcolor(RED);
       printf("\n             ! ce bloc n'existe pas dans le fichier !\n");
    }else{

int k,j;
printf("-------------------------------------------------------------------- Bloc N  : ");
printf("%d -----------------------------------------------------------------------  \n", i);
printf("| Matricule |  Nom  | Prenom | Date de naissance  | Wilaya de naissance |  G.S  |         Grade         |        Force Armee       |  Region militaire  |\n ");
printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");

for(k=0;k< buf->nb;k++){  // itération à travers les enregistrement
printf("|   %d  ",buf->tab[k].Matricule);              // matricule au maximum 9 (6 effectif)
printf("| ");
j=0;
while((buf->tab[k].Nom[j]!='0') && (j<5)){

printf("%c", buf->tab[k].Nom[j]);     // on tranque le nom dans l'affichage pour une meilleur visualization du bloc
j++;
}
if(j<5){
printf(" ");
}
printf(" | ");
j=0;
while((buf->tab[k].Prenom[j]!='0') && (j<6)){

printf("%c", buf->tab[k].Prenom[j]);     // on tranque le nom dans l'affichage pour une meilleur visualization du bloc
j++;
}
while(j<6){
printf(" ");  //combler avec des espaces pour les prenoms avec moins de 7 caracteres
j++;
}
printf(" |     ");
int day = atoi(buf->tab[k].DateNaissance.jour);
        int month = atoi(buf->tab[k].DateNaissance.mois);

        // formatter la date (deux chiffres pour le mois et deux chiffres pour le jour)
        printf("%02d/%02d/%s", day, month, buf->tab[k].DateNaissance.annee);
printf("     | ");
j=0;
printf("  ");
while((buf->tab[k].WilayaNaissance[j]!='\0') && (j<18)){
printf("%c",buf->tab[k].WilayaNaissance[j]);
j++;
}
while(j<18){
printf(" ");                  // combler avec des espaces pour les wilyas avec peu de caracteres
j++;
}
printf("| ");
j=0;
while(buf->tab[k].GroupeSanguin[j]!='\0'){
printf("%c",buf->tab[k].GroupeSanguin[j]);
j++;
}
while(j<4){
printf(" ");
j++;
}
printf("  | ");
j=0;
while(buf->tab[k].Grade[j]!='\0' && j<21){
printf("%c",buf->tab[k].Grade[j]);
j++;
}
while(j<21){
printf(" ");
j++;
}
printf( " | ");
j=0;
while((j<24 )&& (buf->tab[k].ForceArmee[j]!='\0')){
printf("%c", buf->tab[k].ForceArmee[j]);
j++;
}
while(j<24){
printf(" ");
j++;
}
printf(" | ");
j=0;
while((j<16) && (buf->tab[k].RegionMilitaire[j]!='\0')){
printf("%c", buf->tab[k].RegionMilitaire[j]);
j++;
}
while(j<16){
printf(" ");
j++;
}
printf("   |");
printf("\n");
printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}
printf(" NB : ");
printf(" |        |\n");
printf("       |   %d   | \n",buf->nb);
//printf("       |        | \n");
printf("        --------  \n");

}
}


void affichge_index(Index *ind){
printf("-----------------------------  Index   ");
printf("-----------------------------\n");
printf("--------------------------------------------------------------------\n");
printf("|   Matricule   |  Numero de bloc  |    deplacement dans le bloc   | \n");
printf("--------------------------------------------------------------------\n");
int i;
for(i=0;i<ind->nbi;i++){
printf("     ");
printf( "%d",ind->tab[i].Matricule);
printf("     ");
printf("| ");
printf("       ");
printf("%03d",ind->tab[i].nbloc);
printf("       | ");
printf("             ");
printf("%04d",ind->tab[i].dep);
printf("             | ");
printf("\n");
printf("--------------------------------------------------------------------\n");
}
printf(" NBI : ");
printf("|   %d   | \n",ind->nbi);
//printf("       |        | \n");
printf("----------------  \n");

};


void affichage_enreg(enreg e){
printf("-------------------------------  < Enregistrement >  -------------------------------\n");
printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
printf("|       Matricule       |  ");
printf( " %d",e.Matricule);
printf(" \n");
printf("------------------------------------------------------------------------------------\n");
printf("|           Nom         |  ");
printf(e.Nom);
printf(" \n");
printf("------------------------------------------------------------------------------------\n");
printf("|         Prenom        |  ");
printf(e.Prenom);
printf(" \n");
printf("------------------------------------------------------------------------------------\n");
printf("|   Date de naissance   |  ");
printf(e.DateNaissance.jour);
printf("/");
printf(e.DateNaissance.mois);
printf("/");
printf(e.DateNaissance.annee);
printf(" \n");
printf("------------------------------------------------------------------------------------\n");
printf("|  Wilaya de naissance  |  ");
printf(e.WilayaNaissance);
printf(" \n");
printf("------------------------------------------------------------------------------------\n");
printf("|    Groupe Sanguin     |  ");
printf(e.GroupeSanguin);
printf(" \n");
printf("------------------------------------------------------------------------------------\n");
printf("|         Grade         |  ");
printf(e.Grade);
printf(" \n");
printf("------------------------------------------------------------------------------------\n");
printf("|      Force Armee      |  ");
printf(e.ForceArmee);
printf(" \n");
printf("------------------------------------------------------------------------------------\n");
printf("|    Region militaire   |  ");
printf(e.RegionMilitaire);
printf(" \n");
printf("------------------------------------------------------------------------------------\n");
}



// modules de controles de saisie :--------------------------------------------------------------------------------------------------------------
bool matricule_valide (int matric)
{
    char x;
    int pos;
    if ((matric > 999999) || (matric < 111111)){
        return false;
    }

    return true;
}
bool matricule_existe (int matric, FILE* F ,Index *ind){
    bool x;
    int pos;
    recherche_dicho_Index( ind, ind->nbi,matric,  &x, &pos);
    if(x){
        return true;
    }else{
        textcolor(RED);
        return false;
    }
}

bool fichier_existe(FILE* F,char nomf[30]){
   ouvrir(&F,"PERSONNEL-ANP_DZ.dat","rb");
   if( F == NULL ){
      //printf("! le fichier PERSONNEL-ANP_DZ.dat n'existe pas vous devez le creer !");
       return false;

  }else {
    // printf("le fichier PERSONNEL-ANP_DZ.dat existe deja");
      return true;
  }
}







// modules supplementaires :-----------------------------------------------------------------------------------------------------------

enum //les code numerique des touches du clavier
{
    ENTRER = 13,
    ALPHA_a = 97,
    ALPHA_z = 122,
    ALPHA_A = 65,
    ALPHA_Z = 90,
    KEY_0 = 48,
    KEY_9 = 57,
    BACK_SPACE = 8,
    SPACE_BAR = 32
};

int getkey(void)
{
    int ch;
    clearkeybuf(); //on initialise le buffer
    ch = getch();  //lit immediatement le ch entr�
    return ch;
}

void getNumber(char *num)
{
    int x, y, i = 0, c;
    x = wherex();
    y = wherey();
    do
    {
        gotoxy(x + i, y);
        c = getkey();                             //on enregistre le caractere dans le buffer
        if ((c >= KEY_0 && c <= KEY_9) && i < 10) // (code asci des nombre 1..9)
        {
            num[i] = c;      //on affecte le chiffre a num
            printf("%c", c); // on affiche le caractere
            i++;             //on passe au prochain c
        }
        else if ((c == BACK_SPACE) && (i > 0)) // on supprime un caractere
        {
            gotoxy(x, y);
            i--;
            num[i] = '\0';     //on arrive a la fin de num si on ajoute rien
            printf("%s", num); //on affiche le num sans le caractere supprim�
            gotoxy(x + i, y);
            printf(" "); // on affiche un vide
        }
        else if (c != ENTRER)
            Beep(1000, 250);          //si le caractere n'est pas un chiffre ni un (.) ni un espace ni une suppression
    } while (c != ENTRER || i == 0); // i==0 pour que le num ne soit pas vide
    num[i] = '\0';                   //la fin de num
    gotoxy(1, y + 1);                //on saute un ligne
}


void scanf2(long long *choix)
{
    long long tmp;
    do
    {
        char num[10]; // l'initialisation du num � vide
        sprintf(num, "%s", "");
        int x = wherex();
        int y = wherey();
        getNumber(num);   //on lit le num
        tmp = atoll(num); // chaine vers un un r�el
        if (tmp == 0)     // on verifie si num est un entier
        {
            gotoxy(x, y);
            printf("          ");
            gotoxy(x, y);
        }
    } while (tmp == 0); // on sort du boucle jusqu'a num est un entier positif strictement
    *choix = tmp;
}

