
///////////////////////////////////////////
/*
   * test math
   */
void initCa(vector<vector<int> >&a){
    if(a.size()<2) return ;
    int N=a.size();
    a[1][1]=a[1][0]=1;
    for(int i=2;i<N;i++) a[i][0]=1;
    for(int i=2;i<N;i++){
        for(int j=1;j<=i;j++){
            a[i][j]=a[i-1][j-1]+a[i-1][j];
        }
    }
}
int simca(int n,int m){
    static vector<vector<int> >s(1000,vector<int>(1000,0));
    static bool inited=false;
    int N=1000;
    if(!inited){
        initCa(s);
        inited=true;
    }
    if(n<m) return 0;
    assert(n>0&&n<N);
    return s[n][m];
}

int kpow(ll n,ll m){
    ll ans=1;
    n%=MOD;
    while(m>0){
        if(m&1) ans=(ans*n)%MOD;
        n=(n*n)%MOD;
        m>>=1;
    }
    return ans;
}
int _ca(ll n,ll m){
    if(n<m) return 0;
    ll ans=1;
    for(int i=1;i<=m;i++){
        ans=ans*((n+i-m)%MOD*kpow(i,MOD-2)%MOD)%MOD;
    }
    return ans;
}
// n=m=E(p^i*ai)
// C(n,m)%MOD=II(C(ai,bi))%MOD
int ca(ll n,ll m){
    if(n<m) return 0;
    if(m==0) return 1;
    return _ca(n%MOD,m%MOD)*ca(n/MOD,m/MOD)%MOD;
}
void test11(){
    ll x=pow(10,18);
    cout<<"pow 10,18:";
    cout<<x<<endl;
    /////test C(n,m)%MOD
    //test Lucas Principle on http://blog.csdn.net/acdreamers/article/details/8037918
    cout<<"ca(10,3):"<<ca(10,3)<<endl;	
    cout<<"ca(10,0):"<<ca(10,0)<<endl;	
    cout<<"ca(11,1):"<<ca(11,1)<<endl;	
    cout<<"ca(1,1):"<<ca(1,1)<<endl;	
    cout<<"ca(111111111111,1):"<<ca(111111111111,1)<<endl;	
    cout<<"ca(111111111111,0):"<<ca(111111111111,0)<<endl;	
    cout<<"ca(111111,111111):"<<ca(111111,111111)<<endl;	
    cout<<"ca(111111,111110):"<<ca(111111,111110)<<endl;	
    cout<<"ca(111111,111109):"<<ca(111111,111109)<<endl;	
    cout<<"assert =:"<< (ll)111111*111110/2%MOD<<endl;
    cout<<"ca(111111,111112):"<<ca(111111,111112)<<endl;	
    cout<<"simca(111,112):"<<simca(111,112)<<endl;	
    cout<<"simca(111,109):"<<simca(111,109)<<endl;	
    cout<<"simca(111,110):"<<simca(111,110)<<endl;	
}
