package java_3_4;

public class WeekWorker extends Employee {
	int week;
	double weekSalary;
	WeekWorker(int w,double s){
		week=w;
		weekSalary=s;
	}
    public double earnings() {
		return week*weekSalary;
	}


}
