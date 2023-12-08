package plateau;

import jeuDeLoie.Oie;

public class CaseFaste extends Case {

    public CaseFaste(int numCase) {
        super(numCase);
    }

    @java.lang.Override
    public Case depart(Oie oie) {

        int valeurDes = oie.lancerDe();
        /* message dans la methode lancerDe()*/
        Case cArrivee = super.caseSuivante(oie, valeurDes + numCase);

        return cArrivee;
    }

    @java.lang.Override
    protected Case arrivee(Oie oie) {
        oie.ajouterMessage(" tombe sur une case faste et rejoue!\n");
        Case casePostFast = depart(oie);
        return casePostFast;
    }
}
