/**
 * \project Bataille Navale
 * \author Yann Fanha
 * \date 04.03.2020
 * \version 0.1 (pour le 18.03.2020)
 */

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <time.h>
#pragma execution_character_set("utf-8") //Accents

#define SIZE_ROW 10 //Taille MAX des lignes du grille
#define SIZE_COLUMN 10 //Taille MAX des colunnes de la grille
#define TETE_GRILLE  {'A','B','C','D','E','F','G','H','I','J'}
#define GRILLE_SHOOT {{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'}};
#define GRILLE_DE_JEU {{'-','-','2','2','-','-','-','5','-','-'},{'-','-','-','-','-','-','-','5','-','-'},{'-','-','-','-','-','-','-','5','-','-'},{'-','-','-','-','-','-','-','5','-','-'},{'3','3','3','-','-','-','-','5','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','4','-','-','-','-','-','-','-','-'},{'-','4','-','-','-','-','-','-','-','-'},{'-','4','-','-','-','3','3','3','-','-'},{'-','4','-','-','-','-','-','-','-','-'},};



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
 * \date 06.03.2020
 * \description fonction qui permet de jouer
 */
void jouer(){
    char teteDeGrille[SIZE_ROW]  = TETE_GRILLE;
    char grilleDeShoot[SIZE_COLUMN][SIZE_ROW] = GRILLE_SHOOT;
    char grilleAttaque[SIZE_COLUMN][SIZE_COLUMN] = GRILLE_DE_JEU;
    int coordonneeHorizon, coordonneeVertical;
    //Afficher titre
    afficherTitre();


    //Affichage de la grille
    for (int lettre = 0; lettre < SIZE_ROW; lettre++){ //Afficher l'en-tete des colonnes
        if(lettre == 0){
            printf("%8c", teteDeGrille[lettre]);
        }else{
            printf("%7c", teteDeGrille[lettre]);
        }
    }
    printf("\n");
    for (int colonne = 0; colonne < SIZE_COLUMN; colonne++ ){
        printf("%d", colonne + 1);
        for (int ligne = 0; ligne < SIZE_ROW; ligne++){
            if(colonne == 9 && ligne == 0) { //Bien aligner les tirets quand le nombre tout a gauche == 10
                printf("%6c", grilleDeShoot[colonne][ligne]);
            } else {
                printf("%7c", grilleDeShoot[colonne][ligne]);
            }
        }
        printf("\n");
    }

    printf("\n\n");
    printf("Coordonnées de shoot");
    printf("\nHorizontal : ");
    scanf("%d", &coordonneeHorizon);
    printf("\nVertical : %c", 186);
    scanf("%d", &coordonneeVertical);

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

    fichierAide = fopen("DataBase\\documentation.txt", "r"); //Ouvre le documents

    if(fichierAide != NULL){ //Si le fichier s'ouvre
        afficherTitre();
        do{
            aide = fgetc(fichierAide);

            printf("%c", aide);
        }while(aide != EOF);

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

    system("cls");

    //appeller la bonne fonction
    switch(choix){
        case 1:jouer();
            break;

        case 2: printf("Fonction pas encore disponible.");
            break;

        case 3: printf("Fonction indisponible");
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