#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<ctime>
using namespace std;
int n,root,size;
long long ans,sum;
long long inf=1000005;
long long a[50010];
struct P{
    int l,r,sz,re,key,rd;
}t[50010];
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
    if(t[k].key==x)   t[k].re++;
    else{
        if(x>t[k].key)
        {
            init(t[k].r,x);
            if(t[t[k].r].rd<t[k].rd)	left(k);
        }
        else{
            init(t[k].l,x);
            if(t[t[k].l].rd<t[k].rd)    right(k);
        }
    }
}
void pre(int k,int x)
{
    if(k==0)  return;
    if(t[k].key<=x)
    {
         ans=k;
         pre(t[k].r,x);
    }
    else pre(t[k].l,x);
}
void nxt(int k,int x)
{
    if(k==0)  return;
    if(t[k].key>=x)
    {
        ans=k;
        nxt(t[k].l,x);
    }
    else nxt(t[k].r,x);
}
int main()
{
    srand(0);
    scanf("%d",&n);
    t[0].key=inf;
    for(int i=1;i<=n;i++)  scanf("%lld",&a[i]);
    sum = a[1];
    init(root,a[1]);
    for(int i=2;i<=n;i++)
    {
        pre(root,a[i]);
        int x=ans;
        nxt(root,a[i]);
        sum+=(long long)min(abs(a[i]-t[x].key),abs(t[ans].key-a[i]));
        init(root,a[i]);
        //printf("%lld\n", sum);
    }
    printf("%lld",sum);
    return 0;
}
