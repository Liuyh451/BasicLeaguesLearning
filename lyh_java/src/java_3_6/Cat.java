package java_3_6;

public class Cat extends Animal {
	String name;
	Cat(String b){
		name=b;
	}
	public void cry() {
	System.out.println("������");
	}
	public String getAnimalName() {
		return name;
	}

}
