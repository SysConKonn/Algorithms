#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
#define MAX_N 40000
#define INF 2147483647
typedef long long ll;
using namespace std;

int N, M, u[MAX_N];
ll a[MAX_N];
struct node {
  node* ch[2];
  int r;
  ll v;
  int s;
  int cmp(ll x) const {
    return x < v ? 0 : 1;
  }

  void maintain() {
    s = ch[0]->s + ch[1]->s + 1;
  }
};

node* null;
void init_null() {
  null = new node();
  null -> s = 0;
}
node* root;

void rot (node* &o, int d) {  //d==0 把左儿子转上来
  node* k = o -> ch[d];o -> ch[d] = k -> ch[d ^ 1];k -> ch[d ^ 1] = o;
  o -> maintain(); k -> maintain();
  o = k;
}

void ins (node* &o, ll x) {
  if (o == null) {
    o = new node();
    o -> ch[0] = o -> ch[1] = null;
    o -> v = x;
    o -> r = rand();
    o -> s = 1;
    return;
  }
  o -> s++;
  int d = o -> cmp(x);
  ins (o -> ch[d], x);
  if (o -> ch[d] -> r > o -> r) rot (o, d);
  o -> maintain();
}

ll kth_small (node* o, int x) {
  if (o == null) return INF;
  if (o -> ch[0] -> s == x - 1) {
    return o -> v;
  }
  if (x <= o->ch[0]->s) return kth_small(o -> ch[0], x);
  else return kth_small(o -> ch[1], x - o->ch[0]->s - 1);
}

int main () {
  srand(0);
  scanf("%d%d", &M, &N);
  for (int i = 1;i <= M; ++i) scanf("%lld", a + i);
  for (int i = 1;i <= N; ++i) scanf("%d", u + i);

  int now = 1;
  init_null(); root = null;
  for (int t = 1;t <= N; ++t) {
    if (u[t] != u[t - 1]) {
      for (;now <= u[t]; ++now ) {
	ins (root, a[now]);
      }
    }
    printf("%lld\n", kth_small(root, t));
  }
  return 0;
}
