package humain;

public class Ronin extends Humain {

    private int honneur;


    public Ronin(String nom, int argent, String boisson) {
        super(nom, argent, boisson);
        this.honneur = 1;
    }



    public void donner(int somme, Commercant c) {

        perdreArgent(somme);
        parler(java.lang.String.format("Tiens %s voilà %d sous.", c.getNom(), somme));

        c.recevoir(somme);
    }

    public void provoquer(Yakusa y) {

        if (this.honneur * 2 > y.getReputation()) {
            int aYakuza = y.perdre();
            ajouterArgent(aYakuza);
            honneur += 1;
            parler("Je t’ai eu petit yakusa!");
        } else {
            parler("Rhooo! Je suis sûr que tu as triché >:(");
            honneur -= 1;

            y.gagner();
        }

    }
}
