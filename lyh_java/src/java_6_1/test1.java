package java_6_1;
import java.io.*;
public class test1 {
	
	
	public static void main(String args[]) {
	    try{
	        FileOutputStream out=new FileOutputStream("hello.txt");//创建指向文件hello.txt的输出流       
	        FileInputStream in=new FileInputStream("hello.txt");
	        byte content[]="ABCDEFG".getBytes();//并将结果存储到一个新的 byte 数组中
	        StringBuffer bufferOne=new StringBuffer();
	        StringBuffer bufferTwo=new StringBuffer();
	        int m=-1;
	        byte tom[]=new byte[3];
	        out.write(content);
	        out.close();
	        while((m=in.read(tom,0,3))!=-1){//调用read方法从源中读取3个字节到字节数组tom中，并从0开始存放

	            String s1=new String(tom,0,m);//String方法取tom中0到m个字节返回一个新的字符数组
	            bufferOne.append(s1);
	            String s2=new String(tom,0,3);//String方法取tom中0到3个字节返回一个新的字符数组
	            bufferTwo.append(s2);
	        }
	        in.close();
	        System.out.println(bufferOne);
	        System.out.println(bufferTwo);
	    }
	    catch(IOException e){}
	}
	}



