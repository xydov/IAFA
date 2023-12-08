package livre;

import java.util.LinkedList;

import bataille.Bataille;
import bataille.Camp;
import protagoniste.Heros;
import protagoniste.Homme;

public class AideEcrivain {
	
	private LinkedList<Homme> listeTriee = new LinkedList<Homme>();
	
	private Bataille bataille;
	
	public AideEcrivain(Bataille bataille) {
		this.bataille = bataille;
	}
	
	public String visualiserForcesHumaines() {
		Camp<Homme> c = bataille.getCampHumains();
		int iHeros = 0;
		
		for(Homme h: c) {
			if (h instanceof Heros) {
				listeTriee.add(iHeros, h);
				iHeros += 1;
			} else if (h instanceof Homme) {
				listeTriee.add(h);
			}
		}
		
//		for(Homme h: c) {
//			if (h.getForceDeVie() == 100) {
//				listeTriee.add(iHeros, h);
//				iHeros += 1;
//			} else if (h.getForceDeVie() == 70) {
//				listeTriee.add(h);
//			}
//		}
			
		return listeTriee.toString();
	}

}
