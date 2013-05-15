
public class Clone4 extends Clone0 implements Cloneable{//必须实现这个接口，jvm才允许调用super隐藏的protected clone函数。
	public Clone4(String a, int b,String c,int d) {
		super(a, b);
		a3=d;s3=c;
		// TODO Auto-generated constructor stub
	}
	public Object clone(){//如果没有这个，c3.Clone将返回super.clone（）的结果。新增的c3.s3引用型成员变量得不到深拷贝。
		Clone4 res;
		try {
			res = (Clone4)super.clone();//super.clone因为Clone0没有实现clone，所以调用Object.clone,引用类型s1没有得到拷贝。
			res.s3=new String(s3);//重写使得当前类表的引用类型s3得到深拷贝
			return res;
		} catch (CloneNotSupportedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}
	int a3;
	String s3;
	public static void main(String[]args){
		Clone4 c3=new Clone4("worldhello",112,"extstr",700);
		Clone4 c4=(Clone4)c3.clone();
		System.out.println(c3==c4);
		System.out.println(".......");
		System.out.println(c3.s1==c4.s1);//s1从Clone0继承，没有实现深拷贝
		System.out.println(c3.a1==c4.a1);
		System.out.println(c3.s3==c4.s3);//s3实现了深拷贝
		System.out.println(c3.a3==c4.a3);
		System.out.println(".......");
		c3.a1=13123;
		System.out.println(c4.a1);
		c3.s1="fsafdsa";
		System.out.println(c3.s1+":"+c4.s1);
		c3.a3=133;
		System.out.println(c4.a3);
		c3.s3="aaaaaa";
		System.out.println(c3.s3+":"+c4.s3);//虽然结果都变了，但是过程有区别。
	}
}
