package Bank;

public class main1 {
	public  static void main(String args[]){
		ConstructionBank money1=new ConstructionBank();
		BankOfQingdao money2=new BankOfQingdao();
		CommercialBank money3=new CommercialBank();
		money1.savedMoney=50000;
		money1.year=5.216;
		money2.savedMoney=50000;
		money2.year=5.216;
		money3.year=8.236;
		money3.savedMoney=80000;
		System.out.println(Math.abs(money1.computerInterest()-money2.computerInterest()));
		System.out.println(String.format("%.2f", money3.computerInterest()));
	
	}

}
