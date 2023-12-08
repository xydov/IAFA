package attaque;

public class Arc extends Arme{
	
	private int nbFlechesRestantes;
		
	public Arc(int nbFlechesRestantes) {
		super(50, "Arc");
		this.nbFlechesRestantes = nbFlechesRestantes;
	}
	
	public int utiliser() {
		
		if (operationnel) {
			nbFlechesRestantes -= 1;
			if (nbFlechesRestantes == 0) {
				operationnel = false;
			}
		}
		return 50;
	}
}
