package humain;

public class Humain {

    private String nom;
    private int argent;
    private String boisson;


    public Humain(String nom, int argent, String boisson) {
        this.nom = nom;
        this.argent = argent;
        this.boisson = boisson;
    }

    public void parler(String texte) {
        System.out.println(java.lang.String.format("(%s) - %s", this.nom, texte));
    }

    public void direBonjour() {
        parler(java.lang.String.format("Bonjour je m'appelle %s et j'aime boire du %s et j'ai %d sous en poche", this.nom, this.boisson, this.argent));
    }

    public void boire() {
        parler("Ahhh, un bon verre de " + this.boisson + "! GLOUPS!");
    }

    public void ajouterArgent(int somme) {
        this.argent += somme;
    }

    public void perdreArgent(int somme) {
        this.argent -= somme;
    }

    public int getArgent() {
        return argent;
    }

    public String getBoisson() {
        return boisson;
    }

    public String getNom() {
        return nom;
    }
}
