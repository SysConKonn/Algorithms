#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#define MAX_N 200010
typedef long long ll;
using namespace std;
struct edge{
  ll ans, val;
};

int N;
ll h, w;
ll dat[MAX_N * 4];

int mk_tree (ll l, ll r, ll k, ll w) {
  //printf("%lld %lld %lld %lld\n", l, r, k, w);
  if (l == r) {/*printf("%lld %lld\n", l, k);*/return dat[k] =  w;}
  return dat[k] = (mk_tree(l, (l + r) / 2, k * 2, w) + mk_tree((l + r) / 2 + 1, r, k * 2 + 1, w)) / 2;
}

ll res;

edge sum (int l, int r, int k, int val) {
  if (l == r) {
    if (val <= dat[k]) {
      dat[k] -= val;
      return (edge){l, dat[k]};
    }
    else return (edge){-1, -1};
  }
  else {
    if (dat[k] < val) return (edge){-1, -1};
    edge res = sum(l, (l + r) / 2, k * 2, val);
    if (res.ans != -1) {
      dat[k] = max(dat[k * 2], dat[k * 2 + 1]);
      return (edge){res.ans, dat[k]};
    }
    else {
      edge res = sum((l + r) / 2 + 1, r, k * 2 + 1, val);
      dat[k] = max(dat[k * 2], dat[k * 2 + 1]);
      return (edge){res.ans, dat[k]};
    }
  }
}

int main () {
  while (scanf("%lld%lld%d", &h, &w, &N) == 3) {
    
    memset(dat, 0, sizeof(dat));
    h = min(h, 1LL * N);
    //printf("%lld %lld %d\n", h, w, N);
    dat[1] = mk_tree(1, h, 1, w);
    int x = N;
    while (x--) {
      ll d;
      scanf("%lld", &d);
      printf("%lld\n", sum(1, h, 1, d).ans);
    }
  }
  return 0;
}
