package java_5_1;

public class FindMess {
	public static void main(String args[]){

        String mess="���������� ����ʱ�䣺1989.10.16��������վ��http://www.zhang.com����ߣ�185cm�����أ�72kg";

        int index= mess.indexOf("��");  //mess����indexOf(String s)���������ַ������״γ���ð�ŵ�λ��

        String name=mess.substring(index+1);

        if(name.startsWith("��")){

                System.out.println("�����е�������\"��\" ");

        }

        index=mess.indexOf("��",8);  //mess����indexOf(String s,int start)�����ַ����е�2�γ���ð�ŵ�λ��

        String date=mess.substring(index+1,index+11);

        System.out.println(date);

        index=mess.indexOf("��",index+1);

        int heightPosition=mess.indexOf("���",10); //mess����indexOf(String s)�����ַ������״γ�����ߵ�λ��

String personNet=mess.substring(index+1,heightPosition-1);

System.out.println(personNet);

index=mess.indexOf("��",48); //mess����indexOf(String s,int start)�����ַ�������ߺ����ð��λ��

int cmposition=mess.indexOf("cm");

String height=mess.substring(index+1,cmposition);

height=height.trim();

int h=Integer.parseInt(height);

if(h>=180){

System.out.println("�����е����"+height+"���ڻ����180cm");

}

else {

System.out.println("�����е����"+height+"С��180cm");

}

index=mess.indexOf("��",58); //mess����lastIndexOf(String s)�����ַ��������һ��ð�ŵ�λ��

int kgPosition=mess.indexOf("kg");

String weight=mess.substring(index+1,kgPosition);

weight=weight.trim();

int w=Integer.parseInt(weight);

if(w>=75){

System.out.println("�����е�����"+weight+"���ڻ����75kg");

}

else{

   System.out.println("�����е�����"+weight+"С��75kg");

}

}

}
