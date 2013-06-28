#include <iostream>
#include <vector>
using namespace std;
#define MAXN 1000
#define MAXP 1000
#define MAX 9999999
vector<int>Edges[MAXN];//邻接矩阵
int a[MAXN][MAXP];
int N,P,ROOT;
void calc(int c){//计算以c为根节点，得到P子树需要的剪枝次数
	int min[MAXP];
	bool first=true;//Ok*p*p
	for(int i=0;i<Edges[c].size();i++)//对子树进行归并
		calc(Edges[c][i]);

	if(Edges[c].size()==0){
		for(int i=2;i<=P;i++) a[c][i]=MAX;a[c][1]=0;
	}

	else{
		for(int i=0;i<Edges[c].size();i++){//对子树进行归并
			int t=Edges[c][i];
			if(first){
				a[c][0]=min[0]=1;//需要进行剪枝,所以为1
				for(int i=1;i<=P;i++) a[c][i]=min[i]=a[t][i];//第一个分支
				first=false;
				continue;
			}else{
				for(int i=0;i<=P;i++) min[i]++;//先和0归并,即对其剪枝
				for(int j=1;j<=P;j++){//再和其他归并
					if(a[t][j]<MAX){
						for(int k=0;k<=P-j;k++)
							if(a[c][k]+a[t][j]<min[k+j]) min[k+j]=a[c][k]+a[t][j];
					}
				}
				for(int i=0;i<=P;i++) a[c][i]=min[i];
			}
		}
		for(int i=P;i>=1;i--) a[c][i]=a[c][i-1];//加上自己
	}
}
int getmin(){
	int min=a[ROOT][P];
	for(int i=0;i<N;i++)
		min=(i!=ROOT&&a[i][P]+1<min)?a[i][P]+1:min;
	return min;
}
int main(){
	cin>>N>>P;
	int a,b;
	while(cin>>a>>b)
		Edges[a-1].push_back(b-1);	
	ROOT=0;
	calc(0);
	cout<<getmin()<<endl;
	return 0;
}
