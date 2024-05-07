package tp3.console;

import java.awt.Point;
import java.rmi.Naming;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Random;

import tp3.Sujet;
/*import tp3.jeux.JeuSimple;
import tp3.jeux.Joueur;
*/
import tp3.serveur.Asteroide325;
import tp3.serveur.VueSujet;

/** 
 * @author Sebastien Leriche, leriche@irit.fr
 * Fevrier 2006 - TP L3 Concepts de Programmation
 * Cette classe aurait pu servir de console, mais en faisant gerer les exceptions par les eleves
 * On a fait le choix de simplifier au maximum la vision de la console en les encapsulant
 *
 */

public class QuasiConsole extends UnicastRemoteObject implements Console {
	private static final long serialVersionUID = 1L;
	private static final int port=5099;	//port par defaut pour communiquer avec le serveur RMI
	private Remote server=null;
	private VueSujet vs;
	private Sujet c;
	private Hashtable<Integer,Point> vue;
	private int[][] vision=new int[20][20];
	private boolean cacheVue;
	private Point pointErrance;
	
	QuasiConsole (Sujet c) throws RemoteException {
		super();
		try{
			this.c=c;	//pour le call-back direct du sujet
			
			//affectation d'une position aleatoire
			Random r=new Random();
			int posx=r.nextInt(100);
			int posy=r.nextInt(100);
			
			//handshake/enregistrement RMI
			server=Naming.lookup("rmi://localhost:"+port+"/Asteroide325");
			int id=((Asteroide325) server).allocateRef();
			Naming.rebind("rmi://localhost:"+port+"/Console"+id,this);
			vs=new VueSujet(id,posx,posy, c.getNom(), c.getArgent(), "Aterrissage...");
			((Asteroide325) server).connect(vs);
			System.out.println("(JAVABOY) Console connectee ["+id+"]");
		} catch (Exception e) {
			System.out.println("(JAVABOY) Erreur : la console n'a pas pu etre creee !\nCause : "+e.getCause());
			//e.printStackTrace();
		}
	}
	
	/**
	 * Appele par le serveur, pour prevenir le client que ce dernier ne sera plus "joue"
	 * Cela permet de ne pas saturer le serveur avec des clients mal programmes (boucle infine etc.)
	 */
	public void shutDown(String cause) throws RemoteException {
		System.out.println("(JAVABOY) Console deconnectee : "+cause);
		System.exit(1);
	}

	/**
	 * Appele par le serveur pour faire jouer un sujet un tour 
	 */
	public void run() throws RemoteException {
		vs.decrTTL();		//le sujet perd un point de duree de vie
		cacheVue=false;		//permet de ne pas appeller regarder() si deje fait
		c.run();
	}
	
	/**
	 * Appelle par le serveur pour faire la MAJ du sujet
	 */
	public VueSujet update() throws RemoteException {
		VueSujet aux=(VueSujet) vs.clone();
		vs.setPhrase("");
		return aux;
	}
	
	private class PointComparator implements Comparator<Point> {
		private Point p0;

		PointComparator(int dx, int dy) {
			p0=new Point(dx,dy);
		}

		public int compare(Point arg0, Point arg1) {
			return (distance(arg0).compareTo(distance(arg1)));
		}

		private int carre(double d) {
			return (int) Math.pow(d,2);
		}
		
		private Integer distance(Point arg1) {
			return carre(p0.getX()-arg1.getX())+carre(p0.getY()-arg1.getY());
		}
	}
	
	private class distPoint {
		Point[] pList=new Point[8];
		distPoint() {
			int k=0;
			for (int i=-1; i<=1; i++)
				for (int j=-1; j<=1; j++)
					if ((i!=0)||(j!=0)) 
						pList[k++]=new Point(i,j);
		}
		
		Point[] sort(int dx, int dy) {
			Arrays.sort(pList, new PointComparator(dx,dy));
			return pList;
		}
	}
	
	/**
	 * Deplace ce sujet d'une case en direction du sujet dont la reference est donnee en parametre
	 * @param ref la reference d'un sujet
	 */
	public void seDirigerVers(int ref) {
		Point pvers;
		
		if (ref==vs.getRef()) return; //on se cherche soi-meme ??? soit...
				
		if ((vue==null) || (! cacheVue)) regarder(); 
		if (vue==null) return;

		//ref==0=>errer aleatoirement
		if (ref==0) {
			if ((pointErrance!=null) && (pointErrance.getX()==vs.getX()) && (pointErrance.getY()==vs.getY())) pointErrance=null;
			if (pointErrance==null) { // definir un nouvel objectif
				Random r=new Random();
				pointErrance=new Point(r.nextInt(100), r.nextInt(100));
			}
			pvers=pointErrance;
		} else pvers=vue.get(ref);
		
		if (pvers==null) return;
		
		int dx=(int) (pvers.getX()-vs.getX());
		if (dx!=0)	dx=dx/Math.abs(dx);
		int dy=(int) (pvers.getY()-vs.getY());
		if (dy!=0)  dy=dy/Math.abs(dy);
		
		if (vision[10+dy][10+dx]==0) {		
			vs.setX(vs.getX()+dx);
			vs.setY(vs.getY()+dy);
		} else {// aller dans la case libre non occupee la plus appropriee
			distPoint dt=new distPoint();
			Point[] possibles=dt.sort(dx,dy);
			for (int i=0; i<possibles.length; i++) 
				if (vision[(int) (10+possibles[i].getY())][(int) (10+possibles[i].getX())]==0) {
					vs.setX((int) (vs.getX()+possibles[i].getX()));
					vs.setY((int) (vs.getY()+possibles[i].getY()));
					return;
				}
		}
	}

	/**
	 * Permet e un sujet de percevoir son environnement
	 * @return un tableau d'entiers, nuls si il n'y a aucun sujet en cette position, une reference de sujet sinon
	 */
	public int[][] regarder() {
		int[][] aux=new int[20][20];
		
		//on efface tout
		for (int i=0; i<vision.length; i++)
			for(int j=0; j<vision[0].length; j++)
				vision[i][j]=0;
		
		//en cas d'erreur : retourne un tableau rempli de '0'
		try {
			vue=((Asteroide325) server).regarder(vs.getX(),vs.getY());
			cacheVue=true;
			
			for(Enumeration<Integer> enu=vue.keys(); enu.hasMoreElements();) {
				int ref=enu.nextElement();
				if (ref!=vs.getRef()) { //on ne se voit pas soi-meme
					Point p=vue.get(ref);
					vision[10+(int) p.getY()-vs.getY()][10+(int) p.getX()-vs.getX()]=ref;
				}
			}
		} catch (Exception e) {e.printStackTrace();}
		
		//on fait une copie de la vision (pour ne pas qu'elle soit deformee par le sujet)
		for (int i=0; i<vision.length; i++)
			for(int j=0; j<vision[0].length; j++)
				aux[i][j]=vision[i][j];
		
		return aux;
	}
		
	/**
	 * Pour communiquer avec l'exterieur
	 * @param s le message e transmettre
	 */
	public void parler(String s) {
		vs.setPhrase(vs.getPhrase()+" - "+s);
	}

	/**
	 * Lancer un jeu sur le serveur entre ce sujet et celui passe en parametre
	 * @param jeu
	 * @param ref l'adversaire
	 */
/*	public void jouer(JeuSimple jeu, int ref) {
		String c1,c2;
		int result;
		Random r=new Random();
		
		if (vs.getArgent()<=0) {
			parler("Je ne peux pas jouer e "+jeu.getNom()+" ! Pas assez d'argent ("+vs.getArgent()+")...");
			return;
		}
		
		try {
			if (! ((Asteroide325) server).peutJouer(vs.getRef(),ref)) 
				parler("["+ref+"] ne veut pas ou ne peut pas jouer avec moi !");
			else {
				c1=jeu.jouerUnTour();
				c2=jeu.jouerUnTour();
				result=r.nextBoolean()?jeu.arbitrer(c1,c2):jeu.arbitrer(c2,c1);
				if (result<0) {
					((Joueur) c).perdre(1);
					vs.setArgent(vs.getArgent()-1);
					((Asteroide325) server).faireGagnerPerdre(ref,1);
				} else if (result>0) {
					((Joueur) c).gagner(1);
					vs.setArgent(vs.getArgent()+1);
					((Asteroide325) server).faireGagnerPerdre(ref,-1);
				} else parler("Ex-aequo au jeu de "+jeu.getNom());
			}
		} catch (RemoteException e) {e.printStackTrace();}
	}
*/

	/**
	 * Vrai si le sujet implemente l'interface Joueur
	 */
	public boolean isJoueur() throws RemoteException {
/*		return (c instanceof Joueur);
*/
		return false;
	}

	/**
	 * Appele par le serveur pour faire gagner/perdre le sujet
	 * Si ce n'est pas un 'Joueur', on ne fait rien
	 */
	public void faireGagnerPerdre(int qtite) throws RemoteException {
/*		if (! isJoueur()) return;
		vs.setArgent(vs.getArgent()+qtite);
		if (qtite>0) ((Joueur) c).gagner(qtite); else ((Joueur) c).perdre(-qtite);
*/
	}
}
