package attaque;

public abstract class ForceDeCombat {
	
	private String nom;
	private int pointDeDegat;
	protected boolean operationnel = true;
	
	public ForceDeCombat(int pointDeDegat, String nom) {
		this.pointDeDegat = pointDeDegat;
		this.nom = nom;
	}
	
	public int getPointDeDegat() {
		return pointDeDegat;
	}
	
	public String getNom() {
		return nom;
	}
	
	public boolean isOperationnel() {
		return operationnel;
	}
		
	
	@Override
	public String toString() {
		return "ForceDeCombat [nom=" + nom + ", pointDeDegat=" + pointDeDegat + "]";
	}

	public int utiliser() {
		return pointDeDegat;
	}
	
}