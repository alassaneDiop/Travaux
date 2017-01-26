package view;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

import controller.*;

public class View implements IntView{
	
	private static View instance;
	
	public static View getInstance(){
		if (instance==null)
			instance = new View();
		return instance;
	}
	
	private JFrame frame;
	private JPanel panel, component;
	private JTextField textfield;
	private JButton[] buttons;
	
	private View(){
		frame = new JFrame();
		frame.setTitle("Calculette");
		frame.setSize(300, 400);
		frame.setResizable(false);
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		FlowLayout fl = new FlowLayout();
		fl.setHgap(16);
		fl.setVgap(16);
		panel = new JPanel(fl);
		frame.add(panel);
		component = new JPanel(new GridBagLayout());
		panel.add(component, BorderLayout.CENTER);
		
		GridBagConstraints c = new GridBagConstraints();
		textfield = new JTextField("");
		textfield.setHorizontalAlignment(JTextField.RIGHT);
		textfield.setEditable(false);
		textfield.setFont(new Font("SansSerif", Font.BOLD, 18));
		c.insets=new Insets(4, 4, 4, 4);
		c.gridx=0;
		c.gridy=0;
		c.gridwidth=GridBagConstraints.REMAINDER;
		c.gridheight=1;
		c.fill=GridBagConstraints.BOTH;
		c.anchor=GridBagConstraints.CENTER;
		component.add(textfield, c);
		
		buttons = new JButton[22];
		
		buttons[0] = new JButton("MC");
		buttons[0].setActionCommand("MC");
		c.gridy=1;
		c.gridwidth=1;
		component.add(buttons[0], c);	
		
		buttons[1] = new JButton("M+");
		buttons[1].setActionCommand("M+");
		c.gridx=1;
		component.add(buttons[1], c);	
		
		buttons[2] = new JButton("M-");
		buttons[2].setActionCommand("M-");
		c.gridx=2;
		component.add(buttons[2], c);	
		
		buttons[3] = new JButton("MR");
		buttons[3].setActionCommand("MR");
		c.gridx=3;
		component.add(buttons[3], c);	
		
		buttons[4] = new JButton("C");
		buttons[4].setActionCommand("C");
		c.gridx=0;
		c.gridy=2;
		component.add(buttons[4], c);	
		
		buttons[5] = new JButton("+/-");
		buttons[5].setActionCommand("UMINUS");
		c.gridx=1;
		component.add(buttons[5], c);	
		
		buttons[6] = new JButton("/");
		buttons[6].setActionCommand("DIV");
		c.gridx=2;
		component.add(buttons[6], c);	
		
		buttons[7] = new JButton("x");
		buttons[7].setActionCommand("MUL");
		c.gridx=3;
		component.add(buttons[7], c);	
		
		buttons[8] = new JButton("7");
		buttons[8].setActionCommand("7");
		c.gridx=0;
		c.gridy=3;
		component.add(buttons[8], c);	
		
		buttons[9] = new JButton("8");
		buttons[9].setActionCommand("8");
		c.gridx=1;
		component.add(buttons[9], c);	
		
		buttons[10] = new JButton("9");
		buttons[10].setActionCommand("9");
		c.gridx=2;
		component.add(buttons[10], c);	
		
		buttons[11] = new JButton("-");
		buttons[11].setActionCommand("MINUS");
		c.gridx=3;
		component.add(buttons[11], c);	
		
		buttons[12] = new JButton("4");
		buttons[12].setActionCommand("4");
		c.gridx=0;
		c.gridy=4;
		component.add(buttons[12], c);	
		
		buttons[13] = new JButton("5");
		buttons[13].setActionCommand("5");
		c.gridx=1;
		component.add(buttons[13], c);	
		
		buttons[14] = new JButton("6");
		buttons[14].setActionCommand("6");
		c.gridx=2;
		component.add(buttons[14], c);	
		
		buttons[15] = new JButton("+");
		buttons[15].setActionCommand("PLUS");
		c.gridx=3;
		component.add(buttons[15], c);	
		
		buttons[16] = new JButton("1");
		buttons[16].setActionCommand("1");
		c.gridx=0;
		c.gridy=5;
		component.add(buttons[16], c);	
		
		buttons[17] = new JButton("2");
		buttons[17].setActionCommand("2");
		c.gridx=1;
		component.add(buttons[17], c);	
		
		buttons[18] = new JButton("3");
		buttons[18].setActionCommand("3");
		c.gridx=2;
		component.add(buttons[18], c);	
		
		buttons[19] = new JButton("=");
		buttons[19].setActionCommand("=");
		c.gridx=3;
		c.gridheight=2;
		c.weighty=1;
		component.add(buttons[19], c);	
		
		buttons[20] = new JButton("0");
		buttons[20].setActionCommand("0");
		c.gridx=0;
		c.gridy=6;
		c.gridwidth=2;
		component.add(buttons[20], c);	
		
		buttons[21] = new JButton(",");
		buttons[21].setActionCommand(",");
		c.gridx=2;
		c.gridwidth=1;
		component.add(buttons[21], c);	
		
		frame.pack();
		frame.setVisible(true);
	}

	public void addActionListener(Controller controller) {
		for (JButton button : buttons)
			button.addActionListener(controller);
	}

	public void drawData(String dataToDraw){
		textfield.setText(dataToDraw);
	}
	
}
