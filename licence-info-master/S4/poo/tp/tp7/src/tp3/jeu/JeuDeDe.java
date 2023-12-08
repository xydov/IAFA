package tp3.jeu;

import java.util.Random;

public class JeuDeDe extends JeuSimple {

    public void JeuDeDe() {

    }

    @java.lang.Override
    int arbitrer(String c1, String c2) {
        int c1I = Integer.parseInt(c1);
        int c2I = Integer.parseInt(c2);

        if (c1I > c2I) {
            return -1;
        } else if ( c1I < c2I) {
            return 1;
        }
        return 0;
    }

    @java.lang.Override
    String jouerUnTour() {
        // seed is the current system time
        Random r = new Random(System.currentTimeMillis());
        return String.format("%d", r.nextInt(6) + 1);
    }
}
