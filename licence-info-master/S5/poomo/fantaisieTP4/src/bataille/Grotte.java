package bataille;

import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Random;

import protagoniste.Monstre;
import protagoniste.ZoneDeCombat;

public class Grotte {
	private LinkedHashMap<Salle, List<Salle>> planGrotte = new LinkedHashMap<Salle, List<Salle>>();
	private HashMap<Salle, Bataille> batailles = new HashMap<Salle, Bataille>(); 
	private HashSet<Salle> sallesExplorees = new HashSet<Salle>();
	private int numeroSalleDecisive;

	
	public void ajouterSalle(ZoneDeCombat zdc, Monstre<?>...monstres ) {
		// creation de la nouvelle salle
		Salle s = new Salle(planGrotte.size() + 1, zdc);
		// creation de la bataille liee a la salle
		Bataille b = new Bataille(); 
		
		// ajout des monstres dans la bataille
		for(Monstre<?> m: monstres) {
			b.ajouter(m);
		}
		// ajout de la salle aux attributs: 
		// 	planGrotte
		// 	cle: la salle | valeur: une <ArrayList>
		planGrotte.put(s, new ArrayList<Salle>());
		//	batailles
		//	cle: la salle | valeur: la bataille
		batailles.put(s, b);		
	}
	
	private Salle trouverSalle(int numeroSalle) {
		int indice = 0;
		
		for(Salle s: planGrotte.keySet()) {
			// nombre de salles parcourus
			indice ++;
			if (s.getNumeroSalle() == numeroSalle) {
				return s;
			}
		}
		return null;
	}
	
	public void configurerAcces(int n_salle_origine, int...numeros) {
		Salle s_origine = trouverSalle(n_salle_origine);
		List<Salle> salles_accessibles = planGrotte.get(s_origine);
		// pour chaque numero passee en parametres
		// recuperer la salle coorrespondante
		// et l'ajouter a la liste des salles accessibles
		for(int i: numeros) {
			salles_accessibles.add(trouverSalle(i));
		}
	}
	
	
	public void setNumeroSalleDecisive(int numeroSalleDecisive) {
		this.numeroSalleDecisive = numeroSalleDecisive;
	}
	
	public boolean salleDecisive(Salle s) {
		return s.getNumeroSalle() == numeroSalleDecisive;
	}
	
	public Salle premiereSalle() {
		Salle ps = trouverSalle(1);
		sallesExplorees.add(ps);
		return ps;
	}
	
	public Salle salleSuivante(Salle actuelle) {
		Random r = new Random();
		List<Salle> salles_accessibles = planGrotte.get(actuelle);
		// enlever les salles déjà explorées, sallesExplorees de salles_accessibles		
		for(Salle se: sallesExplorees) {
//			if (salles_accessibles.size() == 0) {
//				for(Salle s: planGrotte.keySet()) {
//					salles_accessibles.add(s);
//				}
//			}
			for(Salle sa: salles_accessibles) {
				if (se.equals(sa)) {
					salles_accessibles.remove(se);
				}
			}
		}
		
		
		Salle dest = salles_accessibles.get(r.nextInt(salles_accessibles.size()));
		sallesExplorees.add(dest);
		return dest;
	}
	
	
	public String afficherPlanGrotte() {
		StringBuilder affichage = new StringBuilder();
		for (Map.Entry<Salle, List<Salle>> entry : planGrotte.entrySet()) {
			Salle salle = entry.getKey();
			List<Salle> acces = planGrotte.get(salle);
			affichage.append("La " + salle + ".\nelle possede " + acces.size() + " acces : ");
			for (Salle access : acces) {
				affichage.append(" vers la salle " + access);
		   }
			Bataille bataille = batailles.get(salle);
			Camp<Monstre<?>> camp = bataille.getCampMonstres();
			Monstre<?> monstre = camp.selectionner();
			if (camp.nbCombattants() > 1) {
				affichage.append("\n" + camp.nbCombattants() + " monstres de type ");
			} else {
				affichage.append("\nUn monstre de type ");
			}
		 	 affichage.append(monstre.getNom() + " la protege.\n");
		 	 if (salle.getNumeroSalle() == numeroSalleDecisive) {
		 		 affichage.append("C'est dans cette salle que se trouve la pierre de sang.\n");
		 	 }
		 	 affichage.append("\n");
		}
		return affichage.toString();
	}
}
