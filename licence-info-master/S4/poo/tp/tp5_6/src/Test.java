import jeuDeLoie.*;

public class Test {
    public static void main(String[] args) {

        /** Test du lancer de dé

        De d = new De();
        for (int i = 0; i< 10; i++) {
            System.out.println("rand = " + d.lancer());
        }
         */
        JeuOie j = new JeuOie(3);
        j.ajouterOie("verte");
        j.ajouterOie("jaune");
        j.ajouterOie("bleu");
        j.jouer();
    }
}
