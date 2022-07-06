package java_3_4;

public class MonthWorker extends Employee {
	int month;
	double monthSalary;
	MonthWorker(int m,double s){
		month=m;
		monthSalary=s;
		
	}
	public double earnings() {
		return month*monthSalary;
	}

	

}
