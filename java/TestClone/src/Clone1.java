import java.util.concurrent.Callable;


public class Clone1  implements Cloneable{  //这个空接口声明不能少，否则clone报exception
	public String s1;
	public int a1;
	public static void main(String[]args){
		Clone1 c1=new Clone1();
		c1.s1="str1";
		c1.a1=1;
		Clone1 c2;
		try {
			c2=c1;//纯粹浅拷贝，没有调用Object的clone函数。
			System.out.println(c1==c2);
			System.out.println(c1.s1==c2.s1);
			c1.s1="str2";
			System.out.println(c2.s1);
			c1.a1=2;
			System.out.println(c1.a1==c2.a1);
			
			System.out.println("........................");
			c2 = (Clone1)c1.clone();
			System.out.println(c1==c2);
			System.out.println(c1.s1==c2.s1);//引用类型的成员变量s1没有得到深拷贝。
			c1.s1="anotherstr";
			System.out.println(c2.s1);
			c1.a1=3;
			System.out.println(c1.a1==c2.a1);//数据类型的成员变量a1得到了深拷贝。
		} catch (CloneNotSupportedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
	}

}
