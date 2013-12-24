public class OverRide extends Test1 {// Test2
	public OverRide() {
	}
	public void method1() {
		System.out.println("test2++++++++++++");
	}
	public void method2(OverRide t) {
		System.out.println("test2.method2");
	}
//	public void method3(test t) {
//		System.out.println("test2.method3");
//	}

	public static void main(String arg[]) {

		test aa = new OverRide();
		aa.method1();
		Test1 bb=new Test1();
		aa.method2(bb);
		aa.method3(bb);
		if(aa instanceof OverRide){ System.out.println("aa is test2");}
		if(aa instanceof Test1){ System.out.println("aa is test1");}
		if(aa instanceof test){ System.out.println("aa is test");}
		if(bb instanceof OverRide){ System.out.println("bb is test2");}
		if(bb instanceof Test1){ System.out.println("bb is test1");}
		if(bb instanceof test){ System.out.println("bb is test");}
	}
}

class Test1 extends test {
	//overload
	public void method1() {
		System.out.println("test1+++++++++++++++");
	}
	//override
	public void method2(Test1 t) {
		System.out.println("test1.method2");
	}
	//overload
	public void method3(test t) {
		System.out.println("test1.method3");
	}
}

class test {
	public void method1() {
		System.out.println("test++++++++++++");
	}

	public void method2(test t) {
		System.out.println("test.method2");
	}
	
	public void method3(test t) {
		System.out.println("test.method3");
	}
}