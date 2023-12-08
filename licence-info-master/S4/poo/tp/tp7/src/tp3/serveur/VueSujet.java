package tp3.serveur;

import java.io.Serializable;

public final class VueSujet implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int ref;
	private int x;
	private int y;
	private String nom;
	private String phrase;
	private int argent;
	private int TTL=60*10;	//10 minutes de duree de vie max
	
	public VueSujet(int ref, int x, int y, String nom, int argent, String phrase) {
		super();
		this.ref = ref;
		this.x = x;
		this.y = y;
		this.nom = nom;
		this.phrase = phrase;
		this.argent = argent;
	}
	


	private VueSujet(int ref, int x, int y, String nom, String phrase, int argent, int ttl) {
		// TODO Auto-generated constructor stub
		this.ref = ref;
		this.x = x;
		this.y = y;
		this.nom = nom;
		this.phrase = phrase;
		this.argent = argent;
		TTL = ttl;
	}



	public int getArgent() {
		return argent;
	}

	public String getNom() {
		return nom;
	}

	public String getPhrase() {
		return phrase;
	}

	public int getRef() {
		return ref;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	public void setX(int i) {
		x=i;
	}

	public void setY(int i) {
		y=i;
	}
	
	public int getTTL() {
		return TTL;
	}
	
	public void decrTTL() {
		if (TTL>0) TTL--;
	}

	public void setPhrase(String s) {
		phrase=s;
	}

	public void setArgent(int argent) {
		this.argent = argent;
	}
	
	public VueSujet clone() {
		return new VueSujet( ref,  x,  y,  nom, phrase, argent, TTL);
	}
}
