package java_3_6;

public class Simulator {
	Animal animal;
	public void playSound(Animal animal) {
		this.animal=animal;
		animal.cry();
		System.out.println(animal.getAnimalName());
		
	}
	

}
