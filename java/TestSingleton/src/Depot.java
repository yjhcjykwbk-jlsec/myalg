import java.util.HashMap;
import java.util.Map;
//单例仓库
public class Depot {
	private static Depot depot;
	private static Map<Phone,Integer> reserve;//库存
	public static synchronized Depot getInstance(){
		if(depot==null){
			depot=new Depot();
		}
		return depot;
	}
	private Depot(){
		reserve=new HashMap<Phone,Integer>();
		reserve.put(new Phone("nokia","n95","red"),4);
		reserve.put(new Phone("apple","iphone","black"),3);
	}
	public synchronized static Phone getPhone(String band,String series,String color){
		Phone phone=new Phone(band,series,color);
		if(reserve.containsKey(phone)&&reserve.get(phone)>0){
			reserve.put(phone,reserve.get(phone)-1);
			return phone;
		}
		return null;
	}
	public static void main(String []args){
		Phone phone=Depot.getInstance().getPhone("nokia", "n95", "red");
		System.out.println(phone.band+":"+phone.series+":"+phone.color);
	}
}
class Phone {
	String band;String series;String color;
	Phone(String a,String b,String c){
		band=a;series=b;color=c;
	}
	//注意了：必须重载equals和hashCode方法，才能够让reserve.containsKey(phone)得到正确结果，不然containsKey默认equals为a==b(指针值相等）
	//Hashmap.containsKey（obj）首先计算i=obj.hashCode(),然后在相应hash[i]这个链表里依次比较hash[i].element[j].equals(obj),如果找到“相等”返回true
	public boolean equals(Object obj){
		Phone phone=(Phone)obj;
		if(band.equals(phone.band)&&
			series.equals(phone.series)&&
			  color.equals(phone.color))
			return true;
		return false;
	}
	public int hashCode(){
		return band.hashCode()&series.hashCode()&color.hashCode();
	}
	
}
