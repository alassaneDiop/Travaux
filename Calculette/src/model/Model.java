package model;

public class Model implements IntModel {

	private static Model instance;
	private Node root;
	private String data;
	
	public static Model getInstance(){
		if (instance==null)
			instance = new Model();
		return instance;
	}
	
	private Model(){
		root=new Node();
		root.reset();
		data=root.toString();
	}
	
	public void executeCommand(String actionCommand) {
		switch (actionCommand){
		case "0": case "1": case "2": case "3": case "4": case "5": case "6": case "7": case "8": case "9":
			root.addDigit(actionCommand);
			break;
		case "PLUS": case "MINUS": case "MUL": case "DIV":
			root = root.addBinaryOperator(actionCommand);
			break;
		case "UMINUS":
			root = root.addUnaryOperator(actionCommand);
			break;
		case "=":
			root.eval();
			break;
		case "C":
			root.reset();
			break;
		case ",":
			root.addDot();
			break;
		default:
			root.notYet();
			break;
		}	
		data = root.toString();
	}

	public String getData() {
		return data;
	}
}
