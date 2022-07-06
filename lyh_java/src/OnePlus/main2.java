package OnePlus;

public class main2 {
	public static void main(String args[]) {
		MobileTelephone oneplus=new MobileTelephone();
		SIMOfChinaMobile card1=new SIMOfChinaMobile();
		SIMOfChinaUnicom card2=new SIMOfChinaUnicom();
		card1.setNumber("15093548547");
		card2.setNumber("15638714749");
		oneplus.useSIM(card1);
		oneplus.showMess();
		oneplus.useSIM(card2);
		oneplus.showMess();	
		
	}

}
