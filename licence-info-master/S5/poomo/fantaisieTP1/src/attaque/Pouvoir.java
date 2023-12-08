package attaque;

public abstract class Pouvoir extends ForceDeCombat{

	private int nbUtilisationPouvoir;
	private int nbUtilisationPouvoirInitial;
	
	
	public Pouvoir(int pointDeDegat, String nom, int nbUtilisationPouvoir) {
		super(pointDeDegat, nom);
		this.nbUtilisationPouvoir = nbUtilisationPouvoir;
		this.nbUtilisationPouvoirInitial = nbUtilisationPouvoir;
	}
	
	public void regenererPouvoir() {
		nbUtilisationPouvoir = nbUtilisationPouvoirInitial;
	}
	
	public int utiliser() {
		nbUtilisationPouvoir -= 1;
		if (nbUtilisationPouvoir == 0) {
			operationnel = false;
		}
		return getPointDeDegat();
	}
}
