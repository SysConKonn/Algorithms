#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
int n,root,size,ans;
struct P{
  int l,r,sz,key,rd,re;//re为重复次数
}t[1000005];
void update(int k)
{
  t[k].sz=t[t[k].l].sz+t[t[k].r].sz+t[k].re;
}
void left(int &k)
{
  int y=t[k].r;
  t[k].r=t[y].l;
  t[y].l=k;
  t[y].sz=t[k].sz;
  update(k);
  k=y;
}
void right(int &k)
{
  int y=t[k].l;
  t[k].l=t[y].r;
  t[y].r=k;
  t[y].sz=t[k].sz;
  update(k);
  k=y;
}
void init(int &k,int x)
{
  if(k==0)
    {
      size++;
      k=size;
      t[k].sz=1;
      t[k].re=1;
      t[k].key=x;
      t[k].rd=rand();
      return;
    }
  t[k].sz++;
  if(t[k].key==x)  t[k].re++;
  else{
    if(x>t[k].key)
      {
	init(t[k].r,x);
	if(t[t[k].r].rd<t[k].rd)   left(k);
      }
    if(x<t[k].key)
      {
	init(t[k].l,x);
	if(t[t[k].l].rd<t[k].rd)   right(k);
      }
  }
} 
void del(int &k,int x)
{
  if(k==0)  return;
  if(t[k].key==x)
    {
      if(t[k].re>1)
	{
	  t[k].re--;
	  t[k].sz--;
	  return;
	}
      if(t[k].l*t[k].r==0)  k=t[k].l+t[k].r;//k代表指针的移动，所以移动到了左或右儿子
      else
	{
	  if(t[t[k].l].rd<t[t[k].r].rd){
	    right(k);
	    del(k,x);
	  }
	  else{
	    left(k);
	    del(k,x);
	  }
	}
    }
  else{
    if(x>t[k].key)
      {
	t[k].sz--;
	del(t[k].r,x);
      }
    else{
      t[k].sz--;
      del(t[k].l,x);
    }
  }
}
int rank1(int k,int x)
{
  if(k==0)  return 0;
  if(t[k].key==x)  return t[t[k].l].sz+1;
  if(x>t[k].key)   return t[t[k].l].sz+rank1(t[k].r,x)+t[k].re;
  if(x<=t[k].key)  return rank1(t[k].l,x);
}
int rank2(int k,int x)
{
  if(k==0)  return 0;
  else if(x<=t[t[k].l].sz)    return rank2(t[k].l,x);
  else if(x>t[t[k].l].sz+t[k].re)  return rank2(t[k].r,x-t[t[k].l].sz-t[k].re);
  else  return  t[k].key; 
}
void pre(int k,int x)
{
  if(k==0)  return;
  if(t[k].key<x)
    {
      ans=k;
      pre(t[k].r,x);
    }
  else pre(t[k].l,x);
}
void nxt(int k,int x)
{
  if(k==0)  return;
  if(t[k].key>x)
    {
      ans=k;
      nxt(t[k].l,x);
    }
  else nxt(t[k].r,x);
}
int main()
{
  srand(time(0));
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
    {
      int num,x;
      scanf("%d%d",&num,&x);
      if(num==1)  init(root,x);
      if(num==2)  del(root,x);
      if(num==3)  printf("%d\n",rank1(root,x));
      if(num==4)  printf("%d\n",rank2(root,x));
      if(num==5)
	{
	  pre(root,x);
	  printf("%d\n",t[ans].key);
	}
      if(num==6)
	{
	  nxt(root,x);
	  printf("%d\n",t[ans].key);
	}
    }
  return 0;
}
