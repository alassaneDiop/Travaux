package controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import view.*;
import model.*;

public class Controller implements ActionListener {
	
	private static Controller instance;
	private View view;
	private Model model;

	private Controller(){
		this.view = View.getInstance();
		this.model = Model.getInstance();
		view.drawData(model.getData());
		view.addActionListener(this);
	}
	
	public static Controller getInstance(){
		if (instance==null)
			instance = new Controller();
		return instance;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		model.executeCommand(e.getActionCommand());
		view.drawData(model.getData());
	}

}
