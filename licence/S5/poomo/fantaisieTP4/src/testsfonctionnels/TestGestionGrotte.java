package testsfonctionnels;

import attaque.BouleDeFeu;
import attaque.Eclair;
import attaque.Feu;
import attaque.Glace;
import attaque.Griffe;
import attaque.LameAcier;
import attaque.Lave;
import attaque.Morsure;
import attaque.PicsDeGlace;
import attaque.Tornade;
import attaque.Tranchant;
import bataille.Grotte;
import bataille.Salle;
import protagoniste.Domaine;
import protagoniste.Monstre;
import protagoniste.ZoneDeCombat;

public class TestGestionGrotte {

	@SuppressWarnings("unchecked")
	public static void main(String[] args) {
		Monstre<Feu> dragotenebre = new Monstre<>("dragotenebre", 200, ZoneDeCombat.AERIEN, Domaine.FEU,
				new BouleDeFeu(4), new Lave(1), new Eclair(3));

		Monstre<Tranchant>[] tableauVampirien = new Monstre[10];
		for (int i = 0; i < 10; i++) {
			tableauVampirien[i] = new Monstre<>("vampirien", 10, ZoneDeCombat.AERIEN, Domaine.TRANCHANT,
					new Morsure(10));
		}

		Monstre<Glace> marinsangant = new Monstre<>("marinsangant", 150, ZoneDeCombat.AQUATIQUE, Domaine.GLACE,
				new PicsDeGlace(10), new Tornade(1));

		Monstre<Tranchant> guillotimort = new Monstre<>("guillotimort", 80, ZoneDeCombat.TERRESTRE, Domaine.TRANCHANT,
				new LameAcier(10), new Griffe());

		Monstre<Glace> givrogolem = new Monstre<>("givrogolem", 200, ZoneDeCombat.TERRESTRE, Domaine.GLACE,
				new PicsDeGlace(10), new Tornade(1));

		Monstre<Feu> aqualave = new Monstre<>("aqualave", 30, ZoneDeCombat.AQUATIQUE, Domaine.FEU, new Lave(5));

		Monstre<Tranchant> requispectre = new Monstre<>("requispectre", 200, ZoneDeCombat.AQUATIQUE, Domaine.TRANCHANT,
				new Griffe());

		Monstre<Glace> soufflemort = new Monstre<>("soufflemort", 120, ZoneDeCombat.AERIEN, Domaine.GLACE,
				new Tornade(8));

		Monstre<Feu> cramombre = new Monstre<>("cramombre", 80, ZoneDeCombat.TERRESTRE, Domaine.FEU, new BouleDeFeu(2),
				new Lave(1), new Eclair(1));

		Grotte grotte = new Grotte();

		grotte.ajouterSalle(ZoneDeCombat.TERRESTRE, guillotimort);
		grotte.ajouterSalle(ZoneDeCombat.AERIEN, dragotenebre);
		grotte.ajouterSalle(ZoneDeCombat.TERRESTRE, cramombre);
		grotte.ajouterSalle(ZoneDeCombat.TERRESTRE, givrogolem);
		grotte.ajouterSalle(ZoneDeCombat.AERIEN, tableauVampirien);
		grotte.ajouterSalle(ZoneDeCombat.AQUATIQUE, aqualave);
		grotte.ajouterSalle(ZoneDeCombat.AQUATIQUE, marinsangant);
		grotte.ajouterSalle(ZoneDeCombat.AQUATIQUE, requispectre);
		grotte.ajouterSalle(ZoneDeCombat.AERIEN, soufflemort);

		grotte.configurerAcces(1, 2, 6);
		grotte.configurerAcces(2, 1, 3, 5);
		grotte.configurerAcces(3, 2, 4);
		grotte.configurerAcces(4, 3, 5, 9);
		grotte.configurerAcces(5, 2, 4, 6, 8);
		grotte.configurerAcces(6, 1, 5, 7);
		grotte.configurerAcces(7, 6, 8);
		grotte.configurerAcces(8, 5, 7, 9);
		grotte.configurerAcces(9, 4, 8);

		grotte.setNumeroSalleDecisive(9);
		

		System.out.println("\n**** TP4 ****");
		System.out.println("Plan de la grotte\n" + grotte.afficherPlanGrotte());
		System.out.println("\nParcours de la grotte\n");
		Salle salle = grotte.premiereSalle();
		System.out.println(salle + "\n");
		if (!grotte.salleDecisive(salle)) {
			do {
				salle = grotte.salleSuivante(salle);
				System.out.println(salle + "\n");

			} while (!grotte.salleDecisive(salle));
			System.out.println("C'est la salle contenant la Pierre de Sang");
		}

	}
//		RESULTAT ATTENDU
//		**** TP4 ****
//		Plan de la grotte
//		La Salle n�1 de type combat TERRESTRE.
//		elle possede 2 acces :  vers la salle Salle n�2 de type combat AERIEN vers la salle Salle n�6 de type combat AQUATIQUE
//		Un monstre de type guillotimort la protege.
//
//		La Salle n�2 de type combat AERIEN.
//		elle possede 3 acces :  vers la salle Salle n�1 de type combat TERRESTRE vers la salle Salle n�3 de type combat TERRESTRE vers la salle Salle n�5 de type combat AERIEN
//		Un monstre de type dragotenebre la protege.
//
//		La Salle n�3 de type combat TERRESTRE.
//		elle possede 2 acces :  vers la salle Salle n�2 de type combat AERIEN vers la salle Salle n�4 de type combat TERRESTRE
//		Un monstre de type cramombre la protege.
//
//		La Salle n�4 de type combat TERRESTRE.
//		elle possede 3 acces :  vers la salle Salle n�3 de type combat TERRESTRE vers la salle Salle n�5 de type combat AERIEN vers la salle Salle n�9 de type combat AERIEN
//		Un monstre de type givrogolem la protege.
//
//		La Salle n�5 de type combat AERIEN.
//		elle possede 4 acces :  vers la salle Salle n�2 de type combat AERIEN vers la salle Salle n�4 de type combat TERRESTRE vers la salle Salle n�6 de type combat AQUATIQUE vers la salle Salle n�8 de type combat AQUATIQUE
//		10 monstres de type vampirien la protege.
//
//		La Salle n�6 de type combat AQUATIQUE.
//		elle possede 3 acces :  vers la salle Salle n�1 de type combat TERRESTRE vers la salle Salle n�5 de type combat AERIEN vers la salle Salle n�7 de type combat AQUATIQUE
//		Un monstre de type aqualave la protege.
//
//		La Salle n�7 de type combat AQUATIQUE.
//		elle possede 2 acces :  vers la salle Salle n�6 de type combat AQUATIQUE vers la salle Salle n�8 de type combat AQUATIQUE
//		Un monstre de type marinsangant la protege.
//
//		La Salle n�8 de type combat AQUATIQUE.
//		elle possede 3 acces :  vers la salle Salle n�5 de type combat AERIEN vers la salle Salle n�7 de type combat AQUATIQUE vers la salle Salle n�9 de type combat AERIEN
//		Un monstre de type requispectre la protege.
//
//		La Salle n�9 de type combat AERIEN.
//		elle possede 2 acces :  vers la salle Salle n�4 de type combat TERRESTRE vers la salle Salle n�8 de type combat AQUATIQUE
//		Un monstre de type soufflemort la protege.
//		C'est dans cette salle que se trouve la pierre de sang.
//
//

		
		//UNE POSSIBILITE DE RESULTAT PARMI D AUTRE
		
//		Parcours de la grotte
//
//		Salle n�1 de type combat TERRESTRE
//
//		Salle n�2 de type combat AERIEN
//
//		Salle n�5 de type combat AERIEN
//
//		Salle n�4 de type combat TERRESTRE
//
//		Salle n�3 de type combat TERRESTRE
//
//		Salle n�2 de type combat AERIEN
//
//		Salle n�3 de type combat TERRESTRE
//
//		Salle n�4 de type combat TERRESTRE
//
//		Salle n�9 de type combat AERIEN
//
//		C'est la salle contenant la Pierre de Sang
}
