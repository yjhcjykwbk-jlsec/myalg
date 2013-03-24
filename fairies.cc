#include <iostream>
#include <map>

using namespace std;
#define rep0(i,n) for(int i=0;i<n;i++)  //[0,n)
#define rep(i,m,n) for(int i=m;i<n;i++) //[m,n)
#define tep0(i,m) for(int i=m;i>0;i--)  //[m.0)
#define tep(i,m,n) for(int i=m;i>n;i--) //[m.n)
//ENDTEMPLATE_BY_ACRUSH_TOPCODER
struct num_10;
#define MAXN 3000
struct num_2{
	int a[MAXN];
	int len;
	num_2(const num_10 &s);
	num_2(){
		a[0]=0;len=1;
	}
	num_2(int n){
		a[0]=n; len=1; adjust(); reverse();
	}
	void reverse(){
		//颠倒
		rep(i,0,len/2) {
			int tmp=a[len-i-1];
			a[len-i-1]=a[i];a[i]=tmp;
		}
	}void adjust(){
		int n=0,i;//从0到高位调整
		for(i=0;i<len||n>0;i++){
			if(i<len) n+=a[i];
			a[i]=n%2;
			n/=2;
		}
		len=i;
	}
	void simplify(){//去掉开头的0
		int i;for(i=0;i<len;i++) if(a[i]!=0) break;
		if(i>=len) len=1;//0
		if(i>0&&i<len) {
			for(int j=i;j<len;j++) a[j-i]=a[j];
			len=len-i;
		}
	}
	bool operator < (const num_2 &b){
		if(len!=b.len) return len<b.len;
		for(int i=0;i<len;i++){
			if(a[i]!=b.a[i]) return a[i]<b.a[i];
		}
		return false;
	}
	bool operator <= (const num_2 &b){
		if(len!=b.len) return len<b.len;
		for(int i=0;i<len;i++){
			if(a[i]!=b.a[i]) return a[i]<b.a[i];
		}
		return true;
	}
	void operator += (int b){
		reverse();a[0]+=b;adjust();reverse();	
	}
	num_2 operator + (int b){
		num_2 tmp(*this);
		tmp.reverse();tmp.a[0]+=b;tmp.adjust();tmp.reverse();
		return tmp;
	}
	num_2 substr(int l,int r){
		num_2 tmp;
		if(l>=r) return tmp;
		for(int i=l;i<r;i++) tmp.a[i-l]=a[i];
		tmp.len=r-l;
		return tmp;
	}
	num_2 operator -(const num_2 & _b){
		num_2 b(_b);
		num_2 tmp; reverse(); 
		b.reverse();
		int c=0;
		for(int i=0;i<len&&i<b.len;i++){
			tmp.a[i]=(a[i]+c-b.a[i]+2)%2;
			if(a[i]+c<b.a[i])  c=-1;
			else c=0;
		}
		for(int i=b.len;i<len;i++) {
			tmp.a[i]=(a[i]+c+2)%2;
			if(a[i]+c<0) c=-1;
			else c=0;
		}
		reverse();b.reverse();
		tmp.len=len;
		tmp.reverse();
		tmp.simplify();
		if(c==-1){
			cout<<*this<<endl<<b<<endl<<tmp<<endl;
			assert(c!=-1);
		}
		return tmp;
	}
	friend	num_2 getCha( num_2 &a, num_2 &b){
		if(a<b) return b-a;
		return a-b;
	}
	friend ostream& operator<<(ostream &os,const num_2& s){
		rep(i,0,s.len) os<<s.a[i];
		return os;
	}
	//如果a是b的某个前缀，或者a是b的某个前缀+1，返回
}m_2,n_2;
struct num_10{
	int a[MAXN];
	int len;
	void reverse(){
		//颠倒
		rep(i,0,len/2) {
			int tmp=a[len-i-1];
			a[len-i-1]=a[i];a[i]=tmp;
		}
	}
	num_10(){//从十进制字符串转
		len=1;a[0]=0;
	}
	num_10(char *s){//从十进制字符串转
		int slen=strlen(s);
		rep(i,0,slen)
			a[i]=s[slen-i-1]-'0';
		len=slen;
		reverse();
	}
	num_10(const num_2 &b){//从2进制转10进制
		len=1;a[0]=0;
		for(int i=0;i<b.len;i++){
			if(b.a[i]==1) add1();
			if(i<b.len-1) mul2();
		}
	}
	bool isZero(){return len==0||a[0]==0;}
	void simplify(){//去掉开头的0
		int i;for(i=0;i<len;i++) if(a[i]!=0) break;
		if(i>=len) len=1;//0
		if(i>0&&i<len) {
			for(int j=i;j<len;j++) a[j-i]=a[j];
			len=len-i;
		}
	}
	int div2(){
		int c=0;
		for(int i=0;i<len;i++){
			a[i]+=c*10;
			c=(a[i]%2);a[i]/=2;
		}
		simplify();
		return c;
	}
	void adjust(){
		int i,c=0;for(i=0;i<len||c>0;i++){
			if(i<len) c+=a[i];
			a[i]=c%10,c/=10;
		}
		len=i;
	}
	void mul2(){
		int c=0;
		reverse();
		for(int i=0;i<len;i++){
			a[i]*=2;
		}
		adjust();
		reverse();
	}
	void add1(){
		int c=1, i;
		for(i=len-1;i>=0;i--){
			c+=a[i];
			a[i]=c%10;c/=10;
			if(c==0) break;
		}
		if(i<0){
			len++;a[0]=1;a[len-1]=0;
		}
	}
	friend ostream& operator<<(ostream &os,const num_10& s){
		rep(i,0,s.len) os<<s.a[i];
		return os;
	}
}m_10,n_10;

num_2::num_2(const num_10 &s)
{//从十进制转
	num_10 tmp=s;
	int c=0;
	rep(i,0,MAXN){
		c=tmp.div2();	
		a[i]=c;
		if(tmp.isZero()) {len=i+1;break;}
	}
	reverse();
}
int getLast(int start){
	int step=0;
	int onecnt=0;
	for(int pos=start;pos<n_2.len;pos++){
		if(n_2.a[pos]==0){
			step+=1;
			if(onecnt>2) step+=1+onecnt+1;//+1 *2(cnt) -1 
			else step+=onecnt*2;//*2  +1
			onecnt=0;
		}
		else onecnt++;
	}
	if(onecnt>2) step+=1+onecnt+1;//+1 *2(cnt) -1
	else step+=onecnt*2;//*2 +1
	return step;
}
int getLast1(int start){
	int pos=start;
	int onecnt=0;
	if(pos==n_2.len) return 1; //-1
	for(;pos<n_2.len;pos++){
		if(n_2.a[pos]==0){
			//	if(onecnt<=0) return getLast(pos+1)+2*onecnt+2; //-1 (*2 +1)(cnt) *2
			return getLast(pos+1)+onecnt+2;   //*2(cnt) -1 *2
		}
		else onecnt++;
	}
	return onecnt+1;
}
num_10 f(){
	if(n_2<m_2) return getCha(m_2,n_2);
	num_10 temp;
	//匹配到mlen
	int pos=m_2.len;
	num_2 tmp=n_2.substr(0,m_2.len);
	num_2 step1;
	if(m_2<=tmp) {
		step1=tmp-m_2;
		cout<<"1 # match to "<<tmp<<", needs "<<step1<<"="<<(temp=step1)<<" steps"<<endl;
		step1+=getLast(pos);
		cout<<"then needs "<<getLast(pos)<<" steps"<<endl;
	}
	else {
		tmp=tmp+1;
		step1=m_2-tmp;
		cout<<"1 # match to "<<tmp-1<<", needs "<<step1<<"="<<(temp=step1)<<" steps"<<endl;
		step1+=getLast1(pos);
		cout<<"then needs "<<getLast1(pos)<<" steps"<<endl;
	}

	// 匹配到mlen-1
	pos=m_2.len-1;
	tmp=n_2.substr(0,m_2.len-1)+1;
	num_2 step2=m_2-tmp;//
	cout<<"2 # match to "<<tmp-1<<", needs "<<step2<<"="<<(temp=step2)<<" steps"<<endl;
	step2+=getLast1(pos);
	cout<<"then needs "<<getLast1(pos)<<" steps"<<endl;

	// 匹配到mlen+1
	if(n_2.len>m_2.len){
		pos=m_2.len+1;
		tmp=n_2.substr(0,m_2.len+1);
		num_2 step3=tmp-m_2;
		cout<<"3 # match to "<<tmp<<", needs "<<step3<<"="<<(temp=step3)<<" steps"<<endl;
		step3+=getLast(pos);
		cout<<"then needs "<<getLast(pos)<<" steps"<<endl;
		if(step3<step1&&step3<step2) { cout<<"#3"<<endl;return step3;}
	}
	if(step1<step2){ cout<<"#1"<<endl;return step1;}
	else{ cout<<"#2"<<endl;return step2;}
}
int main(){
	char m_str[MAXN],n_str[MAXN];
	while(true){
		scanf("%s %s",&n_str,&m_str);
		n_10=n_str;m_10=m_str;
		if(n_10.isZero()&&m_10.isZero()) break;
		n_2=n_10;m_2=m_10;
		m_10=m_2;n_10=n_2;
		cout<<"m:"<<m_2<<"="<<m_10<<endl<<"n:"<<n_2<<"="<<n_10<<endl;
		cout<<"from "<<m_10<<" to "<<n_10<<" needs "<<f()<<" steps"<<endl;
		cout<<"=================================="<<endl;
	}
	//	cout<<n_10<<endl<<m_10<<endl;
	//	##test num_2 num_10
	//	char ss[1000];
	//	cin>>ss;
	//	cout<<"ss:"<<ss<<endl;
	//	n_10=(ss);
	//	cout<<n_10<<endl;
	//	n_10.div2();
	//	cout<<n_10<<endl;
	//	n_2=n_10;
	//	cout<<n_2<<endl;
	return 0;
}
