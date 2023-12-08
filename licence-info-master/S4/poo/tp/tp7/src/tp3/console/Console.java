package tp3.console;

import java.rmi.Remote;
import java.rmi.RemoteException;

import tp3.serveur.VueSujet;
/**
 * 
 * @author Sebastien Leriche, leriche@irit.fr
 * Fevrier 2006 - TP L3 Concepts de Programmation
 * 
 */
public interface Console extends Remote {
	public void shutDown(String cause) throws RemoteException;
	public void run() throws RemoteException;
	public VueSujet update() throws RemoteException;
	public boolean isJoueur() throws RemoteException;
	public void faireGagnerPerdre(int qtite) throws RemoteException;
}
