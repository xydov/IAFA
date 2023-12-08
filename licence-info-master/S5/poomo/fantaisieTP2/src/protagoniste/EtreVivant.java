package protagoniste;

import bataille.Bataille;

public abstract class EtreVivant {
	
	protected String nom;
	protected int forceDeVie;
	protected Bataille bataille;
	
	public EtreVivant(String nom, int forceDeVie) {
		this.nom = nom;
		this.forceDeVie = forceDeVie;
	}
		
	public String getNom() {
		return nom;
	}
	
	public int getForceDeVie() {
		return forceDeVie;
	}
	
	public abstract void mourir();
	
	
	public void rejointBataille(Bataille bataille) {
		this.bataille = bataille;
	}
	
	@Override
	public String toString() {
		return "EtreVivant [nom=" + nom + ", forceDeVie=" + forceDeVie + "]";
	}
}
