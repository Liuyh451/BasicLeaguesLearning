package java_5_3;

public class commune{
	public static void main(String args[]){
		String mess="北京烤鸭:189元，西芹炒肉:12.9元，酸菜鱼:69元，铁板牛柳:32元";
		int index1=mess.indexOf("鸭")+2;
		int index2=mess.indexOf("肉")+2;
		int index3=mess.indexOf("鱼")+2;
		int index4=mess.indexOf("柳")+2;
		 String price1=mess.substring(index1,index1+3);
		 String price2=mess.substring(index2,index2+4);
		 String price3=mess.substring(index3,index3+2);
		 String price4=mess.substring(index4,index4+2);
		System.out.println("北京烤鸭:"+price1+"元");
		System.out.println("西芹炒肉:"+price2+"元");
		System.out.println("酸菜鱼:"+price3+"元");
		System.out.println("铁板牛柳:"+price4+"元");
		double price11=Double.parseDouble(price1);
		double price22=Double.parseDouble(price2);
		double price33=Double.parseDouble(price3);
		double price44=Double.parseDouble(price4);
		
		System.out.print("总价格为:");
		System.out.println(price11+price22+price33+price44);
		
	}
}