package protagoniste;

import java.util.Arrays;
import java.util.Random;
import java.util.Iterator;

import attaque.Pouvoir;
import bataille.Bataille;

public class Monstre <TypePouvoir> extends EtreVivant{
	
	private Pouvoir[] attaques;
	private ZoneDeCombat zoneDeCombat;
	private Domaine domaine;
	private GestionAttaque gestionAttaque;
	
	@SafeVarargs
	public Monstre(String nom, int forceDeVie, ZoneDeCombat zoneDeCombat, Domaine domaine, TypePouvoir...pouvoirs) {
		super(nom, forceDeVie);
		this.zoneDeCombat = zoneDeCombat;
		this.domaine = domaine;
		if (pouvoirs != null) {
			this.attaques = new Pouvoir[pouvoirs.length];
			int i = 0;
			for (TypePouvoir p : pouvoirs) {
				this.attaques[i] = (Pouvoir) p;
				i++;
			}
		}
		else {
			this.attaques = null;
		}
	}
	
	public ZoneDeCombat getZoneDeCombat() {
		return zoneDeCombat;
	}
	
	public Domaine getDomaine() {
		return domaine;
	}

	@Override
	public String toString() {
		return "Monstre [getNom()=" + getNom() +  ", attaques=" + Arrays.toString(attaques) + ", zoneDeCombat=" + zoneDeCombat + ", domaine="
				+ domaine + ", getForceDeVie()=" + getForceDeVie() + "]";
	}
	
	public static class GestionAttaque implements Iterator<Pouvoir>{
		
		private Pouvoir[] attaquesPossibles;
		private int nbAttaquesPossibles;
		
		public GestionAttaque(Pouvoir[] attaques, int nbAttaquesPossibles) {
			this.attaquesPossibles = attaques;
			this.nbAttaquesPossibles = nbAttaquesPossibles;
		}
		
		public boolean hasNext() {
			
			for (int i = 0; i < nbAttaquesPossibles; i++) {
				if (!attaquesPossibles[i].isOperationnel()) {
					attaquesPossibles[i] = attaquesPossibles[nbAttaquesPossibles - 1];
					nbAttaquesPossibles --;
				}
			}
			
			return nbAttaquesPossibles != 0;
		}
		
		public Pouvoir next() {
//			Random r = new Random();
			return attaquesPossibles[new Random().nextInt(nbAttaquesPossibles)];
		}
	}
	
	public void entreEnCombat() {
		// regenere tout les pouvoirs
		for(Pouvoir p: attaques) {
			p.regenererPouvoir();
		}
		// affecte un nouvel objet a gestionAttaque
		int n = attaques.length;
		gestionAttaque = new GestionAttaque(attaques, n);
	}
	
	public Pouvoir attaque() {
		if(gestionAttaque.nbAttaquesPossibles > 0) {
			return gestionAttaque.next();
		}
		return null;
	}
	
	public void rejointBataille(Bataille bataille) {
		this.bataille = bataille;
		this.bataille.ajouter(this);
	}

	@Override
	public void mourir() {
		bataille.eliminer(this);
	}
	
}