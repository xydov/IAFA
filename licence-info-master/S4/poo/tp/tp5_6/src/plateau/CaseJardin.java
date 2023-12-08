package plateau;

import jeuDeLoie.Oie;

public class CaseJardin extends Case {


    public CaseJardin(int numCase) {
        super(numCase);
    }

    /**
     * Surcharge de l'opérateur arrivee permettant de renvoyer 'null' à l'arrivée  sur la case d'un oie
     * @param oie l'oie qui arrive sur la case
     * @return null
     */
    @java.lang.Override
    protected Case arrivee(Oie oie) {
        oie.ajouterMessage(" arrive au jardin et gagne!");
        return null;
    }
}
