package bataille;

import protagoniste.ZoneDeCombat;

public class Salle {
	private int numSalle;
	private ZoneDeCombat zoneDeCombat;
	
	public Salle(int numSalle, ZoneDeCombat zoneDeCombat) {
		this.numSalle = numSalle;
		this.zoneDeCombat = zoneDeCombat;
	}

	public int getNumeroSalle() {
		return numSalle;
	}

	public ZoneDeCombat getZoneDeCombat() {
		return zoneDeCombat;
	}


	public String toString() {
		return "Salle n°" + numSalle + " de type combat " + zoneDeCombat.toString();
	}	
	
}
