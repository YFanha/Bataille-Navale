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
#include <ctype.h>
#include <stdbool.h>
#pragma execution_character_set("utf-8") //Accents

#define SIZE_MAX_PSEUDO 30
#define SIZE_ROW 10 //Taille MAX des lignes du grille
#define SIZE_COLUMN 10 //Taille MAX des colunnes de la grille
#define TETE_GRILLE  {'A','B','C','D','E','F','G','H','I','J'}
#define GRILLE_SHOOT {{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'}}
#define TAILLE_MAX_COORDONNEE 3
#define NUMERO_GRILLE_MIN 0
#define NUMERO_GRILLE_MAX 4 //Correspond on numero de la grille max dans le tableau (donc il y a 5 grille en tout)R
#define PREMIERE_CORDONNEE_GRILLE 2
#define LONGEUR_MAX_LIGNE 50
#define LONG_MAX_NOM_FICHIER 100
#define NOM_FICHIER_GRILLE {{"DataBase\\Grille\\grille1.txt"},{"DataBase\\Grille\\grille2.txt"},{"DataBase\\Grille\\grille3.txt"},{"DataBase\\Grille\\grille4.txt"},{"DataBase\\Grille\\grille5.txt"}}
#define MAX 15

typedef struct {;
    char x;
    int y;
}coordonnee;

char grilleAttaque[SIZE_COLUMN][SIZE_ROW];
char pseudo[SIZE_MAX_PSEUDO] = "0"; //(Car je ne trouvais pas comment return une chaîne de caractère)
bool quit = false; //Variable pour dire si oui ou non on sort du programme (1=OUI, 0=NON)
bool dejaEnregistrer = false; //Dire si oui ou non on est déjà enregistrer


/**
 * \author Yann Fanha
 * \date 06.03.2020
 * \description Afficher le titre
 */
void afficherTitre(){
    system("cls");
    printf("/---------------Bataille Navale---------------/\n\n");
}

void remettreGrilleZero(){
    for (int j = 0; j < SIZE_COLUMN; j++){
        for (int  t = 0;  t < SIZE_ROW; t++) {
            grilleAttaque[j][t] = ' ';
        }
    }
}

void grilleAleatoire(){
    int numeroDeGrille;
    int character = -1;
    char ligne[LONGEUR_MAX_LIGNE];
    char numeroBateau =0;
    char grille[NUMERO_GRILLE_MAX+1][LONG_MAX_NOM_FICHIER] = NOM_FICHIER_GRILLE;
    char grilleVide[SIZE_COLUMN][SIZE_ROW] = GRILLE_SHOOT;
    coordonnee coordonneeXY = {0,0};


    //remet la grille a zero
    remettreGrilleZero();

    FILE*fichierGrille = NULL;
    srand( time(NULL));
    numeroDeGrille = rand() % NUMERO_GRILLE_MAX + 1;
    fichierGrille = fopen(grille[numeroDeGrille], "r");



    if(fichierGrille != NULL){
        printf("%s\n", grille[numeroDeGrille]);
       do{
            character = fgetc(fichierGrille);
            fgets(ligne, sizeof(ligne), fichierGrille);

            numeroBateau = ligne[0];


            printf("Bateau No %c\n", numeroBateau);

            for (int i = PREMIERE_CORDONNEE_GRILLE; i <= MAX; i++) {
                if (isdigit(ligne[i])) {
                    coordonneeXY.y = ligne[i] - '0';
                    grilleAttaque[coordonneeXY.y][coordonneeXY.x] = numeroBateau;
                } else if (isalpha(ligne[i])) {
                    coordonneeXY.x = ligne[i];
                    coordonneeXY.x = toupper(coordonneeXY.x);
                    coordonneeXY.x -= 'A';
                }
            }
        }while(character != EOF);

    } else {
        grilleAleatoire();
    }


    fclose(fichierGrille);
    system("pause");
    system("cls");
}

/**
 * \author Yann Fanha
 * \date 25.03.2020
 * \description Inscrire le pseudo ainsi que le nombre de louper dans le fichier qui sert de base de données
 */
void inscrireLeScore(int louper){
    FILE*fichierScore = NULL;
    char characater;

    fichierScore = fopen("DataBase\\score.txt", "a");

    fprintf(fichierScore,"%s %20d\n", pseudo, louper);

    fclose(fichierScore);
}

/**
 * \author Yann Fanha
 * \date 23.03.2020
 * \description Afficher les scores qui sont enregistrer dans le fichier qui sert de base de données
 */
void afficherLesScores(){
    FILE*fichierScore = NULL;
    int character;

    fichierScore = fopen("DataBase\\score.txt", "r");

    if(fichierScore != NULL) {
        afficherTitre();
        do {
            character = fgetc(fichierScore);

            printf("%c", character);
        } while (character != EOF);

        fclose(fichierScore);
    } else {
        printf("Ce service n'est actuellement pas disponible. Envoyez un mail à l'adresse Yann.FANHA-DIAS@cpnv.ch pour obtenir de l'aide.\n");
    }

    printf("\n\n");
    system("pause");
}

/**
 * \author Yann Fanha
 * \date 21.03.2020
 * \description Demande du pseudo du joueur
 */
void authentification(){
    int changePseudo;

    if((void *) dejaEnregistrer == NULL){
        printf("Entrez votre nom : ");
        gets(pseudo);
        fflush(stdin);
        dejaEnregistrer = true;
    } else {
        printf("Vous êtes déjà enregistrer sous le pseudo de %s. Voulez-vous changer de pseudo ? (oui=1 / non=0)", pseudo);
        scanf("%d", &changePseudo);

        if(changePseudo == 1) {
            dejaEnregistrer = true;
            authentification();
        }
    }
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
 * \date 27.03.2020
 * \description Fonctions qui concatène les deux entiers pour la coordonnée vertical
 * @param nombre1
 * @param nombre2
 * @return coordonneeY
 */
int concat(int nombre1, int nombre2){

    char s1[20];
    char s2[20];

    // convertir les deux entier en chaine
    sprintf(s1, "%d", nombre1);
    sprintf(s2, "%d", nombre2);

    //assembler les deux caratère
    strcat(s1, s2);

    //Transformer les deux caractère en entier
    int coordonneeY = atoi(s1);

    return coordonneeY;
}

/**
 * \author Yann Fanha
 * \16.03.2020
 * \dernière modification le 27.03.2020
 * \description Fonction qui permet de demander les coordonnées du shoot
 * @return coordonneeXY
 */
coordonnee demandeCoordonnee(){
    coordonnee coordonneeXY = {0 , 0};
    char coordonnee[TAILLE_MAX_COORDONNEE] = "\0";


    do {
        int n1 = -20;
        int n2 = -20;
        printf("\nCoordonnées :");
        scanf("%s", coordonnee);

        for (int i = 0; i < TAILLE_MAX_COORDONNEE; ++i) {
            if( isdigit(coordonnee[i]) ) {
                if (n1 == -20) {
                    n1 = coordonnee[i] - '0';
                } else {
                    n2 = coordonnee[i] - '0';
                }

            } else if ( isalpha(coordonnee[i]) ){
                coordonneeXY.x = coordonnee[i];
            }
        }

        if(n2 == -20) {
            coordonneeXY.y = n1 -1;
        } else {
            coordonneeXY.y = concat(n1, n2) - 1;
        }

        //convertir la lettre rentrée en majuscule
        coordonneeXY.x = toupper(coordonneeXY.x);


    }while( coordonneeXY.y > 9 || coordonneeXY.y < 0 || coordonneeXY.x > 'J');

    coordonneeXY.x -= 'A'; //Prendre la bonne valeur décimal

    return coordonneeXY;
}

/**
 * \author Yann Fanha
 * \date 06.03.2020
 * \description fonction qui permet de jouer
 */
void jouer(){
    char teteDeGrille[SIZE_ROW]  = TETE_GRILLE; //POUR L'AFFICHE DE LA TETE DE TITRE
    char grilleDeShoot[SIZE_COLUMN][SIZE_ROW] = GRILLE_SHOOT; //Grille que l'utilisateur pourra voir pour savoir ou tirer

    //Prendre un grille aleatoire
    grilleAleatoire();

    //Déclaration des variable pour savoir si un bateau a été coulé
    int bateau5 = 5, //Bateau qui occupe 5 place
        bateau4 = 4, //Bateau qui occupe 4 place
        bateau3 = 3, //Bateau qui occupe 3 place
        bateau2 = 2, //Bateau qui occupe 2 place
        bateau1 = 3; //Bateau qui occupe 3 place

        int nbrtirs = 0;
        int louper = 0;
        int nbrBateauCouler = 0;
        coordonnee coordonneeXY={0,0};


    do {

        system("cls");

        if(grilleDeShoot[coordonneeXY.y][coordonneeXY.x] == 'T' || grilleDeShoot[coordonneeXY.y][coordonneeXY.x] == 'X'){
                printf("Vous avez déjà tiré sur cette case\n");
            } else {
                switch (grilleAttaque[coordonneeXY.y][coordonneeXY.x]){
                    case '1':
                        printf("\nUn bateau a été touché.\n");
                        grilleDeShoot[coordonneeXY.y][coordonneeXY.x] = 'T';
                        bateau1 -= 1;
                        if(bateau1 == 0){
                            printf("Un bateau a été coulé\n");
                        }
                        break;

                    case '2':
                        printf("\nUn bateau a été touché.\n");
                        grilleDeShoot[coordonneeXY.y][coordonneeXY.x] = 'T';
                        bateau2 -= 1;
                        if(bateau2 == 0){
                            printf("Un bateau a été coulé\n");
                        }
                        break;

                    case '3':
                        printf("\nUn bateau a été touché.\n");
                        grilleDeShoot[coordonneeXY.y][coordonneeXY.x] = 'T';
                        bateau3 -= 1;
                        if(bateau3 == 0){
                            printf("Un bateau a été coulé\n");
                        }
                        break;

                    case '4':
                        printf("\nUn bateau a été touché.\n");
                        grilleDeShoot[coordonneeXY.y][coordonneeXY.x] = 'T';
                        bateau4 -= 1;
                        if(bateau4 == 0){
                            printf("Un bateau a été coulé\n");
                        }
                        break;

                    case '5':
                        printf("\nUn bateau a été touché.\n");
                        grilleDeShoot[coordonneeXY.y][coordonneeXY.x] = 'T';
                        bateau5 -= 1;
                        if(bateau5 == 0){
                            printf("Un bateau a été coulé\n");
                        }
                        break;

                    default:
                        if(nbrtirs > 0) {
                            printf("\nAucun bateau n'a été touché.\n");
                            grilleDeShoot[coordonneeXY.y][coordonneeXY.x] = 'X';
                            louper += 1;
                        }
                        break;
                    }
            }

        //afficher la grille
        afficherGrille(teteDeGrille, grilleDeShoot);


        //Demander les coordonnées de shoot si le jeu n'est pas fini
        if(bateau2 != 0 || bateau3 != 0 || bateau4 != 0 || bateau5 != 0 || bateau1 != 0){
            printf("\n\n");
            printf("/--Coordonnées de shoot--/");
            coordonneeXY = demandeCoordonnee();
            fflush(stdin);
        }


        nbrtirs++;
        printf("\n");
        printf("\n");

    }while (bateau2 != 0 || bateau3 != 0 || bateau4 != 0 || bateau5 != 0 || bateau1 != 0);

    inscrireLeScore(louper);

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
        case 1:
            if((void *) dejaEnregistrer == NULL){
                authentification();
            }
            jouer();
            break;

        case 2: authentification();
            break;

        case 3: afficherLesScores();
            break;

        case 4: aide();
            break;

        case 5: quit = TRUE; //Pour définir que l'on veut bien quitter le programme
            break;

        case 6: grilleAleatoire();
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

    if((void *) quit == false){
        return main();
    } else {
        return 0;
    }
}