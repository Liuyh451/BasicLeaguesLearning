package java_6_2;
import java.io.*;
import java.util.Scanner;
public class test2 {
	public static void main(String[] args) {
		
		try {
		Scanner ss=new Scanner(System.in);
		int n;
		n=ss.nextInt();
		String c=ss.next();
		
			BufferedWriter out=new BufferedWriter(new FileWriter("D:\\javagrade.txt"));
			String s1;
			for(int m=0;m<n;m++) {
				s1=ss.nextLine();
				out.write(s1);
				out.newLine();
			}
			out.close();
			ss.close();
			BufferedReader read=new BufferedReader(new FileReader("D:\\javagrade.txt"));
			String line=read.readLine();
			String grade[][]=new String[n][];
			int i=0;
			while(line!=null) {
				grade[i]=line.split(" ");
				line=read.readLine();//¶ÁÏÂÒ»ÐÐ
				i++;
			}
			read.close();
			int max1=Integer.parseInt(grade[0][1]);
			int f=0;
			int min1=Integer.parseInt(grade[0][1]);
			int s=0;
			for (int p=0;p<n;p++) {
				
					if(Integer.parseInt(grade[p][1])>max1) {
						max1=Integer.parseInt(grade[p][1]);
						f=p;
						
					}
					if(Integer.parseInt(grade[p][1])<min1) {
						min1=Integer.parseInt(grade[p][1]);
						s=p;
					}
					
			}
			System.out.println(grade[f][1]);
			System.out.println(grade[s][1]);
				
					
		}
		catch(Exception e) {
			e.printStackTrace();
		}
	}
}

