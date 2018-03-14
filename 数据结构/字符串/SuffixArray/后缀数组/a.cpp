#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 1000050
using namespace std;
char s[maxn];
int t[maxn],x[maxn],y[maxn],sa[maxn],n,m=128,p;
int main()
{
  scanf("%s",s);
  n=strlen(s);
  for(int i=0;i<m;i++)   t[i]=0;
  for(int i=0;i<n;i++)   t[x[i]=s[i]]++;
  for(int i=0;i<m;i++)   t[i]+=t[i-1];   // 求前缀和
  for(int i=n-1;i>=0;i--)   sa[--t[s[i]]]=i;
  for(int k=1;k<n;k<<=1)
    {
      p=0;
      for(int i=n-k;i<n;i++)   y[p++]=i;//找到第二关键字为0的位置，然后打进去
      for(int i=0;i<n;i++)   if(sa[i]>=k)  y[p++]=sa[i]-k;//按照排名给第二关键字排序
      for(int i=0;i<m;i++)  t[i]=0;
      for(int i=0;i<n;i++)  t[x[y[i]]]++;//x[i]表示的是当前看k个的排名
      for(int i=0;i<m;i++)  t[i]+=t[i-1];//进行新一轮的基数排序
      for(int i=n-1;i>=0;i--)  sa[--t[x[y[i]]]]=y[i];//利用第二关键字排名求出新一轮的后缀排名
		
      swap(x,y);
      p=1;
      x[sa[0]]=0;//将原来排名为0的字符串在下一次的倍增中的排名计为0
      for(int i=1;i<n;i++)
	{
	  if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])  x[sa[i]]=p-1;//若是第一关键字和第二关键字都相等，则将他们赋为相同的排名。
	  else   x[sa[i]]=p++;//否则，赋为当前排名，并将排名加1
	}
      if(p>=n)  break;//如果最大的排名已经是n了，也就是所有的排名均不一样了，就直接跳出
      m=p;//否则，就将m赋为最大的排名
    }
  for(int i=0;i<n;i++)  printf("%d ",sa[i]+1);
  printf("\n");
  return 0;
}
