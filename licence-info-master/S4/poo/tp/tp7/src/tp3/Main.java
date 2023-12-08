package tp3;

import tp3.serveur.Asteroide325Server;
import tp3.sujet.PetitPrince;

public class Main {
    public static void main(String[] args) {

        PetitPrince jean = new PetitPrince("jean");
        jean.run();
        PetitPrince alfredo = new PetitPrince("alfredo");
        alfredo.run();
    }
}
