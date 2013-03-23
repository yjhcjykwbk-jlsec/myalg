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
		Craft* makeCraft(int time);
		int getCraftNum(int i){return craftNum[i];}
};
int Comander::craftLife0[5]={0,1,2,3,4};
class Craft{
	protected:
		int birthtime;
		int number;
		Comander *cmd;//阵营
		int life;//生命值
	public:
		Craft(Comander *comander,int num,int life,int time):cmd(comander),number(num),life(life),birthtime(time){
			comander->lifeEle-=this->life;//每生成一个Craft，将消耗总部生命元
		}
		virtual int getCraftType(){return -1;}	
		const char *getCraftName(){
			switch(getCraftType()){
				case(0):return "dragon";break;
				case(1):return "ninja";break;
				case(2):return "iceman";break;
				case(3):return "lion";break;
				case(4):return "wolf";break;
				default:return "";
			}
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
		Dragon(Comander* cmd,int num,int life,int time):Craft(cmd,num,life,time){
			morale=(float)cmd->lifeEle/life;
			pArm=ArmFactory::getArm(num%3);
			cmd->addCraft(this);
			cout.width(3);
			cout.fill('0');
			cout<<birthtime<<" ";
			cout<<cmd->getColor()<<" "<<getCraftName()<<" "<<number<<" born with strength "<<life<<","<<cmd->getCraftNum(getCraftType())<<" "<<getCraftName()<<" in "<<cmd->getColor()<<" headquarter"<<endl;
			cout<<"It has a "<<pArm->getName()<<",and it's morale is "; cout.precision(3);cout<<morale<<endl;
		}
		int getCraftType(){return 0;}	
};
class Ninja :public Craft{
	Arm *pArm1,*pArm2;
	public:
	Ninja(Comander* cmd,int num,int life,int time):Craft(cmd,num,life,time){
		pArm1=ArmFactory::getArm(num%3);
		pArm2=ArmFactory::getArm((1+num)%3);
			cmd->addCraft(this);
		cout.width(3);
		cout.fill('0');
		cout<<birthtime<<" ";
		cout<<cmd->getColor()<<" "<<getCraftName()<<" "<<number<<" born with strength "<<life<<","<<cmd->getCraftNum(getCraftType())<<" "<<getCraftName()<<" in "<<cmd->getColor()<<" headquarter"<<endl;
		cout<<"It has a "<<pArm1->getName()<<" and a "<<pArm2->getName()<<endl; 
	}
	int getCraftType(){return 1;}	
};

class Iceman :public Craft{ 
	private:
		Arm* pArm;
	public:
		Iceman(Comander* cmd,int num,int life,int time):Craft(cmd,num,life,time){
			pArm=ArmFactory::getArm(num%3);
			cmd->addCraft(this);
			cout.width(3);
			cout.fill('0');
			cout<<birthtime<<" ";
			cout<<cmd->getColor()<<" "<<getCraftName()<<" "<<number<<" born with strength "<<life<<","<<cmd->getCraftNum(getCraftType())<<" "<<getCraftName()<<" in "<<cmd->getColor()<<" headquarter"<<endl;
			cout<<"It has a "<<pArm->getName()<<endl;}
		int getCraftType(){return 2;}	
};
class Lion :public Craft{ 
	private:
		int loyalty;//忠诚度
	public:
		static const int craftType=3;
		Lion(Comander* cmd,int num,int life,int time):Craft(cmd,num,life,time){
			loyalty=cmd->lifeEle;//生命元数量
			cmd->addCraft(this);
			cout.width(3);
			cout.fill('0');
			cout<<birthtime<<" ";
			cout<<cmd->getColor()<<" "<<getCraftName()<<" "<<number<<" born with strength "<<life<<","<<cmd->getCraftNum(getCraftType())<<" "<<getCraftName()<<" in "<<cmd->getColor()<<" headquarter"<<endl;
			cout<<"It's loyalty is "<<loyalty<<endl;
		}
		int getCraftType(){return 3;}	
};
class Wolf :public Craft{
	public:
		Wolf(Comander* cmd,int num,int life,int time):Craft(cmd,num,life,time){
			cmd->addCraft(this);
			cout.width(3);
			cout.fill('0');
			cout<<birthtime<<" ";
			cout<<cmd->getColor()<<" "<<getCraftName()<<" "<<number<<" born with strength "<<life<<","<<cmd->getCraftNum(getCraftType())<<" "<<getCraftName()<<" in "<<cmd->getColor()<<" headquarter"<<endl;
		}
		int getCraftType(){return 4;}	
};
Craft *Comander::makeCraft(int time){
	if(lifeEle<=0) return NULL;
	Craft *craft=NULL;
	if(color==Red){
		for(int c=0;c<5&&craft==NULL;c++,next=(next+1)%5){
			switch(next){
				case(0): 
					if(lifeEle>=getIcemanLife())
					craft=new Iceman(this,++startNum,getIcemanLife(),time);
					break;
				case(1):
					if(lifeEle>=getLionLife())
					craft=new Lion(this,++startNum,getLionLife(),time);
					break;
				case(2):
					if(lifeEle>=getWolfLife())
					craft=new Wolf(this,++startNum,getWolfLife(),time);
					break;
				case(3): 
					if(lifeEle>=getNinjaLife())
					craft=new Ninja(this,++startNum,getNinjaLife(),time);
					break;
				case(4): 
					if(lifeEle>=getDragonLife())
					craft=new Dragon(this,++startNum,getDragonLife(),time);
					break;
			}
		}
	}
	else
		for(int c=0;c<5&&craft==NULL;c++,next=(next+1)%5){
			switch(next){
				case(0): 
					if(lifeEle>=getLionLife())
					craft=new Lion(this,++startNum,getLionLife(),time);
					break;
				case(1): 
					if(lifeEle>=getDragonLife())
					craft=new Dragon(this,++startNum,getDragonLife(),time);
					break;
				case(2): 
					if(lifeEle>=getNinjaLife())
					craft=new Ninja(this,++startNum,getNinjaLife(),time);
					break;
				case(3):
					if(lifeEle>=getIcemanLife())
					craft=new Iceman(this,++startNum,getIcemanLife(),time);
					break;
				case(4):
					if(lifeEle>=getWolfLife())
					craft=new Wolf(this,++startNum,getWolfLife(),time);
					break;
			}
		}
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
	int data[1000][5];int mdata[1000];
	for(int i=1;i<=n;i++){
		cin>>mdata[i];
		for(int j=0;j<5;j++) cin>>data[i][j];
	}
	int i=0;
	while(++i<=n){
		m=mdata[i];//生命元
		Comander *r=new Comander(Red,m);
		Comander *b=new Comander(Blue,m);
		for(int j=0;j<5;j++) Comander::craftLife0[j]=data[i][j];
		cout<<"Case:"<<i<<endl;
		Craft *Craft1,*Craft2;
		bool stopr=false,stopb=false;
		for(int time=0;;time++){
			if(!stopr) {
				Craft1=r->makeCraft(time);
				if(Craft1==NULL) {stopr=true; cout.width(3); cout.fill('0'); cout<<time<<" red headquarter stops making warriors"<<endl;}
			}
			if(!stopb) {
				Craft2=b->makeCraft(time);
				if(Craft2==NULL) {stopb=true; cout.width(3); cout.fill('0'); cout<<time<<" blue headquarter stops making warriors"<<endl;}
			}
			if(stopr&&stopb) break;
		}
	}
	return 0;
}
