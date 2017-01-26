package model;

public enum Operator {
	
	PLUS ("+"), 
	MINUS ("-"), 
	MUL ("x"), 
	DIV ("/"), 
	UMINUS ("-"), 
	NOP ("nop");
	
	private final String sign;
	
	Operator(String s) {
		sign = s;
	}
	
	public String toString(){
        return sign;
    }
	
	public double eval(double lvalue, double rvalue) {
		double value = 0;
		switch (this){
			case PLUS: value = lvalue + rvalue; break;
			case MINUS: value = lvalue - rvalue; break;
			case MUL: value = lvalue * rvalue; break;
			case DIV: value = lvalue / rvalue; break;
			default: break;
			}
		return value;		
	}

	public double eval(double lvalue){
		double value = 0;
		switch (this){
			case UMINUS: value = -lvalue; break;
			default: break;		
			}
		return value;
	}
}
