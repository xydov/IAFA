package banque;

public class Compte {
    private float solde;

    public Compte() {
        this.solde = 0;
    }

    public float getSolde() {
        return solde;
    }

    public void depot(float valeur)
    {
        solde += valeur;
    }

    public void retrait(float valeur)
    {
        solde -= valeur;
    }

    public void afficherSolde() {
        System.out.println("Le solde est de: " + this.solde);
    }

    /**
     * Permet de virer de l'argent vers le compte destinataire
     * @param valeur
     *          Valeur du virement
     * @param destinataire
     *          Compte destinataire
     */
    public void virer(float valeur, Compte destinataire) {

        destinataire.depot(valeur);
        retrait(valeur);

    }
}
