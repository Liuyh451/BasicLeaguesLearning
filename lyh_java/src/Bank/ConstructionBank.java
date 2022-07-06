package Bank;

public class ConstructionBank extends Bank {
		
	double year;
	double day;
	double interest1;
	double computerInterest() {
		super.year=(int)year;
		super.computerInterest();
		day=(year-(int)year)*1000;
		interest1=day*0.0001*savedMoney;
		interest=interest+interest1;
        return interest;

}
}
