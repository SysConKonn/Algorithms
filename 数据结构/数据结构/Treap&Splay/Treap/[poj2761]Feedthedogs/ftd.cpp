//先把询问按l,r为第一， 二关键字排序，再加点查询删点

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#define MAX_N 100010
#define MAX_M 50010
#define INF 2147483647
using namespace std;

int M, N, t;
int num[MAX_N], tot1, tot2;
struct info {
  int l, r, k, pos, ans;
}q[MAX_M];

struct node {
  node* ch[2];
  int r;
  int v;
  int s;
  int cmp (int x) const {
    if (x == v) return -1;
    return x < v ? 0 : 1;
  }
  void maintain() {
    s = 1;
    if (ch[0]) s += ch[0] -> s;
    if (ch[1]) s += ch[1] -> s;
  }
};
node* null;
node* root;
void init_null() {null = new node();null->s = 0;null->v=INF;}

void rot (node* &o, int d) {
  node* k = o -> ch[d];o -> ch[d] = k -> ch[d ^ 1];k -> ch[d ^ 1] = o;
  o -> maintain(); k -> maintain();
  o = k;
}

void ins (node* &o, int x) {
  if (o == NULL) {
    //printf("%d\n", x);
    o = new node();
    o -> ch[0] = o -> ch[1] = NULL;
    o -> s = 1;
    o -> v = x;
    o -> r = rand();
  }
  else {
    int d = x < o->v ? 0 : 1;
    ins(o -> ch[d], x);
    if (o -> r < o -> ch[d] -> r) rot(o, d);
  }
  o -> maintain();
}

void del (node* &o, int x) {
  int d = o -> cmp(x);
  if (d == -1) {
    node* u = o;
    if (o -> ch[0] && o -> ch[1]) {
      int d2 = (o -> ch[0]->r < o -> ch[0] -> r ? 1 : 0);
      rot (o, d2);
      del (o -> ch[d2 ^ 1], x);
    }
    else {
      if (o -> ch[0] == NULL) o = o -> ch[1];
      else o = o -> ch[0];
      delete u;
    }
  }
  else del(o -> ch[d], x);
  if (o) o -> maintain();
}

int kth_small (node* o, int x) {
  if (o == NULL || x <= 0 || x > o->s) return -1;
  int s = (o -> ch[0] == NULL) ? 0 : o -> ch[0] -> s;
  if (s == x - 1) return o -> v;
  else if (x <= s) return kth_small(o -> ch[0], x);
  else return kth_small(o -> ch[1], x - s - 1);
}

bool cmp1(info a, info b) {return a.l < b.l;}
bool cmp2(info a, info b) {return a.r < b.r;}
int main () {
  srand(0);
  scanf("%d%d", &N, &M);
  for (int i = 1;i <= N; ++i) scanf("%d", num + i);
  for (int i = 1;i <= M; ++i) {scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].k);q[i].pos = i;}
  
  sort(q + 1, q + M + 1, cmp1);
  tot1 = tot2 = 1;
  q[0].l = q[1].l;
  for (int i = 2;i <= M + 1; ++i) {
    if (q[i].l != q[i - 1].l) {
      sort(q + tot1, q + tot2 + 1, cmp2);
      tot1 = tot2 + 1; 
    }
    tot2++;
  }
  //for (int i = 1;i <= M; ++i) printf("%d %d %d %d\n", q[i].l, q[i].r, q[i].k, q[i].pos);
  
  init_null(); root = NULL;
  int l_ = q[1].l, r_ = q[1].l - 1; 
  int res[MAX_M]; memset(res, 0, sizeof(res));
  //for (int i = l_; i <= r_; ++i) ins (root, num[i]);
  for (t = 1;t <= M; ++t) {
    for (;l_ < q[t].l; l_++) {
      //printf("del: %d\n", num[l_]);
      del(root, num[l_]);   //delete前面不要的
    }
    
    for (;r_ > q[t].r; r_--) {
      //printf("del: %d\n", num[r_]);
      del(root, num[r_]);   //delete后面不要的
    }
    
    for (int i = r_ + 1;i <= q[t].r; ++r_, ++i) {
      //printf("%d \n", num[i]);
      ins(root, num[i]);
    }
    res[q[t].pos] = kth_small(root, q[t].k);
    //printf("%d %d  %d\n", q[t].l, q[t].r, res[q[t].pos]);
  }

  //printf("OK\n");
  //for (int i = 1;i <= M; ++i) res[q[i].pos] = q[i].ans;
  for (int i = 1;i <= M; ++i) printf("%d\n", res[i]);
  return 0;
}
