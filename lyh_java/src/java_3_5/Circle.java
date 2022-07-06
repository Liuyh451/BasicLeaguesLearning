package java_3_5;

public class Circle extends Figure {
	double r;
	Circle(double r){
		this.r=r;
	}
	public double area() {
		return r*r*Math.PI;
	}

}
