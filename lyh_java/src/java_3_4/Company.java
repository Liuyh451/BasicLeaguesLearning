package java_3_4;

public class Company {
	Employee[] em; //Employee作为成员
    Company(Employee[] em) { //构造函数
    	this.em=em;	
    } 
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Employee[] em=new Employee[3];
		em[0]=new YearWorker(12,12345.0); //上转型对象
		em[1]=new MonthWorker(18,8888.0);
		em[2]=new WeekWorker(66,666.0);
		
		double sum;
		sum=em[0].earnings()+em[1].earnings()+em[2].earnings();
		System.out.println("总工资为:"+sum);
 
	}


}
