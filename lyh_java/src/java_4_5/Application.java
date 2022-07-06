package java_4_5;

public class Application {
	public static void main(String[] args) {
		Machine m=new Machine();
		Goods goods=new Goods();
		String str []= {"boom","cat","kaisa","melon","ps4","ak47"};
		for(int i=0;i<str.length;i++) {
			goods.setName(str[i]);
			if(goods.getName().equals("boom")||goods.getName().equals("ak47")||goods.getName().equals("AK47")) {
				goods.setIsDanger(true);
			}
			else {
				goods.setIsDanger(false);
			} 
			try {
				m.Checkbag(goods);
			}
			catch(DangerException e) {
				System.out.print(goods.getName()+":");
				e.toShow();
			}
	}

}
}
