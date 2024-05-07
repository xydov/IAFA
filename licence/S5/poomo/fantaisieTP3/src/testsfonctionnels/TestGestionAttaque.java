package testsfonctionnels;

import attaque.BouleDeFeu;
import attaque.Eclair;
import attaque.Feu;
import attaque.Lave;
import protagoniste.Domaine;
import protagoniste.Monstre;
import protagoniste.ZoneDeCombat;

public class TestGestionAttaque {

	public static void main(String[] args) {
		Monstre<Feu> dragotenebre = new Monstre<>("dragotenebre", 200, ZoneDeCombat.AERIEN, Domaine.FEU, new BouleDeFeu(4),
				new Lave(1), new Eclair(3));

		System.out.println(dragotenebre);
		dragotenebre.entreEnCombat();
		System.out.println(dragotenebre.attaque());
		System.out.println(dragotenebre.attaque());
		System.out.println(dragotenebre.attaque());
		
//		RESULTAT ATTENDU
//		Monstre [getNom()=dragotenebre, attaques=[ForceDeCombat [nom=une boule de feu, pointDeDegat=20], ForceDeCombat [nom=un jet de lave, pointDeDegat=80], ForceDeCombat [nom=un �clair, pointDeDegat=50]], zoneDeCombat=AERIEN, getForceDeVie()=200]
//		ForceDeCombat [nom=un �clair, pointDeDegat=50]
//		ForceDeCombat [nom=une boule de feu, pointDeDegat=20]
//		ForceDeCombat [nom=un jet de lave, pointDeDegat=80]
	}

}
