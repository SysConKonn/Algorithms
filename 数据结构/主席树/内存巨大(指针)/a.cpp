#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#define MAX_N 100100
#define MAX_M 5010
#define INF 1 << 31 - 1
typedef long long ll;
using namespace std;
struct numm {
  ll x;
  int id;
}num[MAX_N];

struct node {
  int tms;
  node* ch[2];
};
node* null;
node* root[MAX_N];

int N, M;
ll x[MAX_N], x2[MAX_N];
map<int, int> mp;

bool cmp (const numm a, const numm b) {return a.x < b.x;}
void turn () {
  sort (num + 1, num + N + 1, cmp);
  int top = 2;
  ll now = num[1].x, now2;
  num[1].x = 1;
  for (int i = 2;i <= N; ++i) {
    now2 = num[i].x;
    num[i].x = now2 == now ? top - 1 : top++;
    now = now2;
  }
  for (int i = 1;i <= N; ++i) {
    x[num[i].id] = num[i].x;
  }
}

void init (node* &o, int l, int r, int x) {
  //printf("%d %d\n", l, r);
  o = new node();
  o -> ch[0] = o -> ch[1] = null;
  if (l <= x && r >= x) o -> tms++;
  if (l == r) return;
  int mid = (l + r) >> 1;
  init (o -> ch[0], l, mid, x);
  init (o -> ch[1], mid + 1, r, x);
}

int check (int l, int r, int mid, int x) {
  if (l <= x && x <= mid) return 0;
  return 1;
}

void build (node* &o, int l, int r, int x, node* s) {
  //printf("%d %d %d\n", l, r, s -> tms + 1);
  o = new node();
  o -> tms = s -> tms + 1;
  o -> ch[0] = o -> ch[1] = null;
  int mid = (l + r) >> 1;
  if (l == r) return;
  int d = check(l, r, mid, x);
  o -> ch[d ^ 1] = s -> ch[d ^ 1];
  if (d == 0) build (o -> ch[d], l, mid, x, s -> ch[d]);
  else build (o -> ch[d], mid + 1, r, x, s -> ch[d]);
}

int kth (node* o1, node* o2, int l, int r, int k) {
  //printf("%d %d %d   %d %d\n", l, r, k, o1 -> tms, o2 -> tms);
  int x = o2 -> ch[0] -> tms - o1 -> ch[0] -> tms;
  if (l == r) return l;
  int d = k <= x ? 0 : 1;
  int mid = (l + r) >> 1;
  // printf("%d\n", mid);
  if (d == 0) return kth(o1 -> ch[d], o2 -> ch[d], l, mid, k);
  else return kth(o1 -> ch[d], o2 -> ch[d], mid + 1, r, k - x);
}

void init_root () {for (int i = 1;i <= N; ++i) root[i] = null;}
void init_null () {null = new node(); null -> tms = 0;}
int main () {
  init_null();
  init_root();
  scanf("%d%d", &N, &M);
  for (int i = 1;i <= N; ++i) {
    scanf("%lld", &num[i].x);x2[i] = num[i].x;
    num[i].id = i;
  }
  turn();
  //for (int i = 1;i <= N; ++i) printf("%d ", x[i]); printf("\n");
  for (int i = 1;i <= N; ++i) mp[x[i]] = x2[i];
  //for (int i = 1;i <= N; ++i) printf("%d ", mp[x[i]]); printf("\n");

  init(root[0], 1, N, 0);
  init(root[1], 1, N, x[1]);

  for (int i = 2;i <= N; ++i) 
    build (root[i], 1, N, x[i], root[i - 1]);
  
  int l, r, k, res;
  for (int i = 1;i <= M; ++i) {
    scanf("%d%d%d", &l, &r, &k);
    res = kth(root[l - 1], root[r], 1, N, k);
    printf("%d\n", mp[res]);
  }
  return 0;
}
