package tp3.serveur;

import java.awt.Point;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Hashtable;
import java.util.Vector;
/**
 * 
 * @author Sebastien Leriche, leriche@irit.fr
 * Fevrier 2006 - TP L3 Concepts de Programmation
 * 
 */
public interface Asteroide325 extends Remote {

	int allocateRef() throws RemoteException;
	void connect(VueSujet s) throws RemoteException;
	Vector<VueSujet> getWorld() throws RemoteException;
	Hashtable<Integer, Point> regarder(int posx, int posy) throws RemoteException;
	boolean peutJouer(int ref, int ref2) throws RemoteException;
	void faireGagnerPerdre(int ref, int qtite) throws RemoteException;
}
