
public class Clone2 implements Cloneable{
	public String s1;
	public int a1;
	public Clone2(String a,int b){
		s1=a;a1=b;
	}
	protected Object clone(){
		try {
			Clone2 res = (Clone2) super.clone();//引用类型String s1还是没有被super（即Object）给复制过来。
			res.s1=new String(s1);//所以我们在重载clone方法的时候，需要对引用类型的成员变量进行处理：深拷贝。
			return res;
		} catch (CloneNotSupportedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}
	public static void main(String[]args){
		Clone2 c1=new Clone2("helloworld",442);
	 
		Clone2 c2;
		c2 = (Clone2)c1.clone();
		System.out.println(c1==c2);
		System.out.println(c1.s1==c2.s1);
		System.out.println(c1.a1==c2.a1);
	}

}

//class MyObject implements Cloneable{
//	int s;
//	public 
//}