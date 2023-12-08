package jeuDeLoie;

import plateau.Case;
import plateau.Plateau;

public class Oie {

    private String couleur;
    private Journal journal = new Journal();
    private De de;
    private Plateau plateau;
    private Case surCase;


    public Oie(String couleur, Plateau plateau, De d) {
        this.couleur = couleur;
        this.plateau = plateau;
        this.de = d;
        this.surCase = plateau.caseDebutPartie();
    }

    /**
     * Donne la main a l'oie en début de tour
     * @return
     */
    public boolean action() {
        Case casePlateau = this.surCase.depart(this);
        surCase = casePlateau;
        journal.afficherMessage();

        return casePlateau == null;
    }


    public int lancerDe() {
        int valeurDes = de.lancer();
        ajouterMessage(" elle fait " + valeurDes);
        return valeurDes;
    }

    public void ajouterMessage(String message) {
        journal.ajouterMessage(message);
    }

    public String getCouleur() {
        return couleur;
    }

    public Plateau getPlateau() {
        return plateau;
    }
}
