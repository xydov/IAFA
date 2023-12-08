package bataille;

import protagoniste.EtreVivant;
import protagoniste.Homme;
import protagoniste.Monstre;

public class Bataille {
	private Camp<Homme> campHumains = new Camp<Homme>();
	private Camp<Monstre<?>> campMonstres = new Camp<Monstre<?>>();
	
	public void ajouter(Homme homme) {
		campHumains.ajouter(homme);
	}
	
	public void eliminer(Homme homme) {
		campHumains.eliminer(homme);
	}
	
	public void ajouter(Monstre<?> monstre) {
		campMonstres.ajouter(monstre);
	}
	
	public void eliminer(Monstre<?> monstre) {
		campMonstres.eliminer(monstre);
	}
		
	public Camp<Homme> getCampHumains() {
		return campHumains;
	}
	
	public Camp<Monstre<?>> getCampMonstres() {
		return campMonstres;
	}
	
}

