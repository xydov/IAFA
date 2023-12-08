package jeuDeLoie;

import java.util.Random;

public class De {

    private Random r = new Random(System.currentTimeMillis());

    public int lancer() {
        return r.nextInt(12) + 1;
    }
}
