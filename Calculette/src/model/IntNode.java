package model;

public interface IntNode {
	public void addDot();
	public void addDigit(String digit);
	public Node addBinaryOperator(String operator);
	public Node addUnaryOperator(String operator);
	public String toString();
	public void eval();
	public void reset();
	public void error();
	public void notYet();
}
