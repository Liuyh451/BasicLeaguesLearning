package java_3_5;

public class Triangle extends Figure {
	double bottom;
	double high;
	Triangle(double bottom,double high){
		this.bottom=bottom;
		this.high=high;
		
	}
	public double area() {
		return bottom*high/2;
	}

}
