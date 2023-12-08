package tp3.sujet;

import tp3.Sujet;
import tp3.arbitrage.Joueur;
import tp3.console.Console;
import tp3.console.ConsoleJavaBoy;

public class PetitPrince implements Sujet, Joueur {

    private ConsoleJavaBoy console = new ConsoleJavaBoy(this);
    private String nom;
    private int argent;

    public PetitPrince(String nom) {
        this.nom = nom;
    }

    @java.lang.Override
    public void gagner(int argent) {
        this.argent += argent;
    }

    @java.lang.Override
    public void perdre(int argent) {
        this.argent -= argent;
    }


    @java.lang.Override
    public String getNom() {
        return this.nom;
    }

    @java.lang.Override
    public int getArgent() {
        return this.argent;
    }

    @java.lang.Override
    public void run() {
        console.parler("Bonjour je suis le petit-prince: " + this.nom);
        console.seDirigerVers(2);
        //
        // console.
    }
}
