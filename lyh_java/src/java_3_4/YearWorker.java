package java_3_4;

public class YearWorker extends Employee {
	int year;
	double yearSalary;
	YearWorker(int y,double s){ //�����������깤��
		year=y;
		yearSalary=s;
	}
    public double earnings() {  //��д���󷽷�
		return year*yearSalary;
	}


}
