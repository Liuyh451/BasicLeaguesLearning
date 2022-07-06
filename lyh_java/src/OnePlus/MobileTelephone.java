package OnePlus;

public class MobileTelephone {
	SIM card;
	public void useSIM(SIM card) {
		this.card=card;
	}
	public void showMess() {
		System.out.println("using card is :"+card.giveCorpName());
		System.out.println("telephone number is :"+card.giveNumber());
	}

}
