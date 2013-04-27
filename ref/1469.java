/* @author: xuchang09@otcaix.iscas.ac.cn */
import java.io.*;
import java.util.*;
public class Main
{
  static int m,n;
  static boolean[] flag=new boolean[301];
  static int[] occ=new int[301];
  static int[][] adj=new int[101][301];
  public static void main(String args[]) throws Exception
  {
    InputStreamReader is=new InputStreamReader(System.in);
    BufferedReader in=new BufferedReader(is);
    int t=Integer.parseInt(in.readLine());
     while(t--!=0)
     {
     	String[] ss=in.readLine().split(" ");
       n=Integer.parseInt(ss[0]);
       m=Integer.parseInt(ss[1]);
       if(n>m)
        {
         System.out.println("NO");
         continue;
        }
       for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
         adj[i][j]=0;
      for(int i=0;i< n;i++)
      	{
          ss=in.readLine().split(" ");
          int a=Integer.parseInt(ss[0]);
          for(int j=0;j< a;j++)
           {
            adj[i+1][Integer.parseInt(ss[j+1])]=1;
           }
       }
       int count=0;
       for(int i=0;i<=m;i++)
         occ[i]=0;
      	for(int i=1;i<=n;i++)
      	{
        for(int j=0;j<=m;j++)
         flag[j]=false;
        if(find(i))
         {
          count++;
          }
        else
        {
          break;
         }
                    		
       }
      	if(count==n)
         System.out.println("YES");
       else
         System.out.println("NO");
     }
  }
            
  public static boolean find(int i)
  {
    for(int j=1;j<=m;j++)
    {
     if(!flag[j]&&adj[i][j]==1)
      {
       if(occ[j]==0)
        {
           occ[j]=i;
           return true;
        }
       }
    }
    for(int j=1;j<=m;j++)
    {
     if(!flag[j]&&adj[i][j]==1)
      {
        flag[j]=true;
        if(find(occ[j]))
        {
          occ[j]=i;
          return true;
				}
      }
    }
   return false;
 }
}
