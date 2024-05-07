package humain;

public class Samourai extends Ronin {

    private String seigneur;

    public Samourai(String nom, int argent, String boisson, String seigneur) {
        super(nom, argent, boisson);
        this.seigneur = seigneur;
    }

    public void boire(String boisson) {
        parler("Ahhh, un bon verre de " + boisson + "! GLOUPS!");
    }

}

