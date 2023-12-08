package jeuDeLoie;

import plateau.Plateau;

public class JeuOie {

    private int nbOie = 0;
    private Oie[] oies;
    private Plateau plateau = new Plateau();
    private De de = new De();

    public JeuOie(int nbOieMax) {
        oies = new Oie[nbOieMax];
    }

    public void ajouterOie(String couleur) {
        if (nbOie < oies.length) {
            oies[nbOie] = new Oie(couleur, plateau, de);
            nbOie++;
        }
    }

    public void jouer() {
        boolean finPartie = false;
        boolean b_oies = nbOie > 1;
        /* au moins 2 joueurs/oies */

        int i;
        while (!finPartie && b_oies) {
            /*
            on fait jouer chaque oie par tour
             */
            i = 0;
            while (i < nbOie && !finPartie) {
                finPartie = oies[i].action();
                i ++;
            }
        }
    }

}