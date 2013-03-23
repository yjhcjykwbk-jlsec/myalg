#include <iostream>
#include <vector>
using namespace std;
class Craft;
enum Color{Red=0,Blue};
class Comander{
	public:
		int next;//下一个制造什么
		static int craftLife0[5];
		int craftNum[5];
		static int getDragonLife(){return craftLife0[0];}
		static int getNinjaLife(){return craftLife0[1];}
		static  int getIcemanLife(){return craftLife0[2];}
		static  int getLionLife(){return craftLife0[3];}
		static  int getWolfLife(){return craftLife0[4];}
		Color color;//阵营
		int startNum;//编号
		vector<Craft*> crafts;
		int lifeEle; //生命元个数
		const char *getColor(){
			if(color==Red) return "red";
			return "blue";
		}
		Comander(Color _color,int m){
			startNum=0;this->color=_color;lifeEle=m;
			for(int i=0;i<5;i++) craftNum[i]=0;
		}
		void addCraft(Craft* pCraft);
		Craft* makeCraft();
		int getCraftNum(int i){return craftNum[i];}
};
int Comander::craftLife0[5]={0,1,2,3,4};
class Craft{
	protected:
		int number;
		Comander *cmd;//阵营
		int life;//生命值
	public:
		static const int craftType=-1;
		Craft(Comander *comander,int num,int life):cmd(comander),number(num),life(life){
			comander->lifeEle-=this->life;//每生成一个Craft，将消耗总部生命元
		}
		Craft():cmd(NULL),life(0),number(-1){}
		virtual int getCraftType(){return craftType;}	
		const char *getCraftName(){
			switch(getCraftType()){
				case(0): return "dragon";break;
				case(1):return "ninja";break;
				case(2):return "iceman";break;
				case(3):return "lion";break;
				case(4):return "wolf";break;
				default:return "";
			}
		}
		virtual void introduce(){
			cout<<cmd->getColor()<<" "<<getCraftName()<<" "<<number<<" born with strength "<<life<<","<<cmd->getCraftNum(getCraftType())<<" "<<getCraftName()<<" in "<<cmd->getColor()<<" headquarter"<<endl;
		}
};
class Arm{
	public:
		Arm(){}
		virtual const	char *getName(){
			return "arm";
		}
};
class Sword :public Arm{
	public: 
		const char *getName(){return "sword";}
};
class Bomb :public Arm{
	public: 
		const char *getName(){return "bomb";}
};
class Arrow :public Arm{
	public:
		const char *getName(){return "arrow";}
};
class ArmFactory{
	public:
		static Arm* getArm(int num){
			switch(num){
				case(0): return new Sword();
				case(1): return new Bomb();
				case(2): return new Arrow();
				default: return new Arm();
			}
		}
};
class Dragon:public Craft{ 
	private:
		Arm* pArm;
		float morale;//士气
	public:
		static const int craftType=0;
		Dragon(Comander* cmd,int num,int life):Craft(cmd,num,life){
			morale=(float)cmd->lifeEle/life;
			pArm=ArmFactory::getArm(num%3);
		}
		int getCraftType(){return craftType;}	
		void introduce(){
			Craft::introduce();
			cout<<"It has a "<<pArm->getName()<<",and it's morale is ";
			cout.precision(3);cout<<morale<<endl;
		}
};
class Ninja :public Craft{
	Arm *pArm1,*pArm2;
	public:
	static const int craftType=1;
	Ninja(Comander* cmd,int num,int life):Craft(cmd,num,life){
		pArm1=ArmFactory::getArm(num%3);
		pArm2=ArmFactory::getArm((1+num)%3);
	}
	int getCraftType(){return craftType;}	
	void introduce(){ 
		Craft::introduce();
		cout<<"It has a "<<pArm1->getName()<<" and a "<<pArm2->getName()<<endl; }
};

class Iceman :public Craft{ 
	private:
		Arm* pArm;
	public:
		static const int craftType=2;
		Iceman(Comander* cmd,int num,int life):Craft(cmd,num,life){
			pArm=ArmFactory::getArm(num%3);
		}
		int getCraftType(){return craftType;}	
		void introduce(){ 
			Craft::introduce();
			cout<<"It has a "<<pArm->getName()<<endl;}
};
class Lion :public Craft{ 
	private:
		int loyalty;//忠诚度
	public:
		static const int craftType=3;
		Lion(Comander* cmd,int num,int life):Craft(cmd,num,life){
			loyalty=cmd->lifeEle;//生命元数量
		}
		int getCraftType(){return craftType;}	
		void introduce(){ 
			Craft::introduce();
			cout<<"It's loyalty is "<<loyalty<<endl;
		}
};
class Wolf :public Craft{
	public:
		static const int craftType=4;
		int getCraftType(){return craftType;}	
		Wolf(Comander* cmd,int num,int life):Craft(cmd,num,life){}
			void introduce(){ Craft::introduce(); }
};
Craft *Comander::makeCraft(){
	if(lifeEle<=0) return NULL;
	Craft *craft=NULL;
	if(color==Red){
		for(int c=0;c<5&&craft==NULL;c++,next=(next+1)%5){
			switch(next){
				case(0): 
					if(lifeEle>=getIcemanLife())
					craft=new Iceman(this,++startNum,getIcemanLife());
					break;
				case(1):
					if(lifeEle>=getLionLife())
					craft=new Lion(this,++startNum,getLionLife());
					break;
				case(2):
					if(lifeEle>=getWolfLife())
					craft=new Wolf(this,++startNum,getWolfLife());
					break;
				case(3): 
					if(lifeEle>=getNinjaLife())
					craft=new Ninja(this,++startNum,getNinjaLife());
					break;
				case(4): 
					if(lifeEle>=getDragonLife())
					craft=new Dragon(this,++startNum,getDragonLife());
					break;
			}
		}
	}
	else
		for(int c=0;c<5&&craft==NULL;c++,next=(next+1)%5){
			switch(next){
				case(0): 
					if(lifeEle>=getLionLife())
					craft=new Lion(this,++startNum,getLionLife());
					break;
				case(1): 
					if(lifeEle>=getDragonLife())
					craft=new Dragon(this,++startNum,getDragonLife());
					break;
				case(2): 
					if(lifeEle>=getNinjaLife())
					craft=new Ninja(this,++startNum,getNinjaLife());
					break;
				case(3):
					if(lifeEle>=getIcemanLife())
					craft=new Iceman(this,++startNum,getIcemanLife());
					break;
				case(4):
					if(lifeEle>=getWolfLife())
					craft=new Wolf(this,++startNum,getWolfLife());
					break;
			}
		}
	if(craft!=NULL) {addCraft(craft);}
	return craft;
}
void Comander::addCraft(Craft* pCraft)
{
	crafts.push_back(pCraft);
	craftNum[pCraft->getCraftType()]++;
}
int main(){
	int m,n;
	cin>>n;
	while(n-->0){
	cout<<"Case:"<<n+1<<endl;
	cin>>m;//生命元
	Comander *r=new Comander(Red,m);
	Comander *b=new Comander(Blue,m);
	for(int i=0;i<5;i++) cin>>Comander::craftLife0[i];
	Craft *Craft1,*Craft2;
	bool stopr=false,stopb=false;
	for(int time=0;;time++){
		if(!stopr) {
			cout.width(3);
			cout.fill('0');
			Craft1=r->makeCraft();
			if(Craft1!=NULL) {cout<<time<<" ";Craft1->introduce();}
			else {stopr=true; cout<<time<<" red headquarter stops making warriors"<<endl;}
		}
		if(!stopb) {
			cout.width(3);
			cout.fill('0');
			Craft2=b->makeCraft();
			if(Craft2!=NULL){ cout<<time<<" ";Craft2->introduce();}
			else {stopb=true; cout<<time<<" blue headquarter stops making warriors"<<endl;}
		}
		if(stopr&&stopb) break;
		}
	}
	return 0;
}
