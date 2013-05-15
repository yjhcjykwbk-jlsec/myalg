
public class Clone5 {
	public static void main(String[]args){
	Integer[] ints=new Integer[]{1,2,3};
	Integer[] ints2=ints.clone();
	ints[1]=9999;
	System.out.println(ints2[1]);
	
//	SomeClass[] objs=new SomeClass[]{new SomeClass(1),new SomeClass(2),new SomeClass(3)};
//	SomeClass[] objs2=objs.clone();
//	objs[1].modify(777);
//	System.out.println(objs2[1].t);   //指针浅拷贝
//	System.out.println(objs[2]==objs2[2]);
	
	SomeClass2[] objs=new SomeClass2[]{new SomeClass2(1),new SomeClass2(2),new SomeClass2(3)};
	SomeClass2[] objs2=objs.clone();
	objs[1].modify(777);
	System.out.println(objs2[1].t);   //还是指针浅拷贝
	System.out.println(objs[2]==objs2[2]);
	}
 
}
class SomeClass{
	int t;
	SomeClass(int a){t=a;}
	void modify(int s){t=s;}
}
class SomeClass2 implements Cloneable{
	int t;
	SomeClass2(int a){t=a;}
	void modify(int s){t=s;}
	public Object clone(){
		try {
			return super.clone();
		} catch (CloneNotSupportedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
	}
}