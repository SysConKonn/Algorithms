#include <cstdio>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstring>
#define MAX_N 50010
#define INF 214748647
#define MOD 999999
using namespace std;
struct point {
  int w, rd, sz, re, l, r;
}p[MAX_N];

int root, ans, tot;
long long N, num[MAX_N], sum, pre_, nxt_;

int rand_ () {
  int a, b;
  //return a * b * (a - b) * (a + b)  % MOD;
  return 1;
}

void up (int x) {p[x].sz = p[p[x].l].sz + p[p[x].r].sz + p[x].re;}

void r_rot (int &x) {
  int y = p[x].r;
  p[x].r = p[y].l;
  p[y].l = x;
  p[y].sz = p[x].sz;
  up(x);
  x = y;
}

void l_rot (int &x) {
  int y = p[x].l;
  p[x].l = p[y].r;
  p[y].r = x;
  p[y].sz = p[x].sz;
  up(x);
  x = y;
}

void ins (long long x, int& k) {
  if (k == 0) {
    tot++;
    k = tot;
    p[k].w = x;
    p[k].sz = p[k].re = 1;
    p[k].rd = rand();
    return;
  }
  p[k].sz++;
  if (p[k].w == x) p[k].re++;
  else {
    if (x > p[k].w) {
      ins(x, p[k].r);
      if (p[k].rd > p[p[k].r].rd) r_rot(k);
    }
    else {
      ins(x, p[k].l);
      if (p[k].rd > p[p[k].l].rd) l_rot(k);
    }
  }
}

void pre (long long x, int k) {
  if (k == 0) return;
  if (p[k].w <= x) {
    ans = k;
    pre(x, p[k].r);
  }
  else pre(x, p[k].l);
}

void nxt (long long x, int k) {
  if (k == 0) return;
  if (p[k].w >= x) {
    ans = k;
    nxt(x, p[k].l);
  }
  else nxt(x, p[k].r);
}

int main () {
  srand(0);
  scanf("%lld", &N);
  p[0].w = INF;
  for (int i = 1;i <= N; ++i) {
  	scanf("%lld", &num[i]);
  }

  sum = num[1];
  ins(num[1], root);
  for (int i = 2;i <= N; ++i) {
  	pre(num[i], root);
    int x = ans;
  	nxt(num[i], root);
    sum += (long long)min(abs(num[i] - p[x].w), abs(p[ans].w - num[i]));
  	ins(num[i], root);
  }
  printf("%lld\n", sum);
  return 0;
}
