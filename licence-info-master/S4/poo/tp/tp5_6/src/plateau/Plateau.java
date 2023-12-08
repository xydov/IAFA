package plateau;

public class Plateau {
    private final int NB_CASES = 63;
    private Case[]cases = new Case[NB_CASES];

    /**
     * Initialise le nombre de cases a 63 et boucle
     * sur chaque cases pour lui attribuer un numéro
     *
     */
    public Plateau() {

        for (int i = 0; i < NB_CASES; i++) {
            cases[i] = new Case(i + 1);
        }
        initialisationCasesSpecifique();
    }

    /**
     * On veut la cases x, à l'indice x - 1 dans le tableau de Case
     * @param numCase
     * @return la case demandée
     */
    public Case donnerCase(int numCase) {
        return cases[numCase - 1];
    }

    /**
     * Renvoie la premiere case du plateau
     * @return cases[0]
     */
    public Case caseDebutPartie() {
        return cases[0];
    }

    /**
     * Redefinie les cases spéciales
     */
    private void initialisationCasesSpecifique() {

        // cases redirection
        cases[5] = new CaseRedirection(6);
        cases[41] = new CaseRedirection(42);
        cases[57] = new CaseRedirection(58);

        // case jardin
        cases[NB_CASES - 1] = new CaseJardin(NB_CASES);

        // cases fastes
        for (int i = 9; i < 63; i += 9) {
            cases[i - 1] = new CaseFaste(i);
        }

        // case hotel
        cases[18] = new CaseHotel(19);

        // case piege
        cases[30] = new CasePiege(31, "puits");
        cases[51] = new CasePiege(52, "prison");
    }
}
