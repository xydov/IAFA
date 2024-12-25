package humain;

public class Traitre extends Samourai{
    private int traitrise;

    public Traitre(String nom, int argent, String boisson, String seigneur) {
        super(nom, argent, boisson, seigneur);
        this.traitrise = 0;
    }

    @java.lang.Override
    public void direBonjour() {
        super.direBonjour();
        parler("Mon niveau de traitrise est de " + this.traitrise);
    }

    public void extorquer(Commercant c) {
        if (this.traitrise < 3) {
            int argentDuCommercant = c.seFaireExtorquer();
            ajouterArgent(argentDuCommercant);
            parler(java.lang.String.format("J’ai piqué le fric de %s", c.getNom()));

            this.traitrise += 1;
        } else {
            parler("Je ne peux plus extorquer qui que ce soit");
        }
    }

    public void faireLeGentil(Humain h, int somme) {
        parler("Faison ami-ami " + h.getNom());
        h.ajouterArgent(somme);
        this.perdreArgent(somme);

        somme /= 10;

        if (traitrise - somme < 0) {
            traitrise = 0;
        } else {
            traitrise -= somme;
        }
    }
}
