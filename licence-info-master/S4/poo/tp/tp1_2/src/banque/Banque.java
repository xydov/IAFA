package banque;

public class Banque {

    private int nbClients;
    private Client clients[];

    public Banque() {
        this.nbClients = 0;
        this.clients = new Client[100];
    }

    public int ajouterClient(String nomClient, Date date) {
        clients[nbClients] = new Client(nomClient, date);
        nbClients ++;
        return nbClients;
    }

    public Client getClients(int nClient) {
        return clients[nClient];
    }

    public void afficherBilan() {
        for (int i = 0; i < nbClients; i++) {
            clients[i].afficherBilan();
        }
    }
}
