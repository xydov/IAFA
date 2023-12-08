package tp3.jeu;

public abstract class JeuSimple {

    private String nom;

    abstract int arbitrer(String c1, String c2);

    abstract String jouerUnTour();

    public String getNom() {
        return nom;
    }
}
