package java_6_1;
import java.io.*;
public class test1 {
	
	
	public static void main(String args[]) {
	    try{
	        FileOutputStream out=new FileOutputStream("hello.txt");//����ָ���ļ�hello.txt�������       
	        FileInputStream in=new FileInputStream("hello.txt");
	        byte content[]="ABCDEFG".getBytes();//��������洢��һ���µ� byte ������
	        StringBuffer bufferOne=new StringBuffer();
	        StringBuffer bufferTwo=new StringBuffer();
	        int m=-1;
	        byte tom[]=new byte[3];
	        out.write(content);
	        out.close();
	        while((m=in.read(tom,0,3))!=-1){//����read������Դ�ж�ȡ3���ֽڵ��ֽ�����tom�У�����0��ʼ���

	            String s1=new String(tom,0,m);//String����ȡtom��0��m���ֽڷ���һ���µ��ַ�����
	            bufferOne.append(s1);
	            String s2=new String(tom,0,3);//String����ȡtom��0��3���ֽڷ���һ���µ��ַ�����
	            bufferTwo.append(s2);
	        }
	        in.close();
	        System.out.println(bufferOne);
	        System.out.println(bufferTwo);
	    }
	    catch(IOException e){}
	}
	}



