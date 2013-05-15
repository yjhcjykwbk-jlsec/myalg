#include<math.h>
                           #include<stdio.h>
int isPrime(int x)
{
   //wirte your code here
	if(x<2)return false;
	if(x==2)return true;
	for(int i=2;i<=pow(x,0.5);i++)
	{
		if(x%i==0) return false;
	}
  return true; 
}


//start 提示：自动阅卷起始唯一标识，请勿删除或增加。
int main()
{    
    //wirte your code here
	for(int i=1,j=0;i<=1000;i++){
		if(isPrime(i)){
			j++;
			printf("%d ",i);
			if(j%10==0) printf("\n");
		}
	}
	return 0;
}
//end //提示：自动阅卷结束唯一标识，请勿删除或增加。
