/* 
translation: 
    给出一列数组，有两种操作，将某一区间所有的数字都加上c，查询某一区间的和。 
solution: 
    线段树区间操作模板 
note: 
date: 
    2016.11.18 
*/  
#include <iostream>  
#include <cstdio>  
  
using namespace std;  
const int maxn = 100000 + 5;  
const int INF = 1e9 + 10;  
  
typedef long long ll;  
  
ll sum[maxn * 4], inc[maxn * 4];  
int s[maxn * 4], e[maxn * 4];  
int n, q;  
  
inline void push_up(int rt)  
{  
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];  
}  
  
void build(int l, int r, int rt)  
{  
    s[rt] = l;  
    e[rt] = r;  
    inc[rt] = 0;  
    if(l == r){  
        scanf("%lld", &sum[rt]);  
        return;  
    }  
    build(l, (l + r) / 2, rt << 1);  
    build((l + r) / 2 + 1, r, rt << 1 | 1);  
    push_up(rt);  
}  
  
void push_down(int rt, int num)  
{  
    if(inc[rt]){  
        inc[rt << 1] += inc[rt];  
        inc[rt << 1 | 1] += inc[rt];  
        sum[rt << 1] += inc[rt] * (num - (num >> 1));  
        sum[rt << 1 | 1] += inc[rt] * (num >> 1);  
        inc[rt] = 0;  
    }  
}  
  
void update(int c, int l, int r, int rt)    //线段树节点中的l～r区间增加c  
{  
    if(s[rt] == l && e[rt] == r){  
        inc[rt] += c;  
        sum[rt] += (ll)c * (r - l + 1);  
        return;  
    }  
    if(s[rt] == e[rt])  return;  
  
    push_down(rt, e[rt] - s[rt] + 1);  
  
    int m = (s[rt] + e[rt]) / 2;  
    if(r <= m)   update(c, l, r, rt << 1);  
    else if(l > m)   update(c, l, r, rt << 1 | 1);  
    else{  
        update(c, l, m, rt << 1);  
        update(c, m + 1, r, rt << 1 | 1);  
    }  
  
    push_up(rt);  
}  
  
ll query(int l, int r, int rt)  
{  
    if(s[rt] == l && e[rt] == r){  
        return sum[rt];  
    }  
    push_down(rt, e[rt] - s[rt] + 1);  
  
    ll res = 0;  
    int m = (s[rt] + e[rt]) / 2;  
  
    if(r <= m)   res += query(l, r, rt << 1);  
    else if(l > m)   res += query(l, r, rt << 1 | 1);  
    else{  
        res += query(l, m, rt << 1);  
        res += query(m + 1, r, rt << 1 | 1);  
    }  
    return res;  
}  
  
int main()  
{  
    //freopen("input.txt", "r", stdin);  
    while(~scanf("%d%d", &n, &q)){  
        build(1, n, 1);  
  
        char cmd[5];  
        int a, b, c;  
        while(q--){  
            getchar();  
            scanf("%s", cmd);  
  
            if(cmd[0] == 'C'){  
                scanf("%d%d%d", &a, &b, &c);  
                update(c, a, b, 1);  
            }else if(cmd[0] == 'Q'){  
                scanf("%d%d", &a, &b);  
                printf("%lld\n", query(a, b, 1));  
            }  
        }  
    }  
    return 0;  
}  
