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
		SimpleDateFormat format = new SimpleDateFormat("yyyyMMdd");//设置输入日期的格式
		Date date1 = format.parse(s1);
		Date date2 = format.parse(s2);
		if(date2.equals(date1)) {
			             System.out.println("两个日期的年月日完全相同");
			        }
			         else if (date2.after(date1)) {
			            System.out.println("第二个日期小于第一个日期");
			         }
			         else if (date2.before(date1)) {
			             System.out.println("第二个日期大于第一个日期");
			        }
		
		int a = (int) ((date2.getTime() - date1.getTime()) / (1000 * 3600 * 24));
		System.out.println("日期差为" + a+"天");
	}
	
	}
