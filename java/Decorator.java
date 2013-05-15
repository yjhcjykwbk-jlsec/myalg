class Base{
	Base(){}
	void work(){ System.out.println("something");}
}public class Decorator extends Base{
	Base b;
	Decorator(Base base){this.b=base;}
	void work(){b.work();}
}class Extend1 extends Decorator{
	Extend1(Base b){super(b);}
	void work(){  super.work(); System.out.println("somemore1");}
} class Extend2 extends Decorator{
	Extend2(Base b){super(b);}
	void work(){  super.work(); System.out.println("somemore2");}
}
  class Extend3 extends Decorator{
	Extend3(Base b){super(b);}
	void work(){  super.work(); System.out.println("somemore3");}
	
	
	//测试装饰功能：
	public static void main(String []args){
		Base b=new Base();//b.work();
		Base b1=new Extend1(b); b1.work();
		System.out.println("-------------");
		Base b2=new Extend2(b1); b2.work();
		System.out.println("-------------");
		Base b3=new Extend3(b2); b3.work();
		System.out.println("-------------");
		Base b32=new Extend1(b3); b32.work();
	}
}
//  something
//  somemore1
//  -------------
//  something
//  somemore1
//  somemore2
//  -------------
//  something
//  somemore1
//  somemore2
//  somemore3
//  -------------
//  something
//  somemore1
//  somemore2
//  somemore3
//  somemore1