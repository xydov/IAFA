package banque;

public class Terminal {

    private int numClient;
    private int numCompte;
    private Banque banque;

    public Terminal(int numClient, int numCompte, Banque banque) {
        this.numClient = numClient;
        this.numCompte = numCompte;
        this.banque = banque;
    }

    public int payer(float montant, Carte carte, int[] code) {
        if (carte.codeValide(code)) {
            Banque b = carte.getBanque();
            if (genererAutorisation(carte, montant)) {
                carte.payer(this.banque, this.numClient, this.numCompte, montant);
                return 0;
            }
        } else {
            System.out.println("Code de la carte Invalide");
        }
        return 1;
    }

    private boolean genererAutorisation(Carte c, float m) {
        if (m > 1000) {
            System.out.println("Erreur, le montant est supérieur à 1000 €");
            return false;
        }
        Date now = new Date();
        if (!now.posterieurA(c.getDateDeValidite())) {
            System.out.println("Carte périmée, date de validité dépassée");
            return false;
        }
        System.out.println("OK");
        return true;
    }
}
