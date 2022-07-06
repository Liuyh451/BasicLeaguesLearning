package Bank;

public class Bank {
	int savedMoney;
	int year;
	double interest;
	double computerInterest() {

        interest=year*0.035*savedMoney;

        return interest;

}
		
}
