package view;

import controller.Controller;

public interface IntView {
	
	void addActionListener(Controller controller);
	void drawData(String dataToDraw);
		
}
