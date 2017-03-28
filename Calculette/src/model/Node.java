package model;

public class Node implements IntNode{
	
	private static enum Type {UNARY_OPERATOR, BINARY_OPERATOR, OPERAND, ERROR, NOTYET};
	
	private Type type;
	private double value;
	private String operand;
	private Operator operator;
	private Node left;
	private Node right;

	public Node() {
		this.type = Type.OPERAND;
	}
	
	public Node(String operand) {
		this.type = Type.OPERAND;
		this.operand = new String(operand);
	}
	
	public Node(String operator, Node left, Node right) {
		this.type = Type.BINARY_OPERATOR;
		this.left = left;
		this.right = right;
		this.operator = Operator.valueOf(operator);
	}

	public Node(String operator, Node left) {
		this.type = Type.UNARY_OPERATOR;
		this.left = left;
		this.right = null;
		this.operator = Operator.valueOf(operator);
	}

	public void addDot() {
		if (type==Type.OPERAND){
			if (this.operand==null)
				this.operand = "0.";
			else if (!this.operand.contains("."))
				this.operand += '.';
		}
		else if (type==Type.UNARY_OPERATOR){
			if (left != null)
				left.addDot();
		}
		else if (type==Type.BINARY_OPERATOR){
			if (right == null)
				right = new Node("0.");
			else
				right.addDot();
		}
	}

	public void addDigit(String digit) {
		if (type==Type.OPERAND){
			if ((this.operand==null) || (this.operand=="0"))
				this.operand = digit;
			else 
				this.operand += digit;
		}
		else if (type==Type.UNARY_OPERATOR){
			if (left != null)
				left.addDigit(digit);
		}
		else if (type==Type.BINARY_OPERATOR){
			if (right == null)
				right = new Node(digit);
			else
				right.addDigit(digit);
		}
	}

	public Node addBinaryOperator(String operator) {
		switch (type){
		case OPERAND:
			eval();
			return new Node(operator, this, null);
		case BINARY_OPERATOR:
			if (right != null){
				eval();
				return addBinaryOperator(operator);
			}
			else {
				error();
				return this;
			}
		case ERROR:
			return this;
		case UNARY_OPERATOR:
			eval();
			return addBinaryOperator(operator);
		default:
			break;
		}
		return this;
	}

	public Node addUnaryOperator(String operator) {
		switch (type){
		case OPERAND:
			eval();
			return new Node(operator, this);
		case BINARY_OPERATOR:
			if (right!=null){
				right = right.addUnaryOperator(operator);
				right.eval();
			}
			else
				error();
			return this;
		case UNARY_OPERATOR:
			eval();
			return addUnaryOperator(operator);
		case ERROR:
			return this;
		default:
			break;
		}
		return this;
	}

	public String toString(){
		String result="";
		switch (type) {
		case OPERAND:
			if (operand != null)
				result += operand;
			else
				result += String.valueOf(value);
			break;
		case BINARY_OPERATOR:		
			if (left != null)
				result += left.toString();
			result += operator.toString();
			if (right != null)
				result += right.toString();
			break;
		case UNARY_OPERATOR:
			result += operator.toString();
			if (left != null){
				if (left.value<0)
					result+="(";
				result += left.toString();
				if (left.value<0)
					result+=")";
			}
			break;
		case ERROR:
			result = "ERROR";
			break;
		case NOTYET:
			result = "NOT YET";
			break;
		default:
			break;
		}
		return result;
	}

	public void eval() {
		switch (type){
		case OPERAND:
			if (operand!=null){
				value = Double.parseDouble(operand);
				operand=null;
				}
			break;
		case UNARY_OPERATOR:
			if (left!=null){
				left.eval();
				value = operator.eval(left.value);
				type = Type.OPERAND;
				left = null;
				}
			break;
		case BINARY_OPERATOR:
			if (left!=null && right!=null){
				left.eval();
				right.eval();
				value = operator.eval(left.value, right.value);
				type = Type.OPERAND;
				left = null;
				right = null;
				}
			break;
		case ERROR:
			break;
		default:
			break;
		}
		
	}

	public void reset() {
		this.type=Type.OPERAND;
		this.value=0;
		this.operand="0";
		this.left=null;
		this.right=null;
	}

	public void error() {
		reset();
		this.type=Type.ERROR;
	}

	public void notYet() {
		reset();
		this.type=Type.NOTYET;
	}

}
