package banque;

public class Client {

    private String nom;
    private Date date;
    private int nbComptes;
    private Compte comptes[] = new Compte[100];

    /**
     * Initialise le nom, la date de naissance du client et crée le premier compte du nouvel utilisateur
     *
     * @param nom
     * @param date
     */
    public Client(String nom, Date date) {
        this.nom = nom;
        this.date = date;
        this.nbComptes = 1;
        this.comptes[0] = new Compte();
    }

    public String getNom() {
        return nom;
    }

    public Date getDate() {
        return date;
    }

    public Compte getComptes(int numero) {
        return comptes[numero];
    }

    public void afficherBilan() {
        for (int i = 0; i < nbComptes; i++) {
            comptes[i].afficherSolde();
        }
    }

    /**
     * Calcule le solde total
     * @return le solde total
     */
    public float soldeTotal() {
        float total = 0;
        for (int i = 0; i < nbComptes; i++) {
            total += comptes[i].getSolde();
        }
        return total;
    }

    /**
     * Affiche le solde total
     */
    public void afficherSolde() {

        System.out.println("Solde total = " + soldeTotal() + "€");
    }

    /**
     * Ajoute un nouveau compte
     * @return
     */
    public int ajouterCompte() {
        comptes[nbComptes] = new Compte();
        nbComptes ++;
        return nbComptes;
    }
}
