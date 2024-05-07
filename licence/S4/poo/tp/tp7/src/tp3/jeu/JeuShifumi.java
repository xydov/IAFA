package tp3.jeu;

import java.util.Random;

public class JeuShifumi extends JeuSimple {

    @java.lang.Override
    int arbitrer(String c1, String c2) {
        if ( (c1.equals(Shifumi.CISEAUX) && c2.equals(Shifumi.FEUILLE))
            || c1.equals(Shifumi.FEUILLE) && c2.equals(Shifumi.PIERRE)
            || c1.equals(Shifumi.PIERRE) && c2.equals(Shifumi.CISEAUX)) {
            return -1;
        } else if ((c1.equals(Shifumi.CISEAUX) && c2.equals(Shifumi.CISEAUX))
                || c1.equals(Shifumi.FEUILLE) && c2.equals(Shifumi.FEUILLE)
                || c1.equals(Shifumi.PIERRE) && c2.equals(Shifumi.PIERRE)){
            return  0;
        }
        return 1;
    }

    @java.lang.Override
    String jouerUnTour() {
        // seed is the current system time
        Random r = new Random(System.currentTimeMillis());
        return String.format("%s", Shifumi.values()[r.nextInt(3)]);
    }
}
