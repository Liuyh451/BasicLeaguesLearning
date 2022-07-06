package java_5_2;
import java.util.*;

public class function {
	public char getMAX(String s) {
		char[] ar = s.toCharArray();
		Arrays.sort(ar);
		int no;
		no=ar.length-1;
		return ar[no];
	}

}
