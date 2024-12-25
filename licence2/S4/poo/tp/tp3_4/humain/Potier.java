package humain;

import java.util.Random;

public class Potier extends Humain{

    private String [] poteries = new String[50];
    private int pCount;


    public Potier(String nom, int argent, String boisson) {
        super(nom, argent, boisson);
        this.pCount = 0;
    }

    public void creerUnePoterie(String nom) {
        Random r = new Random();
        int prixFabrication = r.nextInt(10) + 1;
        perdreArgent(prixFabrication);
        poteries[pCount] = nom;
        pCount ++;
    }

    public  void annoncerStock() {
        parler("REGARDER MES BELLES POTERIES !!");
        parler(java.lang.String.format("J'en ai plus que %d en stock !!", pCount));

        Random r = new Random();
        parler(java.lang.String.format("Par exemple cette magnifique pieces nommé: %s !", poteries[r.nextInt(pCount)]));
    }

    public void vendre(int n, Humain hAcheteur, int prixAchat) {
        if (n >= pCount) {
            parler("Je n'ai pas cette pièces en stock!");
            annoncerStock();
        } else {
        if (prixAchat < 15) {
            parler(java.lang.String.format("Tu te fiche de moi %s, %d sous, c'est bien trop peu!!", hAcheteur.getNom(), prixAchat));
        } else {
            parler("Marché conclu ! Tu repart avec une magnifique poterie qui se nomme " + poteries[n]);
            hAcheteur.perdreArgent(prixAchat);
            this.ajouterArgent(prixAchat);
            pCount --;
        }
        }

    }
}

