package com.calculatrice;

public class ElementPile
{
	private int valeur;
	
	public ElementPile () {
		this.valeur = 0;
	}

	public ElementPile (int valeur) {
		this.valeur = valeur;
	}

	public int getValue () {
		return valeur;
	}

	public void affiche () {
		System.out.print (" "+valeur);
	}
}
