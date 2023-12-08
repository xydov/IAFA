import banque.*;

public class Main {
    public static void main(String[] args) {
        Date dt = new Date(28, 01, 2020);
        System.out.println(dt.toString());

        Compte c = new Compte();
        c.depot(20);
        c.afficherSolde();
    }
}
