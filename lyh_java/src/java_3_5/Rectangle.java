package java_3_5;

public class Rectangle extends Figure {
	double length;
	double width;
	Rectangle(double a,double b){
		length=a;
		width=b;
	}
	public double area() {
		return length*width;
	}

}
