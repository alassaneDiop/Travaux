package com.calculatrice;

public class Calculatrice {

	// faire une fonction static pour qu'elle puisse etre accessible directement a partir du nom de la classe sans instancier un objet de la classe
	public static String run(PileEntier p1, PileChar p2) {
		while(!p2.estVide()){
			p2.depile();
			int x = p1.depile();
			int y = p1.depile();
			p1.empile(x+y);
		}
	return Integer.toString(p1.sommet());
	}
}
