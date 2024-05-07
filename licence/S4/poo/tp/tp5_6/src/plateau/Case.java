package plateau;

import jeuDeLoie.Oie;

public class Case {

    protected int numCase;

    public Case(int numCase) {
        this.numCase = numCase;
    }

    /**
     * Getter, récupère le numéro de la case sous forme de string ????
     * @return n° de case
     */
    public String getNom() {
        return "numero: " + numCase;
    }

    /**
     * action à éffectuer au début du tour
     */
    public Case depart(Oie oie) {
        String couleurOie = oie.getCouleur();
        String nomCase = getNom();
        oie.ajouterMessage("L'oie " + couleurOie + " est sur la case " + nomCase);

        int valeurDes = oie.lancerDe();
        /* message dans la methode lancerDe() */
        Case cArrivee = caseSuivante(oie, valeurDes + numCase);

        return cArrivee;
    }

    /**
     * Donne les infos de la case d'arrivée
     */
    protected Case caseSuivante(Oie oie, int numCaseDestination) {
        Plateau plateau = oie.getPlateau();
        if (numCaseDestination > 63) {
            numCaseDestination = 63 - (numCaseDestination % 63);
        }
        Case caseDestination = plateau.donnerCase(numCaseDestination);
        Case caseArrivee = caseDestination.arrivee(oie);

        return caseArrivee;
    }

    /**
     * Donne les actions à effectuer lorsque l'oie tombe sur la case
     */
    protected Case arrivee(Oie oie) {
        String nomCase = getNom();
        oie.ajouterMessage(" elle va sur la case " + nomCase);
        return this;
    }
}