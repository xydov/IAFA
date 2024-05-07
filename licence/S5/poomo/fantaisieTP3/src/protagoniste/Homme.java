package protagoniste;

import bataille.Bataille;

public class Homme extends EtreVivant {

	public Homme(String nom) {
		super(nom, 70);
	}
	
	public void rejointBataille(Bataille bataille) {
		this.bataille = bataille;
		this.bataille.ajouter(this);
	}
	
	public void mourir() {
		bataille.eliminer(this);
	}

	@Override
	public String toString() {
		return "Homme [nom=" + nom + ", forceDeVie=" + forceDeVie + "]";
	}
	
	
	
}
