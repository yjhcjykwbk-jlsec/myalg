#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
	cout<<"1"<<endl;
	for(int cases=0;cases<1;cases++){
		int n=random()%100;
		cout<<n<<" "<<n<<endl;
		for(int i=0;i<n;i++){
			int m=random()%10;
			cout<<m<<" ";
			for(int k=0;k<m;k++){
				int s=random()%n+1;	
				cout<<s<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
}
