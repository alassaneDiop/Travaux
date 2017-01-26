package com.calculatrice;

import java.util.ArrayList;

public class PileEntier
{
	private int pos; // position dans le tableau
	private int [] p;

	public PileEntier () // creation d’une pile vide de taille 10
	{
		p = new int[10];
		pos = -1;
	}

	public PileEntier (int taille) // creation d’un pile vide de taille donnee
	{
		p = new int[taille];
		pos = -1;
	}

	public void empile (int e)
	{
		p[++pos] = e;
	}

	public int depile ()
	{
		return p[pos--];
	}

	public int sommet ()
	{
		return p[pos];
	}

	public boolean estVide ()
	{
		return pos < 0;
	}
}
