///注意三种概念：指针赋值（SomeClass a=b)，浅拷贝(Object.Clone),和深拷贝（类自己定义的Clone函数中的拷贝操作，在调用了super.clone的同时，一般递归着还把自己的引用类型成员变量给深拷贝出来。不过需要成员变量的类也支持clone，实在不支持的话就构造一个相同的东西。）

public class Clone0 {  //这个空接口声明不能少，否则clone报exception
	public String s1;
	public int a1;
	public Clone0(String a,int b){
		s1=a;a1=b;
	}
	public static void main(String[]args){
		Clone0 c1=new Clone0("str1",1);
		 
		Clone0 c2;
		try {
			c2=c1;//纯粹浅拷贝，没有调用Object的clone函数。
			System.out.println(c1==c2);
			System.out.println(c1.s1==c2.s1);
			c1.s1="str2";
			System.out.println(c2.s1);
			c1.a1=2;
			System.out.println(c1.a1==c2.a1);
			
			System.out.println("........................");
			c2 = (Clone0)c1.clone();
			System.out.println(c1==c2);
			System.out.println(c1.s1==c2.s1);
			c1.s1="anotherstr";
			System.out.println(c2.s1);//引用类型的成员变量s1没有得到深拷贝。
			c1.a1=3;
			System.out.println(c1.a1==c2.a1);//数据类型的成员变量a1得到了深拷贝。
		} catch (CloneNotSupportedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
	}

}
