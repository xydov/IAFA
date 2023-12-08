package plateau;

import jeuDeLoie.Oie;

public class CaseRedirection extends Case {


    public CaseRedirection(int numCase) {
        super(numCase);
    }

    /**
     * Surchage de la methode arrivee(), permettant de modifier le fonctionnement
     * des cases d'arrivees 12, 42 et 58 qui effectuent un redirection
     * @param oie l'oie qui arrive sur la case
     * @return la case de destination aprés redirection
     */
    @java.lang.Override
    protected Case arrivee(Oie oie) {
        Case casePostRedirection = null;
        Plateau plateau = oie.getPlateau();
        switch (this.numCase) {
            // Pont: 6 -> 12
            case 6:
                casePostRedirection = plateau.donnerCase(12);
                oie.ajouterMessage(" tombe sur la case pont et va sur la case " + casePostRedirection.getNom());
                break;
            //Laby: 42 -> 30
            case 42:
                casePostRedirection = plateau.donnerCase(30);
                oie.ajouterMessage(" tombe sur la case labyrinthe et va sur la case " + casePostRedirection.getNom());
                break;
            // Mort: 58 -> 1
            case 58:
                casePostRedirection = plateau.donnerCase(1);
                oie.ajouterMessage(" tombe sur la case mort et va sur la case " + casePostRedirection.getNom());
                break;
            default:
                System.out.println("Erreur case redirection!");
        }

        return casePostRedirection;
    }
}
