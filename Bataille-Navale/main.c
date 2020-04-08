/**
 * \project Bataille Navale
 * \author Yann Fanha
 * \date 04.03.2020
 * \version 0.1
 * \desciption Jeu de la bataille navale qui s'ouvre dans le terminal de commande
 * *********************************************************************************************************************
 * \version 1.0
 * \description Rejout des fonctions suivantes; Authentification en tant que joueur, grille aléatoire dans des fichiers externes, affichage des scores précédents
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
#define NUMERO_GRILLE_MAX 4 //Correspond on numero de la grille max dans le tableau (donc il y a 5 grille en tout)
#define PREMIERE_CORDONNEE_GRILLE 2
#define LONGEUR_MAX_LIGNE 50
#define LONG_MAX_NOM_FICHIER 100
#define NOM_FICHIER_GRILLE {{"DataBase\\Grille\\grille1.txt"},{"DataBase\\Grille\\grille2.txt"},{"DataBase\\Grille\\grille3.txt"},{"DataBase\\Grille\\grille4.txt"},{"DataBase\\Grille\\grille5.txt"}}
#define MAX 15

typedef struct { ;
    char x;
    int y;
} coordonnee; //Structure pour les coordonnnées horzi. et verti.

typedef struct { ;
    int h;
    int min;
    int sec;
    int day;
    int mois;
    int an;
} date; //Structure pour obtenir l'heure actuelle et la date

char grilleAttaque[SIZE_COLUMN][SIZE_ROW];
char pseudo[SIZE_MAX_PSEUDO] = "0"; //(Car je ne trouvais pas comment return une chaîne de caractère)
bool dejaEnregistrer = false; //Dire si oui ou non on est déjà enregistrer



/**
 * \author Yann Fanha
 * \date 06.03.2020
 * \description Afficher le titre
 */
void afficherTitre() {
    system("cls");
    printf("/---------------Bataille Navale---------------/\n\n");
}

/**
 * \author Yann Fanha
 * \date 08.04.2020
 * \description Récuperer la date et l'heure actuelle
 * @return date
 */
date heureActuelle() {
    date date;
    time_t now;

    time(&now);

    struct tm *local = localtime(&now);
    date.h = local->tm_hour;
    date.min = local->tm_min;
    date.sec = local->tm_sec;
    date.day = local->tm_mday;
    date.mois = local->tm_mon + 1;
    date.an = local->tm_year + 1900;


    return date;
}

/**
 * \author Yann Fanha
 * \date 06.04.2020
 * \description vider la grille d'attaquer des bateaux
 */
void remettreGrilleZero() {
    for (int numeroLigne = 0; numeroLigne < SIZE_COLUMN; numeroLigne++) {
        for (int numeroColonne = 0; numeroColonne < SIZE_ROW; numeroColonne++) {
            grilleAttaque[numeroLigne][numeroColonne] = ' ';
        }
    }
}

/**
 * \author Yann Fanha
 * \date 29.03.2020
 * \description Choisir un fichier aléatoire qui contient les coordonnées des grilles
 */
void grilleAleatoire() {
    int numeroDeGrille;
    int character;
    char ligne[LONGEUR_MAX_LIGNE];
    char numeroBateau = 0;
    char grille[NUMERO_GRILLE_MAX + 1][LONG_MAX_NOM_FICHIER] = NOM_FICHIER_GRILLE;

    coordonnee coordonneeXY = {0, 0};
    date date;

    //Ouverture du fichier des faits
    FILE *fichierLogs = fopen("DataBase\\logs.txt", "a");

    //remet la grille a zero
    remettreGrilleZero();

    //Rentrer l'événement dans l'historique
    date = heureActuelle();
    fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Remise de la grille d'attaque a zéro.\n", date.day, date.mois,
            date.an, date.h, date.min, date.sec);


    srand(time(NULL));
    numeroDeGrille = rand() % NUMERO_GRILLE_MAX + 1;

    //ouverture du fichier de la grille
    FILE *fichierGrille = fopen(grille[numeroDeGrille], "r");

    //Rentrer l'événement dans l'historique
    date = heureActuelle();
    fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Ouverture du fichier de la grille choisie aléatoirement.\n",
            date.day, date.mois, date.an, date.h, date.min, date.sec);


    if (fichierGrille != NULL) {

        printf("%s\n", grille[numeroDeGrille]);

        do {
            character = fgetc(fichierGrille);
            fgets(ligne, sizeof(ligne), fichierGrille);

            numeroBateau = ligne[0];

            for (int i = PREMIERE_CORDONNEE_GRILLE; i <= MAX; i++) {
                if (isdigit(ligne[i])) {
                    coordonneeXY.y = ligne[i] - '0';
                    grilleAttaque[coordonneeXY.y][coordonneeXY.x] = numeroBateau;

                    //Rentrer l'événement dans l'historique
                    date = heureActuelle();
                    fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Chargement des coordonnées du bateaux N°%d.\n",
                            date.day, date.mois, date.an, date.h, date.min, date.sec, numeroBateau);

                } else if (isalpha(ligne[i])) {
                    coordonneeXY.x = ligne[i];
                    coordonneeXY.x = toupper(coordonneeXY.x);
                    coordonneeXY.x -= 'A';
                }
            }
        } while (character != EOF);

        //Rentrer l'événement dans l'historique
        date = heureActuelle();
        fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Fin de chargement de la grille N°%d.\n", date.day, date.mois,
                date.an, date.h, date.min, date.sec, numeroDeGrille + 1);

    } else {
        grilleAleatoire();
    }


    fclose(fichierGrille);
    fclose(fichierLogs);
    system("pause");
    system("cls");
}

/**
 * \author Yann Fanha
 * \date 25.03.2020
 * \description Inscrire le pseudo ainsi que le nombre de louper dans le fichier qui sert de base de données
 */
void inscrireLeScore(int louper) {
    date date;

    //Ouverture du fichier des scores
    FILE *fichierScore = fopen("DataBase\\score.txt", "a");

    //Ouvertures des fichier des faits
    FILE *fichierLogs = fopen("DataBase\\logs.txt", "a");

    //Inscrire le score dans le fichier
    fprintf(fichierScore, "%s %20d\n", pseudo, louper);

    //Rentrer l'événement dans l'historique
    date = heureActuelle();
    fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Inscription du scores dans le fichier.\n", date.day, date.mois,
            date.an, date.h, date.min, date.sec);


    fclose(fichierScore);
    fclose(fichierLogs);
}

/**
 * \author Yann Fanha
 * \date 23.03.2020
 * \description Afficher les scores qui sont enregistrer dans le fichier qui sert de base de données
 */
void afficherLesScores() {
    int character;
    date date;

    //Ouverture du fichier des scores
    FILE *fichierScore = fopen("DataBase\\score.txt", "r");

    //Ouverture du fichier des faits
    FILE *fichierLogs = fopen("DataBase\\logs.txt", "a");

    if (fichierScore != NULL) {

        //Rentrer l'événement dans l'historique
        date = heureActuelle();
        fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Ouverture du fichier des scores.\n", date.day, date.mois,
                date.an, date.h, date.min, date.sec);

        afficherTitre();

        do {
            character = fgetc(fichierScore);

            printf("%c", character);
        } while (character != EOF);

        //Rentrer l'événement dans l'historique
        date = heureActuelle();
        fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Affichage des scores précédents.\n", date.day, date.mois,
                date.an, date.h, date.min, date.sec);

        fclose(fichierScore);

    } else {
        printf("Ce service n'est actuellement pas disponible. Envoyez un mail à l'adresse Yann.FANHA-DIAS@cpnv.ch pour obtenir de l'aide.\n");

        //Rentrer l'événement dans l'historique
        date = heureActuelle();
        fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Echec de l'ouverture du fichier des scores.\n", date.day,
                date.mois, date.an, date.h, date.min, date.sec);
    }

    fclose(fichierLogs);
    printf("\n\n");
    system("pause");
}

/**
 * \author Yann Fanha
 * \date 21.03.2020
 * \description Demande du pseudo du joueur
 */
void authentification() {
    int changePseudo;
    date date;
    FILE *fichierLogs = fopen("DataBase\\logs.txt", "a");

    if (dejaEnregistrer == false) {
        printf("Entrez votre nom : ");
        fflush(stdin);
        gets(pseudo);
        dejaEnregistrer = true;

        //Rentrer l'événement dans l'historique
        date = heureActuelle();
        fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Enregistrement sous le nom de : %s.\n", date.day, date.mois,
                date.an, date.h, date.min, date.sec, pseudo);
    } else {
        printf("Vous êtes déjà enregistrer sous le pseudo de %s. Voulez-vous changer de pseudo ? (oui=1 / non=0)",
               pseudo);
        scanf("%d", &changePseudo);

        if (changePseudo == 1) {
            dejaEnregistrer = false;
            authentification();

            //Rentrer l'événement dans l'historique
            date = heureActuelle();
            fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Demande de changement de pseudo.\n", date.day, date.mois,
                    date.an, date.h, date.min, date.sec);
        }
    }

    fclose(fichierLogs);
}

/**
 * \author Yann Fanha
 * \16.03.2020
 * \description Fonction qui permet de demander la valeur de la coordonnée veritcal
 * @param teteDeGrille[SIZE_ROW] grilleDeShoot[SIZE_COLUMN][SIZE_ROW]
 */
void afficherGrille(char teteDeGrille[SIZE_ROW], char grilleDeShoot[SIZE_COLUMN][SIZE_ROW]) {

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
int concat(int nombre1, int nombre2) {

    char s1[20];
    char s2[20];

    // convertir les deux chiffres en chaine
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
coordonnee demandeCoordonnee() {
    coordonnee coordonneeXY = {0, 0};
    date date;
    char coordonnee[TAILLE_MAX_COORDONNEE] = "\0";

    //ouverture du fichier des faits
    FILE *fichierLogs = fopen("DataBase\\logs.txt", "a");

    do {
        int n1 = -20;
        int n2 = -20;

        printf("\nCoordonnées :");
        scanf("%s", coordonnee);

        //Rentrer l'événement dans l'historique
        date = heureActuelle();
        fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d L'utilisateur tire sur la case %s.\n", date.day, date.mois,
                date.an, date.h, date.min, date.sec, coordonnee);

        for (int i = 0; i < TAILLE_MAX_COORDONNEE; ++i) {
            if (isdigit(coordonnee[i])) {
                if (n1 == -20) {
                    n1 = coordonnee[i] - '0';
                } else {
                    n2 = coordonnee[i] - '0';
                }

            } else if (isalpha(coordonnee[i])) {
                coordonneeXY.x = coordonnee[i];
            }
        }

        if (n2 == -20) {
            coordonneeXY.y = n1 - 1;
        } else {
            coordonneeXY.y = concat(n1, n2) - 1;
        }

        //convertir la lettre rentrée en majuscule
        coordonneeXY.x = toupper(coordonneeXY.x);


    } while (coordonneeXY.y > 9 || coordonneeXY.y < 0 || coordonneeXY.x > 'J');

    coordonneeXY.x -= 'A'; //Prendre la bonne valeur décimal

    fclose(fichierLogs);
    return coordonneeXY;
}

/**
 * \author Yann Fanha
 * \date 06.03.2020
 * \description fonction qui permet de jouer
 */
void jouer() {
    char teteDeGrille[SIZE_ROW] = TETE_GRILLE; //POUR L'AFFICHE DE LA TETE DE TITRE
    char grilleDeShoot[SIZE_COLUMN][SIZE_ROW] = GRILLE_SHOOT; //Grille que l'utilisateur pourra voir pour savoir ou tirer
    int nbrtirs = 0;
    int louper = 0;

    //Déclaration des variables pour savoir si un bateau a été coulé
    int bateau5 = 5, //Bateau qui occupe 5 place
    bateau4 = 4, //Bateau qui occupe 4 place
    bateau3 = 3, //Bateau qui occupe 3 place
    bateau2 = 2, //Bateau qui occupe 2 place
    bateau1 = 3; //Bateau qui occupe 3 place

    coordonnee coordonneeXY = {-1, -1};
    date date;

    //Prendre un grille aleatoire
    grilleAleatoire();

    FILE *fichierLogs = fopen("DataBase\\logs.txt", "a");
    //Rentrer l'événement dans l'historique
    date = heureActuelle();
    fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Lancement d'une partie.\n", date.day, date.mois, date.an, date.h,
            date.min, date.sec);

    do {
        system("cls");

        if (grilleDeShoot[coordonneeXY.y][coordonneeXY.x] == 'T' ||
            grilleDeShoot[coordonneeXY.y][coordonneeXY.x] == 'X') {
            printf("Vous avez déjà tiré sur cette case\n");
        } else {

            switch (grilleAttaque[coordonneeXY.y][coordonneeXY.x]) {
                case '1':
                    printf("\nUn bateau a été touché.\n");
                    grilleDeShoot[coordonneeXY.y][coordonneeXY.x] = 'T';
                    bateau1 -= 1;
                    if (bateau1 == 0) {
                        printf("Un bateau a été coulé\n");
                    }
                    break;

                case '2':
                    printf("\nUn bateau a été touché.\n");
                    grilleDeShoot[coordonneeXY.y][coordonneeXY.x] = 'T';
                    bateau2 -= 1;
                    if (bateau2 == 0) {
                        printf("Un bateau a été coulé\n");
                    }
                    break;

                case '3':
                    printf("\nUn bateau a été touché.\n");
                    grilleDeShoot[coordonneeXY.y][coordonneeXY.x] = 'T';
                    bateau3 -= 1;
                    if (bateau3 == 0) {
                        printf("Un bateau a été coulé\n");
                    }
                    break;

                case '4':
                    printf("\nUn bateau a été touché.\n");
                    grilleDeShoot[coordonneeXY.y][coordonneeXY.x] = 'T';
                    bateau4 -= 1;
                    if (bateau4 == 0) {
                        printf("Un bateau a été coulé\n");
                    }
                    break;

                case '5':
                    printf("\nUn bateau a été touché.\n");
                    grilleDeShoot[coordonneeXY.y][coordonneeXY.x] = 'T';
                    bateau5 -= 1;
                    if (bateau5 == 0) {
                        printf("Un bateau a été coulé\n");
                    }
                    break;

                default:
                    if (nbrtirs > 0) {
                        printf("\nAucun bateau n'a été touché.\n");
                        grilleDeShoot[coordonneeXY.y][coordonneeXY.x] = 'X';
                        louper += 1;
                    }
                    break;
            } //Fin du switch
        } //Fin du if

        //afficher la grille
        afficherGrille(teteDeGrille, grilleDeShoot);


        //Demander les coordonnées de shoot si le jeu n'est pas fini
        if (bateau2 != 0 || bateau3 != 0 || bateau4 != 0 || bateau5 != 0 || bateau1 != 0) {
            printf("\n\n");
            printf("/--Coordonnées de shoot--/");
            coordonneeXY = demandeCoordonnee();
            fflush(stdin);
        }


        nbrtirs++;
        printf("\n");
        printf("\n");

    } while (bateau2 != 0 || bateau3 != 0 || bateau4 != 0 || bateau5 != 0 || bateau1 != 0);

    //Rentrer l'événement dans l'historique
    date = heureActuelle();
    fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Fin de la partie.\n", date.day, date.mois, date.an, date.h,
            date.min, date.sec);

    inscrireLeScore(louper);

    fclose(fichierLogs);
    system("pause");
}

/**
 * \author Yann Fanha
 * \date 06.03.2020
 * \description Affiche l'aide du jeu
 */
void aide() {
    int aide;
    date date = heureActuelle();

    //Ouverture du fichier de l'aide
    FILE *fichierAide = fopen("DataBase\\aide.txt", "r");

    //ouverture du fichier des faits important
    FILE *fichierLogs = fopen("DataBase\\logs.txt", "a");

    if (fichierAide != NULL) { //Si le fichier s'ouvre

        //Rentrer l'événement dans l'historique
        fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Ouverture du fichier de l'aide.\n", date.day, date.mois,
                date.an, date.h, date.min, date.sec);

        afficherTitre();

        do {
            aide = fgetc(fichierAide);

            printf("%c", aide);
        } while (aide != EOF); //EOF == End Of File

        fclose(fichierAide);

        //Rentrer l'événement dans l'historique
        fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Affichage de l'aide.\n", date.day, date.mois, date.an, date.h,
                date.min, date.sec);

    } else {

        //Rentrer l'événement dans l'historique
        fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Echec de l'ouverture du fichier de l'aide.\n", date.day,
                date.mois, date.an, date.h, date.min, date.sec);

        printf("L'aide n'est actuellement pas disponible. Envoyez un mail à l'adresse Yann.FANHA-DIAS@cpnv.ch pour obtenir de l'aide.");
    }


    printf("\n\n");
    system("Pause");

    //Rentrer l'événement dans l'historique
    fprintf(fichierLogs, "%02d/%02d/%d %02d:%02d:%02d Fermeture de l'aide.\n", date.day, date.mois, date.an, date.h,
            date.min, date.sec);

    fclose(fichierLogs);
    system("cls");
}

/**
 * \author Yann Fanha
 * \date 06.03.2020
 * \description Affiche le menu et récupere le choix de l'user
 * @param choix
 */
void menu() {
    int choix = 0;
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
    switch (choix) {
        case 1:
            if (dejaEnregistrer == false) {
                authentification();
            }
            jouer();
            break;

        case 2:
            authentification();
            break;

        case 3:
            afficherLesScores();
            break;

        case 4:
            aide();
            break;

        case 5:
            exit(0);
            break;

        default:
            system("cls");
            menu(choix);
            break;
    }
}

int main() {
    SetConsoleOutputCP(65001);//Accents

    //Appeller le menu
    system("cls");
    menu();

    return main();
}