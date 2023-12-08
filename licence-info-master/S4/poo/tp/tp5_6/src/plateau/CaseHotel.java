package plateau;

import jeuDeLoie.Oie;

public class CaseHotel extends Case {

    private int nbToursRestant;

    public CaseHotel(int numCase) {
        super(numCase);
    }

    public CaseHotel(int numCase, int nbToursRestant) {
        super(numCase);
        this.nbToursRestant = nbToursRestant;
    }

    @java.lang.Override
    public Case depart(Oie oie) {
        Case caseArrivee = null;

        if (this.nbToursRestant == 0) {
            // a effectuer ses deux nuits a l'hotel
            caseArrivee = super.depart(oie);

        } else if (this.nbToursRestant > 0){
            // il reste des nuits a passer dans l'hotel pour l'oie
            this.nbToursRestant --;
            String couleurOie = oie.getCouleur();
            oie.ajouterMessage(java.lang.String.format("L'oie %s est a l'hotel pour encore %d tour", couleurOie, this.nbToursRestant));
            caseArrivee = this;
        } else {
            // arrivée sur la case hotel
            caseArrivee = arrivee(oie);
        }
        return caseArrivee;
    }

    @java.lang.Override
    protected Case arrivee(Oie oie) {
        oie.ajouterMessage(" elle va sur la case hotel");
        Case caseHotel = new CaseHotel(this.numCase, 2);
        return caseHotel;
    }
}
