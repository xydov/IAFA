/* =================================================================== */
// Progrmame centralisé d'un joueur qui doit deviner la case du trésor.
// Le coup consite en une abcsisse et une ordonnée (x, y).
// Après chaque coup le résultat est affiché.
// Le programme s'arrête lorsque le joueur a trouvé le trésor.
/* =================================================================== */
/* T. Desprats, E. Lavinal - Nov. 2020 - Université Paul Sabatier */

/*
 * Version du jeu qui nécessite la bibliothèque "ncurses" :
 *     https://invisible-island.net/ncurses/
 *
 * ncurses on Ubuntu/Debian
 *   sudo apt install libncurses-dev
 * ncurses on CentOS 6.x/7.x+ and Fedora <= 21
 *   sudo yum install ncurses-devel
 * ncurses on Fedora Linux >= 22
 *   sudo dnf install ncurses-devel
 * ncurses on Mac OS X (with Homebrew https://brew.sh/)
 *   brew install ncurses
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "tresor.h"

#define N 10
#define YEL  1
#define RED  2
#define MAG  3
#define GRN  4
#define CYA  5
#define RED2 6

/* ====================================================================== */
/*         Affichage du jeu en mode texte (bibliothèque ncurses)          */
/* ====================================================================== */
void afficher_jeu(int jeu[N][N], int res, int points, int coups) {

    clear();
    move(0,0);
    attron(A_BOLD);
    printw("************ TROUVEZ LE TRESOR ! ************\n");
    attroff(A_BOLD);
    printw("    ");
    for (int i=0; i<10; i++)
        printw("  %d ", i+1);
    printw("\n    -----------------------------------------\n");
    for (int i=0; i<10; i++){
        printw("%2d  ", i+1);
        for (int j=0; j<10; j++) {
            printw("|");
            switch (jeu[i][j]) {
                case -1:
                    printw(" 0 ");
                    break;
                case 0:
                    attron(COLOR_PAIR(GRN));
                    printw(" T ");
                    attroff(COLOR_PAIR(GRN));
                    break;
                case 1:
                case 2:
                case 3:
                    attron(COLOR_PAIR(jeu[i][j]));
                    printw(" X ");
                    attroff(COLOR_PAIR(jeu[i][j]));
                    break;
            }
        }
        printw("|\n");
    }
    printw("    -----------------------------------------\n");
    attron(A_BOLD);
    printw("Pts dernier coup %d | Pts total %d | Nb coups %d\n", res, points, coups);
    attroff(A_BOLD);
    refresh();
}

/* ====================================================================== */
/*                    Fonction principale                                 */
/* ====================================================================== */
int main(int argc, char **argv) {

    int jeu[N][N];
    int x_tresor = 4, y_tresor = 5;
    int lig, col;
    int res = -1, points = 0, coups = 0;

    /* Init args */
    if (argc == 2 && strcmp(argv[1],"rand")==0) {
        srand(time(NULL));
        x_tresor = 1 + rand()%N;
        y_tresor = 1 + rand()%N;
    }

    /* Init jeu */
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            jeu[i][j] = -1;

    /* Init ncurses */
    WINDOW * mainwin;
    if ((mainwin = initscr())== NULL) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(EXIT_FAILURE);
    }
    if (has_colors() == FALSE) {
        endwin();
        fprintf(stderr, "Your terminal does not support color.\n");
        exit(EXIT_FAILURE);
    }
    start_color();
    init_pair(GRN,  COLOR_BLACK, COLOR_GREEN);
    init_pair(YEL,  COLOR_BLACK, COLOR_YELLOW);
    init_pair(RED,  COLOR_BLACK, COLOR_RED);
    init_pair(RED2, COLOR_RED,   COLOR_BLACK);
    init_pair(MAG,  COLOR_BLACK, COLOR_MAGENTA);
    init_pair(CYA,  COLOR_BLACK, COLOR_CYAN);

    /* Tentatives du joueur : stoppe quand trésor trouvé */
    do {
        afficher_jeu(jeu, res, points, coups);
        printw("\nEntrer le numéro de ligne : ");
        scanw("%d", &lig);
        printw("Entrer le numéro de colonne : ");
        scanw("%d", &col);
        refresh();

        /* Calcul résultat de la tentative du joueur */
        res = recherche_tresor(N, x_tresor, y_tresor, lig, col);

        /* Mise à jour */
        if (lig>=1 && lig<=N && col>=1 && col<=N)
            jeu[lig-1][col-1] = res;
        points += res;
        coups++;

    } while (res);

    /* Terminaison du jeu : le joueur a trouvé le tresor */
    afficher_jeu(jeu, res, points, coups);
    attron(A_BOLD);
    attron(COLOR_PAIR(RED2));
    printw("\nBRAVO : trésor trouvé en %d essai(s) avec %d point(s)"
            " au total !\n", coups, points);
    getch();
    attrset(A_NORMAL);
    delwin(mainwin);
    endwin();
    return 0;
}
