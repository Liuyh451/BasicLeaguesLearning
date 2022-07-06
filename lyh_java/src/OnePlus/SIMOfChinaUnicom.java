package OnePlus;

public class SIMOfChinaUnicom extends SIM {
	   String Number;
	   
		public void setNumber(String n) {
			Number=n;
			
		}
		public String giveNumber() {
			return Number;
		}
		public String giveCorpName() {
			return "ChinaUnicom";
		}

}
