#include <iostream>
#include <cstdlib>
using namespace std;
int main(){
	int n=64;
	srand(time(NULL));
	cout<<n<<endl;
	for(int i=1;i<=n;i++)
		cout<<rand()%40+1<<" ";
	cout<<endl;
	return 0;
}
