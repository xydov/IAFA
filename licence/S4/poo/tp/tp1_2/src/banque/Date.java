package banque;

import java.util.Calendar;

/**
 * Classe Date
 * @author Tarek Kunze
 */


public class Date {
    private int jour;
    private int mois;
    private int an;
    private int heure = 0;
    private int minute = 0;
    private int seconde = 0;



    public Date() {
        Calendar now = Calendar.getInstance();
        this.jour = now.get(Calendar.DAY_OF_MONTH);
        this.mois = now.get(Calendar.MONTH);
        this.an = now.get(Calendar.YEAR);
        this.heure = now.get(Calendar.HOUR);
        this.minute = now.get(Calendar.MINUTE);
        this.seconde = now.get(Calendar.SECOND);

    }

    /**
     * Constructeur permettant la création d'un date an initialisant le jour, le mois et l'année
     * @param jour
     *          n° du jour
     * @param mois
     *          n° du mois
     * @param an
     *          année en cours
     */
    public Date(int jour, int mois, int an) {
        this.jour = jour;
        this.mois = mois;
        this.an = an;
    }

    /**
     * Surcharge l'opérateur toString() pour renvoyer une String personnalisé
     * @return Une string de la forme  [heure:minute:seconde jour/mois/an].
     */
    @Override
    public String toString() {
        return String.format("[" + heure + ":" + minute + ":" + seconde + " " + jour + "/" + mois + "/" + an + "]");
    }

    /**
     * vérifie si la date entrée en paramètre a une 'valeur' plus élevée
     * @param d date de comparaison
     * @return True si la date en paramètre a une valeur plus élevée
     *          False sinon
     */
    public boolean posterieurA(Date d) {

        boolean isPosterieur = false;

        if (this.an < d.getAn()
        && this.mois < d.getMois()
        && this.jour < d.getJour()) {
            isPosterieur = true;
        }

        return isPosterieur;
    }

    public int getJour() {
        return jour;
    }

    public int getMois() {
        return mois;
    }

    public int getAn() {
        return an;
    }

    public int getHeure() {
        return heure;
    }

    public int getMinute() {
        return minute;
    }

    public int getSeconde() {
        return seconde;
    }
}
