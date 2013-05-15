class Base{}
class Child extends Base{
	public static Base getO(){
		return new Child();
	}
 public static void main(String[] args){
  Base base=new Child();//上溯造型
  Child child=(Child)base;//下溯造型
	Base base1=getO();
	System.out.println(base1.getClass());
  Child child1=(Child)(base1);//抛出ClassCastException异常
 // String s=(String)(base1);//抛出ClassCastException异常
	try{
  Child s=(Child)(new Base());//抛出ClassCastException异常
	}catch(Exception e){
		e.printStackTrace();
	}
 }
}
