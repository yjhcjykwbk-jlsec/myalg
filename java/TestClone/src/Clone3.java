
public class Clone3 extends Clone2 implements Cloneable{//必须实现这个接口，jvm才允许调用super隐藏的protected clone函数。
	public Clone3(String a, int b,String c,int d) {
		super(a, b);
		a3=d;s3=c;
		// TODO Auto-generated constructor stub
	}
	public Object clone(){//如果没有这个，c3.Clone将返回super.clone（）的结果。新增的c3.s3引用型成员变量得不到深拷贝。
		Clone3 res=(Clone3)super.clone();
		res.s3=new String(s3);//当前类表的引用类型
		return res;
	}
	int a3;
	String s3;
	public static void main(String[]args){
		Clone3 c3=new Clone3("worldhello",112,"extstr",700);
		Clone3 c4=(Clone3)c3.clone();
		System.out.println(c3==c4);
		System.out.println(".......");
		System.out.println(c3.s1==c4.s1);
		System.out.println(c3.a1==c4.a1);
		System.out.println(c3.s3==c4.s3);
		System.out.println(c3.a3==c4.a3);
	}
}
