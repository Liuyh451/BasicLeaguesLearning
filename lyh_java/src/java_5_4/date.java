package java_5_4;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

 
public class date {
	public static void main(String[] args) throws ParseException{
		Scanner input = new Scanner(System.in);
		String s1 = input.next();
		String s2 = input.next();
		input.close();
		SimpleDateFormat format = new SimpleDateFormat("yyyyMMdd");//�����������ڵĸ�ʽ
		Date date1 = format.parse(s1);
		Date date2 = format.parse(s2);
		if(date2.equals(date1)) {
			             System.out.println("�������ڵ���������ȫ��ͬ");
			        }
			         else if (date2.after(date1)) {
			            System.out.println("�ڶ�������С�ڵ�һ������");
			         }
			         else if (date2.before(date1)) {
			             System.out.println("�ڶ������ڴ��ڵ�һ������");
			        }
		
		int a = (int) ((date2.getTime() - date1.getTime()) / (1000 * 3600 * 24));
		System.out.println("���ڲ�Ϊ" + a+"��");
	}
	
	}
