package humain;

public class Commercant extends Humain {



    public Commercant(String nom, int argent) {

        super(nom, argent, "thé");
    }

    public int seFaireExtorquer() {
        int argent = getArgent();
        perdreArgent(argent);
        parler("J’ai tout perdu! Le monde est trop injuste...");
        return argent;
    }


    public void recevoir(int a) {
        ajouterArgent(a);
        parler("Je te remercie généreux donateur!");
    }
}
