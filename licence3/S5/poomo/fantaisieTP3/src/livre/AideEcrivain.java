package livre;

import java.util.Comparator;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.NavigableSet;
import java.util.TreeSet;

import attaque.Glace;
import bataille.Bataille;
import bataille.Camp;
import protagoniste.Domaine;
import protagoniste.Heros;
import protagoniste.Homme;
import protagoniste.Monstre;
import protagoniste.ZoneDeCombat;

public class AideEcrivain {
	private Bataille bataille;
	private LinkedList<Homme> listeTriee = new LinkedList<Homme>();
	
	private TreeSet<Monstre<?>> monstreDomaineSet = 
			new TreeSet<Monstre<?>>(
					new Comparator<Monstre<?>>() {
						public int compare(Monstre<?> arg0, Monstre<?> arg1) {
							int c = arg0.getDomaine().compareTo(arg1.getDomaine());
							// prevent the exclusion of same domain monster
							if (c == 0) {
								c = arg0.getNom().compareTo(arg1.getNom());
							}
							return c;
						}
					});
	private TreeSet<Monstre<?>> monstresZoneSet = 
			new TreeSet<Monstre<?>>(
					new Comparator <Monstre<?>>() {
						public int compare(Monstre<?> arg0, Monstre<?> arg1) {
							ZoneDeCombat zarg0 = arg0.getZoneDeCombat();
							ZoneDeCombat zarg1 = arg1.getZoneDeCombat();
							int farg0 = arg0.getForceDeVie();
							int farg1 = arg1.getForceDeVie();
							if(zarg0.equals(zarg1)) {
								if (farg0 == farg1) {
									return arg0.getNom().compareTo(arg1.getNom());
								}
								else {
									return arg1.getForceDeVie() - arg0.getForceDeVie();
								}
							}
							else {
								return zarg0.compareTo(zarg1);
							}
						}
					});
	
	private NavigableSet<Monstre<?>> monstresDeFeu = new TreeSet<Monstre<?>>();
	private NavigableSet<Monstre<?>> monstresDeGlace = new TreeSet<Monstre<?>>();
	private NavigableSet<Monstre<?>> monstresTranchants = new TreeSet<Monstre<?>>();
	
	
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
	
	public String ordreNaturelMonstre() {
		Camp<Monstre<?>> c = bataille.getCampMonstres();
		
		TreeSet<String> col = new TreeSet<String>();
		
		String final_string = "";
		
		for(Monstre<?> m: c) {
			col.add(m.getNom());
		}
		for(String s: col) {
			final_string += (s + ", ");
		}
		return final_string;
	}
	
	
	public void updateMonstresDomaine() {
		Camp<Monstre<?>> c = bataille.getCampMonstres();
		for(Monstre<?> m: c) {
			monstreDomaineSet.add(m);
		}
	}
	
	public String ordreMonstreDomaine() {
		updateMonstresDomaine();
		String str = "";
		str += "FEU :\n";
		for(Monstre<?> m: monstreDomaineSet) {
			if(m.getDomaine() == Domaine.FEU) {
				str += (m.getNom() + ", ");
			}
		}
		str += "\nGLACE :\n";
		for(Monstre<?> m: monstreDomaineSet) {
			if(m.getDomaine() == Domaine.GLACE) {
				str += m.getNom() + ", ";
			}
		}
		str += "\nTRANCHANT :\n";
		for(Monstre<?> m: monstreDomaineSet) {
			if(m.getDomaine() == Domaine.TRANCHANT) {
				str += m.getNom() + ", ";
			}
		}
		return str;
	}
	
	public void updateMonstresZone() {
		Camp<Monstre<?>> c = bataille.getCampMonstres();
		for(Monstre<?> m: c) {
			monstresZoneSet.add(m);
		}
	}
	
	public String ordreMonstreZone() {
		updateMonstresZone();
		String str = "";
		str += "AERIEN :\n";
		for(Monstre<?> m: monstresZoneSet) {
			if(m.getZoneDeCombat() == ZoneDeCombat.AERIEN) {
				str += (m.getNom() + ": " + m.getForceDeVie() + ", ");
			}
		}
		str += "\nAQUATIQUE :\n";
		for(Monstre<?> m: monstresZoneSet) {
			if(m.getZoneDeCombat() == ZoneDeCombat.AQUATIQUE) {
				str += (m.getNom() + ": " + m.getForceDeVie() + ", ");
			}
		}
		str += "\nTERRESTRE :\n";
		for(Monstre<?> m: monstresZoneSet) {
			if(m.getZoneDeCombat() == ZoneDeCombat.TERRESTRE) {
				str += (m.getNom() + ": " + m.getForceDeVie() + ", ");
			}
		}
		return str;
	}

	public NavigableSet<Monstre<?>> getMonstresDeFeu() {
		initMonstresDeFeu();
		return monstresDeFeu;
	}

	public NavigableSet<Monstre<?>> getMonstresDeGlace() {
		initMonstresDeGlace();
		return monstresDeGlace;
	}

	public NavigableSet<Monstre<?>> getMonstresTranchants() {
		initMonstresTranchant();
		return monstresTranchants;
	}
	
	
	public Monstre<?> firstMonstreDomaine(Domaine domaine){
		Iterator<Monstre<?>> iter = bataille.getCampMonstres().iterator();
		Monstre<?> retourFonction = iter.next();
		while(iter.hasNext()) {
			if(retourFonction.getDomaine().equals(domaine)) {
				return retourFonction;
			}
			retourFonction = iter.next();
		}
		return null;
	}
	
//	public void initMonstresDeFeu() {
//		updateMonstresDomaine();
//		monstresDeFeu = monstreDomaineSet.headSet(firstMonstreDomaine(Domaine.GLACE), false);
//	}
	
	public void initMonstresDeFeu() {
		updateMonstresDomaine();
		monstresDeFeu = monstreDomaineSet.headSet(new Monstre<Glace>("aaaa", 0, null, Domaine.GLACE, (Glace[] )null) , false);
	}
	
	public void initMonstresDeGlace() {
		updateMonstresDomaine();
		monstresDeGlace = monstreDomaineSet.subSet(new Monstre<Glace>("zzzz", 0, null, Domaine.FEU, (Glace[] )null) , false, new Monstre<Glace>("aaaaa", 0, null, Domaine.TRANCHANT, (Glace[] )null), false);
	}
	
	public void initMonstresTranchant() {
		updateMonstresDomaine();
		monstresTranchants = monstreDomaineSet.tailSet(new Monstre<Glace>("zzzz", 0, null, Domaine.GLACE, (Glace[] )null) , false);
	}
	
	
}
