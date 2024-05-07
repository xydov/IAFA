package humain;

import java.util.Random;

public class GrandMere extends Humain{

    private Humain [] memoire = new Humain [30];
    private int hCount;


    public GrandMere(String nom, int argent) {
        super(nom, argent, "tisane");
        this.hCount = 0;
    }

    public void ragoter() {

        for (int i = 0; i < hCount; i ++) {
            if(memoire[i] instanceof Traitre)
            {
                parler("Je sais que " + memoire[i].getNom() + " est un traître !");
            } else {

                parler("Je crois que " + memoire[i].getNom() + " est un " + humainHasard());
            }
        }
    }

    public void faireConnaissanceAvec(Humain h) {
        if (hCount < 30) {
            memoire[hCount] = h;
            hCount ++;
        } else {
            parler("Je connais trop d'humain");
        }
    }

    private String humainHasard() {
        Random r = new Random();
        int i = r.nextInt(5);

        switch (i) {
            case 0:
                return "Commercant";
            case 1:
                return "Ronin";
            case 2:
                return "Yakusa";
            case 3:
                return "Samourai";
            case 4:
                return "Grand-mere";
            default:
                return "Error !!";
        }
    }
}
