//寻找有序数组中介于（L，U）的元素组成的区间
#include <iostream>
#include <map>
using namespace std;
int L,U;
typedef pair<int,int> Dis;
Dis merge(const Dis &s,const Dis&t){
	if(s.first==-1) return t;//左边为空区间
	else if(t.first==-1) return s;
	else return Dis(s.first,t.second);//合并区间
}
Dis getDistrict(int *a,int l,int r){
	if(l>r) return Dis(-1,-1); //empty district
	int mid=(l+r)/2;
	if(a[mid]<=L) return getDistrict(a,mid+1,r);
	if(a[mid]>=U) return getDistrict(a,l,mid-1);
	else{
		if(l==r) return Dis(l,l);
		Dis d1=getDistrict(a,l,mid);
		Dis d2=getDistrict(a,mid+1,r);
		Dis d=merge(d1,d2);
		return d;
	}
} 
int main(){
	int a[100];
	cin>>L>>U;
	int n;cin>>n;
	for(int i=0;i<n;i++) cin>>a[i];
	//for(int i=0;i<n;i++) cout<<a[i]<<" ";cout<<endl;
	Dis d=getDistrict(a,0,n-1);
	//cout<<L<<"----"<<U<<endl;
	cout<<d.first<<":"<<d.second<<endl;
	for(int i=d.first;i<=d.second;i++) cout<<a[i]<<" ";cout<<endl;
	return 0;
}
