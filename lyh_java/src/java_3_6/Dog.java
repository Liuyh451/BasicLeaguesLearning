package java_3_6;

public class Dog extends Animal {
	String name;
	Dog(String a){
		name=a;
	}
	public void cry() {
	System.out.println("������");
	}
	public String getAnimalName() {
		return name;
	}

}
