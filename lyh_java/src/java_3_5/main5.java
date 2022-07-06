package java_3_5;

public class main5 {
	public static void main(String args[]) {
		Circle circle=new Circle(6.66);
		Rectangle rectangle=new Rectangle(4,20);
		Triangle triangle=new Triangle(12,20);
		System.out.println(String.format("%.2f", circle.area()));
		System.out.println(rectangle.area());
		System.out.println(triangle.area());
	}

}
