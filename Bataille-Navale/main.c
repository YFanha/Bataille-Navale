/**
 * \project Bataille Navale
 * \author Yann Fanha
 * \date 04.03.2020
 * \version 0.1 (pour le 18.03.2020)
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#pragma execution_character_set("utf-8") //Accents

#define SIZE_ROW 10 //Taille MAX des lignes du grille
#define SIZE_COLUMN 10 //Taille MAX des colunnes de la grille
#define TETE_GRILLE  {'A','B','C','D','E','F','G','H','I','J'}
#define GRILLE_SHOOT {{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'}};
#define GRILLE_DE_JEU {{'-','-','2','2','-','-','-','5','-','-'},{'-','-','-','-','-','-','-','5','-','-'},{'-','-','-','-','-','-','-','5','-','-'},{'-','-','-','-','-','-','-','5','-','-'},{'3','3','3','-','-','-','-','5','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','4','-','-','-','-','-','-','-','-'},{'-','4','-','-','-','-','-','-','-','-'},{'-','4','-','-','-','1','1','1','-','-'},{'-','4','-','-','-','-','-','-','-','-'},};
/* plage de valeur decimal pour les lettre dans UTF-
 * A = 65   a = 97
 * B = 66   b = 98
 * C = 67   c = 99
 * D = 68   d = 100
 * E = 69   e = 101
 * F = 70   f = 102
 * G = 71   g = 103
 * H = 72   h = 104
 * I = 73   i = 105
 * J = 74   j = 106
 */

int quit = 0; //Variable pour dire si oui ou non on sort du programme (1=OUI, 0=NON)


/**
 * \author Yann Fanha
 * \date 06.03.2020
 * \description Afficher le titre
 */
void afficherTitre(){
    system("cls");
    printf("/---------------Bataille Navale---------------/\n\n");
}

/**
 * \author Yann Fanha
 * \16.03.2020
 * \description Fonction qui permet de demander la valeur de la coordonnée veritcal
 * @param teteDeGrille[SIZE_ROW] grilleDeShoot[SIZE_COLUMN][SIZE_ROW]
 */
void afficherGrille(char teteDeGrille[SIZE_ROW], char grilleDeShoot[SIZE_COLUMN][SIZE_ROW]){

    //Affichage de la grille
    for (int lettre = 0; lettre < SIZE_ROW; lettre++) { //Afficher l'en-tete des colonnes
        if (lettre == 0) {
            printf("%8c", teteDeGrille[lettre]);
        } else {
            printf("%7c", teteDeGrille[lettre]);
        }
    }
    printf("\n");
    for (int colonne = 0; colonne < SIZE_COLUMN; colonne++) {
        printf("%d", colonne + 1);
        for (int ligne = 0; ligne < SIZE_ROW; ligne++) {
            if (colonne == 9 && ligne == 0) { //Bien aligner les tirets quand le nombre tout a gauche == 10
                printf("%6c", grilleDeShoot[colonne][ligne]);
            } else {
                printf("%7c", grilleDeShoot[colonne][ligne]);
            }
        }
        printf("\n");
    }
}

/**
 * \author Yann Fanha
 * \16.03.2020
 * \description Fonction qui permet de demander la valeur de la coordonnée horizontal
 * @return coordonneeHozion
 */
char coordonneeH(){
    char coordonneeHorizon = 0;
    do {
        printf("\nHorizontal (en lettre): ");
        scanf("%s", &coordonneeHorizon);

        //si la valeur est un nombre
        if (coordonneeHorizon >= 48 && coordonneeHorizon <=57){
            printf("Rentrez la coordonnée en lettre");
        }

    }while  ((coordonneeHorizon > 74 || coordonneeHorizon < 65) && (coordonneeHorizon > 106 || coordonneeHorizon < 97));

    switch (coordonneeHorizon) {
        //Si l'user met la lettre en majuscule
        case 65 :
            coordonneeHorizon = 0; //A
            break;
        case 66:
            coordonneeHorizon = 1; //B
            break;
        case 67:
            coordonneeHorizon = 2; //C
            break;
        case 68:
            coordonneeHorizon = 3; //D
            break;
        case 69:
            coordonneeHorizon = 4; //E
            break;
        case 70:
            coordonneeHorizon = 5; //F
            break;
        case 71:
            coordonneeHorizon = 6; //G
            break;
        case 72:
            coordonneeHorizon = 7; //H
            break;
        case 73:
            coordonneeHorizon = 8; //I
            break;
        case 74:
            coordonneeHorizon = 9; //J
            break;
            //Si l'user met la lettre en minuscule
        case 97:
            coordonneeHorizon = 0; //a
            break;
        case 98:
            coordonneeHorizon = 1; //b
            break;
        case 99:
            coordonneeHorizon = 2; //c
            break;
        case 100:
            coordonneeHorizon = 3; //d
            break;
        case 101:
            coordonneeHorizon = 4; //e
            break;
        case 102:
            coordonneeHorizon = 5; //f
            break;
        case 103:
            coordonneeHorizon = 6; //g
            break;
        case 104:
            coordonneeHorizon = 7; //h
            break;
        case 105:
            coordonneeHorizon = 8; //i
            break;
        case 106:
            coordonneeHorizon = 9; //j
            break;
        default:
            printf("Cette coordonnées n'existe pas");
            break;
    }
    return coordonneeHorizon;
}

/**
 * \author Yann Fanha
 * \16.03.2020
 * \description Fonction qui permet de demander la valeur de la coordonnée veritcal
 * @return coordonneeVertical
 */
int coordonneV(){
    int coordonneeVertical = 0;

    do{
        printf("\nVertical  : ");
        fflush(stdin);
        scanf("%d", &coordonneeVertical);
    }while(coordonneeVertical < 1 || coordonneeVertical > 10);

    coordonneeVertical -= 1;

    return coordonneeVertical;
}

/**
 * \author Yann Fanha
 * \date 06.03.2020
 * \description fonction qui permet de jouer
 */
void jouer(){
    char teteDeGrille[SIZE_ROW]  = TETE_GRILLE; //POUR L'AFFICHE DE LA TETE DE TITRE
    char grilleDeShoot[SIZE_COLUMN][SIZE_ROW] = GRILLE_SHOOT; //Grille que l'utilisateur pourra voir pour savoir ou tirer
    char grilleAttaque[SIZE_COLUMN][SIZE_ROW] = GRILLE_DE_JEU; //Grille qui contiendra les coordonnées des bateaux

    //Déclaration des variable pour savoir si un bateau a été coulé
    int bateau5 = 5, //Bateau qui occupe 5 place
        bateau4 = 4, //Bateau qui occupe 4 place
        bateau3 = 3, //Bateau qui occupe 3 place
        bateau2 = 2, //Bateau qui occupe 2 place
        bateau1 = 3; //Bateau qui occupe 3 place

    char coordonneeHorizon = 'k';
    int coordonneeVertical = 0, nbrtirs = -1;



    do {
        system("cls");

        nbrtirs++;

        //vérification si un bateau a été touché + affichage du bon message
        if(grilleAttaque[coordonneeVertical][coordonneeHorizon] == '2'){
            printf("\nUn bateau a été touché.");
            grilleDeShoot[coordonneeVertical][coordonneeHorizon] = 'T';

            bateau2 -= 1;
            if(bateau2 == 0){
                printf("\nun bateau a été coulé.");
            }
        } else if (grilleAttaque[coordonneeVertical][coordonneeHorizon] == '3'){
            printf("\nUn bateau a été touché.");
            grilleDeShoot[coordonneeVertical][coordonneeHorizon] = 'T';

            bateau3 -= 1;
            if(bateau3 == 0){
                printf("\nun bateau a été coulé.");
            }
        } else if (grilleAttaque[coordonneeVertical][coordonneeHorizon] == '4'){
            printf("\nUn bateau a été touché.");
            grilleDeShoot[coordonneeVertical][coordonneeHorizon] = 'T';

            bateau4 -= 1;
            if(bateau4 == 0){
                printf("\nun bateau a été coulé.");
            }
        } else if (grilleAttaque[coordonneeVertical][coordonneeHorizon] == '5'){
            printf("\nUn bateau a été touché.");
            grilleDeShoot[coordonneeVertical][coordonneeHorizon] = 'T';

            bateau5 -= 1;
            if(bateau5 == 0){
                printf("\nun bateau a été coulé.");
            }
        } else if(grilleAttaque[coordonneeVertical][coordonneeHorizon] == '1'){
            printf("\nUn bateau a été touché.");
            grilleDeShoot[coordonneeVertical][coordonneeHorizon] = 'T';

            bateau1 -= 1;
            if(bateau1 == 0){
                printf("\nun bateau a été coulé.");
            }
        } else if (nbrtirs != 0){
            printf("\nAucun bateau n'a été touché.");
            grilleDeShoot[coordonneeVertical][coordonneeHorizon] = 'X';
        } else {
            //Afficher titre
            afficherTitre();
        }

        printf("\n");

        //afficher la grille
        afficherGrille(teteDeGrille, grilleDeShoot);




        //Demander les coordonnées de shoot si le jeu n'est pas fini
        if(bateau2 != 0 || bateau3 != 0 || bateau4 != 0 || bateau5 != 0 || bateau1 != 0){
            printf("\n\n");
            printf("/--Coordonnées de shoot--/");

             coordonneeHorizon = coordonneeH();
             coordonneeVertical = coordonneV();
             fflush(stdin);
        }


        nbrtirs++;
        printf("\n");
        printf("\n");

    }while (bateau2 != 0 || bateau3 != 0 || bateau4 != 0 || bateau5 != 0 || bateau1 != 0); // pour les test des coordonéées !!A CHANGER!!
    system("pause");
}

/**
 * \author Yann Fanha
 * \date 06.03.2020
 * \description Affiche l'aide du jeu
 */
void aide(){
    FILE*fichierAide = NULL;
    int aide;

    fichierAide = fopen("DataBase\\aide.txt", "r"); //Ouvre le documents

    if(fichierAide != NULL){ //Si le fichier s'ouvre
        afficherTitre();
        do{
            aide = fgetc(fichierAide);

            printf("%c", aide);
        }while(aide != EOF); //EOF == End Of File

        fclose(fichierAide);

    } else {
        printf("L'aide n'est actuellement pas disponible. Envoyez un mail à l'adresse Yann.FANHA-DIAS@cpnv.ch pour obtenir de l'aide.");
    }
    printf("\n\n");
    system("Pause");
    system("cls");
}

/**
 * \author Yann Fanha
 * \date 06.03.2020
 * \description Affiche le menu et récupere le choix de l'user
 * @param choix
 */
void menu(int choix){
    afficherTitre();
    printf("1 - Jouer");
    printf("\n2 - S'enregistrer");
    printf("\n3 - Scores");
    printf("\n4 - Aide");
    printf("\n5 - Quitter\n->");
    scanf("%d", &choix);
    fflush(stdin);
    system("cls");

    //appeller la bonne fonction
    switch(choix){
        case 1:jouer();
            break;

        case 2: printf("Fonction pas encore disponible.\n");
                system("Pause");
                system("cls");
                menu(choix);
            break;

        case 3: printf("Fonction indisponible\n");
                system("Pause");
                system("cls");
                menu(choix);
            break;

        case 4: aide();
            break;

        case 5: quit = 1; //Pour définir que l'on veut bien quitter le programme
            break;

        default: system("cls");
                menu(choix);
                break;
    }
}


int main() {
    int choix = 0;
    SetConsoleOutputCP(65001);//Accents

    //Appeller la fonction du menu
    system("cls");
    menu(choix);


    printf("\n\n");

    if(quit == 0){
        return main();
    } else {
        return 0;
    }
}