package tp3.serveur;

import java.awt.Point;
import java.net.InetAddress;
import java.rmi.Naming;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.text.DateFormat;
import java.util.Date;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Vector;

import tp3.console.Console;


/**
 * 
 * @author Sebastien Leriche, leriche@irit.fr
 * Fevrier 2006 - TP L3 Concepts de Programmation
 * Serveur principal des TP "Asteroede 325"
 * 
 */

public class Asteroide325Server extends UnicastRemoteObject implements Asteroide325, Runnable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int port;
	private int compteur=0;
	private Hashtable<Remote,VueSujet> clients=null;
	
	/**
	 * Classe permettant de lancer une execution du client (run)
	 * dans un thread separe, pour pouvoir limiter son temps d'execution
	 * via un join(timeout)
	 *
	 */
	public class TimeoutOp extends Thread {
		private Remote r;
		TimeoutOp(Remote r) {this.r=r; start();}
		public void run() {
			try {
				((Console) r).run(); //on lance une execution
				clients.put(r,((Console) r).update()); //maj du serveur ac les infos du client
				if (clients.get(r).getTTL()==0) {
					clients.remove(r);
					((Console) r).shutDown("Vous etes reste trop longtemps, le roi s'ennuie et vous chasse !");
					System.out.println("Client elimine car TTL nul (client ne+"+clients.get(r).getRef()+") !");
				}
				
			} catch (Exception e) {
				//les exceptions sont inhibees ici, que ce soit une deconnection du client ou autre
				//en cas d'erreur, le client ne sera plus jamais execute
				//e.printStackTrace();
				clients.remove(r);
			} 
		}
	}
	
	/**
	 * Constructeur du serveur, s'enregistre dans le registre RMI
	 * et demarre son thread serveur
	 * @param port 
	 * @throws Exception
	 */
	Asteroide325Server(int port) throws Exception {
		super();
		this.port=port;
		Naming.rebind("rmi://localhost:"+port+"/Asteroide325",this);
		clients=new Hashtable<Remote,VueSujet>();
		new Thread(this).start();
	}
	
	/**
	 * pour recuperer un identifiant unique (qui sert pour les consoles et pour l'acces RMI)
	 * la synchro permet de garantir l'acces e un seul thread e la fois au compteur++ 
	 */
	public synchronized int allocateRef() throws RemoteException {
		compteur++;
		return compteur;
	}
	
	/**
	 * appele par une console cliente, pour que le serveur recupere son @RMI et le mette en jeu
	 * la synchro permet de garantir qu'on ne fait pas de nouvelle connection pdt un tour de jeu
	 * cf. run()
	 */
	public synchronized void connect(VueSujet s) throws RemoteException {
		try {
			Remote r=Naming.lookup("rmi://localhost:"+port+"/Console"+s.getRef());
			clients.put(r, s);
		} catch (Exception e) {
			System.out.println("Erreur lors de la connexion d'un client (ref="+s.getRef()+") :");
			e.printStackTrace();
		}
	}
		
	/**
	 * appele par l'IHM pour afficher une representation de l'asteroede
	 * via RMI, on envoie une copie (serialisee) du monde 
	 */
	public Vector<VueSujet> getWorld() throws RemoteException {
		Vector<VueSujet> aux=new Vector<VueSujet>();
		for(VueSujet s:clients.values()) {aux.add(s);}
		return aux; 
	}
	
	//distance de Manhatan
	private int distance(int x,int y, int xx, int yy) {
		if (Math.abs(xx-x)>Math.abs(yy-y)) return Math.abs(xx-x); else return Math.abs(yy-y);
	}
	
	/**
	 * appele par la console, pour voir autour du sujet
	 * on se limite e une vision de 20x20
	 */
	public Hashtable<Integer, Point> regarder(int posx, int posy) throws RemoteException {
		Hashtable<Integer, Point> aux=new Hashtable<Integer, Point>();
		
		for(VueSujet s:clients.values()) {
			if ((distance(s.getX(), s.getY(), posx, posy))<10) {
				aux.put(s.getRef(),new Point(s.getX(), s.getY()));
			}
		}
		return aux;
	}
	
	private int countClients() {//pour la boucle dans le main
		return clients.size();
	}
	
	/**
	 * boucle principale du thread serveur
	 */
	public void run() {
		TimeoutOp to;
		while (true) {
			try {
				synchronized(this) {	//on verouille le serveur durant un tour de jeu -> pas de connexion/deconnexion
					//System.out.println(tour++);
					
					for(Enumeration<Remote> enu=clients.keys(); enu.hasMoreElements();) {
						//boucle de jeu
						Remote r=enu.nextElement();
						to=new TimeoutOp(r);
						to.join(1000);
						if (to.isAlive()) {
							to=null;
							System.out.println("Depassement du temps (client ne+"+clients.get(r).getRef()+") !");
							clients.remove(r);
							((Console) r).shutDown("Le roi s'est lasse de votre temps de reponse trop long !");
						} 
					}
				}
				Thread.sleep(1000);	//TODO ? : dormir 'au plus' 1 seconde (difference temps execution et 1sec.)
			} catch (Exception e) {e.getMessage();}
		}
	}
	
	//ref->remote
	private Remote getRemote(int ref) {
		for(Enumeration<Remote> enu=clients.keys(); enu.hasMoreElements();) {
			Remote r=enu.nextElement();
			if (clients.get(r).getRef()==ref) return r;
		}
		return null;
	}

	//ref->VueSujet
	private VueSujet getVueSujet(int ref) {
		for(Enumeration<Remote> enu=clients.keys(); enu.hasMoreElements();) {
			Remote r=enu.nextElement();
			if (clients.get(r).getRef()==ref) return clients.get(r);
		}
		return null;
	}
	
	/**
	 * teste si un joueur implemente Joueur et s'ils sont la meme position 
	 */
	public boolean peutJouer(int ref, int ref2) throws RemoteException {
		VueSujet v1,v2;
		if (! ((Console) getRemote(ref2)).isJoueur()) return false;
		v1=getVueSujet(ref);
		v2=getVueSujet(ref2);
		return distance(v1.getX(), v1.getY(), v2.getX(), v2.getY())<=1;
	}

	/**
	 * transfere l'ordre gagner/perdre au joueur
	 */
	public void faireGagnerPerdre(int ref, int qtite) throws RemoteException {
		((Console) getRemote(ref)).faireGagnerPerdre(qtite);
	}
		
	/**
	 * Programme principal du serveur
	 * @param args Le port sur lequel on lance le serveur.
	 */
	public static void main(String[] args) throws Exception {
		int port=5099;	//par defaut, port=5099
		if (args.length!=0) port=Integer.parseInt(args[0]);
		
		System.out.println("Creation du registre RMI sur le port "+port+"...");
		java.rmi.registry.LocateRegistry.createRegistry(port);
	    
	    System.out.println("Creation du serveur sur le port "+port+"...");
	    Asteroide325Server server=new Asteroide325Server(port);
	    
	    while(true) {
	    	System.out.println("[Asteroede 325 sur "+InetAddress.getLocalHost().getCanonicalHostName()+":"+port+"] "
	    			+DateFormat.getTimeInstance().format(new Date())
	    			+" ("+server.countClients()+" clients)"
	    			+"\n");
	    	try {
	    		Thread.sleep(1000*60); //delai = 1 minute
	    	} catch (InterruptedException e) {}
	    }
	}


}
