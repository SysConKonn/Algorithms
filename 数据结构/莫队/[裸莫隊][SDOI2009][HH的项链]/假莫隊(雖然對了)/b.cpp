#include <bits/stdc++.h>
#define MAX_N 50010
#define MAX_M 200100
#define MAX_NUM 1000000 + 10
using namespace std;
struct query {
  int l, r;
  int id;

  bool operator < (const query& q) const {
    return (l/500 == q.l/500) ? r < q.r : (l/500) < (q.l/500);
  }
}ask[MAX_M];

int N, M;
int x[MAX_N];
int num[MAX_NUM], sum;
int l = 1, r;
int res[MAX_M];

void add (int x) {
  num[x]++;
  if (num[x] == 1) sum++;
}

void del (int x) {
  num[x]--;
  if (num[x] == 0) sum--;
}

int main () {
  scanf("%d", &N);
  for (int i = 1;i <= N; ++i) scanf("%d", x + i);
  scanf("%d", &M);
  for (int i = 1;i <= M; ++i) {
    scanf("%d%d", &ask[i].l, &ask[i].r);
    ask[i].id = i;
  }
  sort (ask + 1, ask + M + 1);

  for (int i = 1;i <= M; ++i) {
    while (l < ask[i].l) {
      del(x[l]);
      l++;
    }
    while (l > ask[i].l) {
      l--;
      add(x[l]);
    }
    while (r > ask[i].r) {
      del(x[r]);
      r--;
    }
    while (r < ask[i].r) {
      r++;
      add(x[r]);
    }
    res[ask[i].id] = sum;
  }

  for (int i = 1;i <= M; ++i) printf("%d\n", res[i]);
  return 0;
}
