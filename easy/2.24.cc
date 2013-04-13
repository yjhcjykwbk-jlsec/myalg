//螺栓螺母配对的程序
#include <iostream>
#include <assert.h>
using namespace std;
struct luosi{ //螺栓
	int size; 	//大小
	friend  ostream & operator <<( ostream &os,const luosi& t){
		os<<" size:"<<t.size;
		return os;
	}
};
struct luomu{ //螺母
	int size; 
	int num;
	luosi * t;//当螺母找到螺栓以后,保存指针到t	
	luomu(){ size=-1;t=NULL;}
	luomu(int n){ num=n;size=-1;t=NULL;}
};
//功能：螺母和螺栓进行比较匹配
//返回:-1：螺母太大 1：螺母太小 0：刚好合适
int cmp(const luomu& s,const luosi &t){
	if(s.size<t.size) return -1;
	else if(s.size>t.size) return 1;
	return 0;
}
//交换两个数组元素
void swap(luomu *lm,int a,int b){
	luomu tmp=lm[a];lm[a]=lm[b],lm[b]=tmp;
}

//区间树
//功能：使用区间树记录多个螺母数组的下标区间
//			给定螺栓，可以二分查找对应的螺母所在子区间
struct Node{
	int s;//自身的下标
	int l,r;//代表区间
	Node *lp,*rp;//左右子节点
	Node(){l=r=s=-1;lp=rp=NULL;}
	Node(int a,int b,int c){l=a,r=b,s=c;lp=rp=NULL;}
};
typedef Node* Tree;
//功能：给定螺栓，从树中二分查找到它对应螺母所落在的区间
Node *findNode(Tree tree,luomu *lm,const luosi &s){
	while(true){
		if(tree->s==-1)
			return tree;
		if(cmp(lm[tree->s],s)<0) tree=tree->rp;
		else tree=tree->lp;
	}
	return NULL;
}

//功能：给定螺栓，找到对应螺母，并将该螺母所在区间划分成左右子区间
//			其中左区间螺母都比该螺栓小，右区间反之
void find_div(Tree tree,luomu *lm,luosi *ps){
	//将比*ps大的螺母放到右边，比*ps小的放到左面
	Node *parent=findNode(tree,lm,*ps);
	int l=parent->l,r=parent->r;
	int lp=l,rp=r;
	int p=-1;
	//	for(int i=l;i<=r;i++) cout<<lm[i].size<<" ";cout<<endl;
	while(lp<=rp){
		while(lp<=r&&cmp(lm[lp],*ps)<=0){//lp指向比×ps大的element
			if(cmp(lm[lp],*ps)==0) p=lp;
			lp++;
		}
		while(rp>=l&&cmp(lm[rp],*ps)>=0){//rp指向比×ps小的element
			if(cmp(lm[rp],*ps)==0) p=rp;
			rp--;
		}
		if(lp<rp) swap(lm,lp,rp);
	}
	assert(p!=-1);
	lm[p].t=ps;//保存该螺丝的指针到对应螺母中
	if(p>=l&&p<=rp) swap(lm,p,rp);
	else if(p>=rp+1&&p<=r) swap(lm,p,rp+1),rp=rp+1;
	//	cout<<"left: "<<l<<":"<<rp-1<<"##"; //	for(int i=l;i<rp;i++) cout<<lm[i].size<<" ";cout<<endl;
	//	cout<<"right: "<<rp+1<<":"<<r<<"##"; //	for(int i=rp+1;i<=r;i++) cout<<lm[i].size<<" ";cout<<endl;

	//区间树的节点parent产生两个新的子节点，记录划分出来的左右区间
	parent->s=rp;parent->lp=new Node(l,rp-1,-1);parent->rp=new Node(rp+1,r,-1);
}	
int main(){
	luomu lm[100];luosi ls[100];
	int N;cin>>N;
	for(int i=0;i<N;i++) cin>>lm[i].size,lm[i].num=i;
	for(int i=0;i<N;i++) cin>>ls[i].size;
	Tree tree=new Node(0,N-1,-1);//初始区间
	for(int i=0;i<N;i++)	find_div(tree,lm,&ls[i]);
	for(int i=0;i<N;i++) 
		cout<<"find lm "<<lm[i].num<< " size:"<<lm[i].size<<" match with luoshuan"<<*(lm[i].t)<<endl;
	return 0;
}

