package com.calculatrice;

import java.util.ArrayList;

public class PileChar
{
	private int pos; // position dans le tableau
	private char [] p;

	public PileChar () // creation d’une pile vide de taille 10
	{
		p = new char[10];
		pos = -1;
	}

	public PileChar (int taille) // creation d’un pile vide de taille donnee
	{
		p = new char[taille];
		pos = -1;
	}

	public void empile (char c)
	{
		p[++pos] = c;
	}

	public char depile ()
	{
		return p[pos--];
	}

	public char sommet ()
	{
		return p[pos];
	}

	public boolean estVide ()
	{
		return pos < 0;
	}
}
