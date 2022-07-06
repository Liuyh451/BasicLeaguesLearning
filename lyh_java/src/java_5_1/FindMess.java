package java_5_1;

public class FindMess {
	public static void main(String args[]){

        String mess="姓名：张三 出生时间：1989.10.16。个人网站：http://www.zhang.com。身高：185cm，体重：72kg";

        int index= mess.indexOf("：");  //mess调用indexOf(String s)方法返回字符串中首次出现冒号的位置

        String name=mess.substring(index+1);

        if(name.startsWith("张")){

                System.out.println("简历中的姓名姓\"张\" ");

        }

        index=mess.indexOf("：",8);  //mess调用indexOf(String s,int start)返回字符串中第2次出现冒号的位置

        String date=mess.substring(index+1,index+11);

        System.out.println(date);

        index=mess.indexOf("：",index+1);

        int heightPosition=mess.indexOf("身高",10); //mess调用indexOf(String s)返回字符串中首次出现身高的位置

String personNet=mess.substring(index+1,heightPosition-1);

System.out.println(personNet);

index=mess.indexOf("：",48); //mess调用indexOf(String s,int start)返回字符串中身高后面的冒号位置

int cmposition=mess.indexOf("cm");

String height=mess.substring(index+1,cmposition);

height=height.trim();

int h=Integer.parseInt(height);

if(h>=180){

System.out.println("简历中的身高"+height+"大于或等于180cm");

}

else {

System.out.println("简历中的身高"+height+"小于180cm");

}

index=mess.indexOf("：",58); //mess调用lastIndexOf(String s)返回字符串中最后一个冒号的位置

int kgPosition=mess.indexOf("kg");

String weight=mess.substring(index+1,kgPosition);

weight=weight.trim();

int w=Integer.parseInt(weight);

if(w>=75){

System.out.println("简历中的体重"+weight+"大于或等于75kg");

}

else{

   System.out.println("简历中的体重"+weight+"小于75kg");

}

}

}
