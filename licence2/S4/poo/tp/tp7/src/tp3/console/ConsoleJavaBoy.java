package tp3.console;

import tp3.Sujet;
/*import tp3.jeux.JeuSimple;
 */

/**
 * 
 * @author Sebastien Leriche, leriche@irit.fr
 * Fevrier 2006 - TP L3 Concepts de Programmation
 * Cache les difficultes liees e la gestion des exceptions 
 * 
 */
public class ConsoleJavaBoy  {
	private QuasiConsole qc=null;
	private boolean echo=false;
	
	/**
	 * Constructeur, prend un sujet en parametre
	 * @param s
	 */
	public ConsoleJavaBoy(Sujet s) {
		try {
			qc=new QuasiConsole(s);
		} catch (Exception e) {System.out.println("Erreur : "+e.getMessage());}
	}
	
	/**
	 * Permet e un sujet de percevoir son environnement
	 * @return un tableau d'entiers, nuls si il n'y a aucun sujet en cette position, une reference de sujet sinon
	 */
	public int[][] regarder() {
		return qc.regarder();
	}
	
	/**
	 * Deplace ce sujet d'une case en direction du sujet dont la reference est donnee en parametre
	 * @param ref la reference d'un sujet, 0=>errance
	 */
	public void seDirigerVers(int ref) {
		qc.seDirigerVers(ref);
	}
	
	/**
	 * Envoie un message qui sera visible sur l'IHM
	 * @param s le message
	 */
	public void parler(String s) {
		if (echo) System.out.println(s);
		qc.parler(s);
	}

	/**
	 * Permet d'afficher ou non les messages envoyes via la console sur le terminal
	 * Valeur e faux par defaut, il peut etre utile pour tester de la mettre e vrai
	 * @param e vrai si on fait l'echo sur le terminal
	 */public void setEcho(boolean e) {
		echo=e;
	}
	
	/**
	 * Pour jouer au jeu passe en parametre avec un autre sujet dont on precise la reference, 
	 * @param jeu le jeu auquel on va jouer
	 * @param ref l'identifiant du joueur oppose
	 */
	/*public void jouer(JeuSimple jeu, int ref){
		qc.jouer(jeu,ref);
	}*/

}
