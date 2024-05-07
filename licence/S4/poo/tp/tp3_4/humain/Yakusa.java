package humain;

public class Yakusa extends Humain {

    private String clan;
    private int reputation;

    public Yakusa(String nom, int argent, String boisson, String clan) {
        super(nom, argent, boisson);
        this.clan = clan;
        this .reputation = 0;
    }

    @java.lang.Override
    public void direBonjour() {
        super.direBonjour();
        parler(java.lang.String.format("mon clan est le clan %s",this.clan));

    }


    public void extorquer(Commercant c) {
        int argentDuCommercant = c.seFaireExtorquer();
        this.reputation += 1;
        ajouterArgent(argentDuCommercant);
        parler(java.lang.String.format("J’ai piqué le fric de %s", c.getNom()));

    }

    public void gagner() {
        this.reputation += 1;
        parler("Victoire!! J'ai gagné mon duel !");
    }

    public int perdre() {
        int argent = getArgent();
        perdreArgent(argent);
        this.reputation -= 1;

        parler(java.lang.String.format("J’ai perdu mon duel et mes %d sous, snif...", argent));

        return argent;
    }


    public String getClan() {
        return clan;
    }

    public int getReputation() {
        return reputation;
    }
}
