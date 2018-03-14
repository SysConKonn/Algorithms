#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 5010
#define INF 1e9
typedef long long ll;
using namespace std;

int N, bit[MAX_N * 2];
ll p[MAX_N];
ll res, num[MAX_N];

void add(int i, int x) {
  while (i <= N) {
    bit[i] += x;
    i += i & -i; 
  }
}

int sum(int i) {
  int s = 0;
  while (i > 0) {
    s += bit[i];
    i -= i & -i;
  }
  return s;
}

int main () {
  while (scanf("%d", &N) == 1) {
    memset(bit, 0, sizeof(bit));
    memset(num, 0, sizeof(num));
    res = 0;
    ll min_ = INF;
    for (int i = 1;i <= N; ++i) scanf("%lld", &p[i]), min_ = min(min_, p[i]);
    //int need = 1 - min_;
    for (int i = 1;i <= N; ++i) p[i]++;
    for (int i = N;i > 0; --i) {
      num[i] = sum(p[i] - 1);
      res += num[i];
      add(p[i], 1);
    }
    min_ = res;
    for (int i = 1;i <= N; ++i) {
      res += (N - 2 * p[i] + 1), min_ = min(min_, res);
    }
    
    printf("%lld\n", min_);
  }
  return 0;
}
