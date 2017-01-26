package com.calculatrice;

public class ElementPileChar
{
	private char val;
	
	public ElementPileChar () {
		this.val = '\0';
	}

	public ElementPileChar (char val) {
		this.val = val;
	}

	public char getValue () {
		return val;
	}

	public void affiche () {
		System.out.print (" "+val);
	}
}
