package java_5_3;

public class commune{
	public static void main(String args[]){
		String mess="������Ѽ:189Ԫ�����۳���:12.9Ԫ�������:69Ԫ������ţ��:32Ԫ";
		int index1=mess.indexOf("Ѽ")+2;
		int index2=mess.indexOf("��")+2;
		int index3=mess.indexOf("��")+2;
		int index4=mess.indexOf("��")+2;
		 String price1=mess.substring(index1,index1+3);
		 String price2=mess.substring(index2,index2+4);
		 String price3=mess.substring(index3,index3+2);
		 String price4=mess.substring(index4,index4+2);
		System.out.println("������Ѽ:"+price1+"Ԫ");
		System.out.println("���۳���:"+price2+"Ԫ");
		System.out.println("�����:"+price3+"Ԫ");
		System.out.println("����ţ��:"+price4+"Ԫ");
		double price11=Double.parseDouble(price1);
		double price22=Double.parseDouble(price2);
		double price33=Double.parseDouble(price3);
		double price44=Double.parseDouble(price4);
		
		System.out.print("�ܼ۸�Ϊ:");
		System.out.println(price11+price22+price33+price44);
		
	}
}