//　instanceof有一些用处。比如我们写了一个处理账单的系统，其中有这样三个类
public class InstanceOf{
	public static void main(String args[]){
		Bill bill1=new PhoneBill(1);
		Bill bill2=new GasBill(1);
		InstanceOf t=new InstanceOf();
		System.out.println("bill1:"+t.calculate(bill1));
		System.out.println("bill2:"+t.calculate(bill2));
		System.out.println("bill1:"+t.calculate1(bill1));
		System.out.println("bill2:"+t.calculate1(bill2));
	}
	//　　在处理程序里有一个方法，接受一个Bill类型的对象，计算金额。假设两种账单计算方法不同，而传入的Bill对象可能是两种中的任何一种，所以要用instanceof来判断：
	public double calculate(Bill bill) {
		if (bill instanceof PhoneBill) {
			//计算电话账单
			return bill.price*1;
		}
		if (bill instanceof GasBill) {
			//计算燃气账单
			return bill.price*2;
		}
		else return 0;
	}
	//　　这样就可以用一个方法处理两种子类。
	//　　然而，这种做法通常被认为是没有好好利用面向对象中的多态性。其实上面的功能要求用方法重载完全可以实现，这是面向对象变成应有的做法，避免回到结构化编程模式。只要提供两个名字和返回值都相同，接受参数类型不同的方法就可以了：

	public double calculate1(Bill bill) {
		//计算电话账单
		return bill.onvisit();
	}
}
//　　所以，使用instanceof在绝大多数情况下并不是推荐的做法，应当好好利用多态。
class Bill {//省略细节
	public float price;
	Bill(float a){price=a;}
	public float onvisit(){return 0;}
}
class PhoneBill extends Bill {//省略细节
PhoneBill(float a){super(a);}
	public float onvisit(){return price*1;}
}
class GasBill extends Bill {//省略细节
GasBill(float a){super(a);}
	public float onvisit(){return price*2;}
}
