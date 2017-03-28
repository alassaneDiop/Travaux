package com.calculatrice;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Button;
import android.view.View;
import android.util.Log;

public class Calcul extends Activity
{
	public TextView zoneAffichage;
	String texte = ""; // texte recupere le texte entre par l'utilisateur
	String buffer = ""; // buffer recupere les valeurs saisies
	PileEntier p1 = new PileEntier(20); // p1 est la pile des valeurs entieres saisies
	PileChar p2 = new PileChar(20); // p2 est la pile des signes

    // variable pour la rotation
    final String texteUser = "";
    final String bufferUser = "";
    
    @Override
    public void onSaveInstanceState(Bundle savedInstanceState) {

        savedInstanceState.putString(texteUser, zoneAffichage.getText().toString());
        savedInstanceState.putString(bufferUser, buffer);
        super.onSaveInstanceState(savedInstanceState);
    }


	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        if (savedInstanceState != null) {
            texte = savedInstanceState.getString(texteUser);
            buffer = savedInstanceState.getString(buffer);
            zoneAffichage = (TextView)findViewById(R.id.affichage);
            zoneAffichage.setText(texte.toString());
            
            if (p1.estVide()) {
                Log.v("vide", "");
            } else {
                Log.v("non vide", "");
            }

        } else {
            // setContentView(R.layout.main);
        }
	}

	public void clicReaction(View view)
	{		
		Bundle initialise = getIntent().getExtras();
		Button btn = (Button)view;
		texte = texte.concat(btn.getText().toString()); // texte concatene au texte du bouton presse
		buffer = buffer.concat(btn.getText().toString()); // buffer concatene au texte du bouton presse
		//affichage du texte entre
		zoneAffichage = (TextView)findViewById(R.id.affichage);
		zoneAffichage.setText(texte.toString());
	}

	public void Reset(View view)
	{
		Bundle initialise = getIntent().getExtras();
		zoneAffichage = (TextView)findViewById(R.id.affichage);

		texte = "";
		zoneAffichage.setText(texte);
		//on vide le contenu des piles
		p1 = null;	p2 = null;
		buffer = "";
	}

	public void Additionner(View view)
	{
		Bundle initialise = getIntent().getExtras();
		Button btn = (Button)view;
		texte = texte.concat(btn.getText().toString());

		if(p1 == null) p1 = new PileEntier(10);
		if(p2 == null) p2 = new PileChar(10);
		//on empile le nombre dans la pile des valeurs entieres
		if(buffer.equals(""))
			p1.empile(0); //empiler 0 si buffer est vide
		else{
			int e = Integer.parseInt(buffer); // caster la valeur de buffer en valeur entiere
			p1.empile(e); // empiler la valeur saisie dans la pile des valeurs entieres
		}
		
		buffer = "+"; // affecter le signe + a buffer
		char c = buffer.charAt(0);
		p2.empile(c); // on empile le signe + dans la pile des signes
		buffer = "";
		zoneAffichage = (TextView)findViewById(R.id.affichage);
		zoneAffichage.setText(texte.toString());
	}

	public void Soustraire(View view)
	{
		Bundle initialise = getIntent().getExtras();
		Button btn = (Button)view;
		texte = texte.concat(btn.getText().toString());

		if(p1 == null) p1 = new PileEntier(10);
		if(p2 == null) p2 = new PileChar(10);

		if(buffer.equals("")) {p1.empile(0);}
		else{int e = Integer.parseInt(buffer); p1.empile(e);}
		
		buffer = "+";
		//on empile le signe + dans sa pile
		char c = buffer.charAt(0);
		p2.empile(c);
		buffer = "-"; // affecter le signe - a buffer pour que la prochaine valeur saisie soit negative
		zoneAffichage = (TextView)findViewById(R.id.affichage);
		zoneAffichage.setText(texte.toString());
	}

	public void Calculer(View view)
	{
		Bundle initialise = getIntent().getExtras();
        int e = 0; // caster la valeur de buffer en valeur entiere
        if (!buffer.equals("")) {
            e = Integer.parseInt(buffer); // caster la valeur de buffer en valeur entiere
        }

		p1.empile(e); //empiler la valeur saisie dans la pile des valeurs entieres
		if(p1 != null && p2 != null){
			zoneAffichage = (TextView)findViewById(R.id.affichage);
			zoneAffichage.setText(Calculatrice.run(p1, p2)); // faire le calcul et afficher le resultat au niveau de la zone affichage
		}
		texte = ""; buffer = "";
	}
}
