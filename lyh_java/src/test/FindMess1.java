package test;
interface Animal{
	void cry();
	String getAnimalName();
}
class Simulator{
	void playSound(Animal animal) {
		animal.cry();
		System.out.printf("%s",animal.getAnimalName());	
	}
}
class Dog implements Animal{
	public void cry() {
		System.out.printf("%s","wang");
	}
	public String getAnimalName() {
		return "dog";
	}
}
class Cat implements Animal{
	public void cry() {
		System.out.printf("%s","miao");
	}
	public String getAnimalName() {
		return "cat";
	}
}