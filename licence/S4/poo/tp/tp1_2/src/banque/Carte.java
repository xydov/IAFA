package banque;

public class Carte {

    private int code[];
    private int erreurRestantes;
    private int numeroClient;
    private int numeroCompte;
    private Date dateDeValidite;
    private Banque banque;


    public Carte(int[] code, Banque banque, int numeroClient, int numeroCompte, Date dateDeValidite) {
        this.code = code;
        this.erreurRestantes = 3;
        this.numeroClient = numeroClient;
        this.numeroCompte = numeroCompte;
        this.dateDeValidite = dateDeValidite;
    }

    public boolean codeValide(int[] code)
    {
        if (this.erreurRestantes == 0) {
            return false;
        }
        int i = 0;
        boolean valide = true;

        while (i < 4) {
            if (code[i] != this.code[i])
            {
                valide = false;
            }
            i++;
        }
        if (!valide) {
            this.erreurRestantes --;
        }
        return valide;
    }

    void payer(Banque b, int numClient, int numCompte, float montant) {
        Compte compteDestination = b.getClients(numClient).getComptes(numCompte);
        Compte compteEmission = this.banque.getClients(this.numeroClient).getComptes(this.numeroCompte);
        compteEmission.virer(montant, compteDestination);
    }

    public Date getDateDeValidite() {
        return dateDeValidite;
    }

    public Banque getBanque() {
        return banque;
    }
}
