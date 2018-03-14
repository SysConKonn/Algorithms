#include <bits/stdc++.h>
#define MAX_N 10010
#define MAX_M 10010
#define MAX_NUM 1000010
#define MAX_C 1010
using namespace std;
struct query {
  int l, r;
  int id, grp;
  int pre;
}q[MAX_M];
struct change {
  int fromid, tocol;
  int id;
}c[1010];

int N, M, grp;
int qm, cm;
int l, r;
int fre;
int x[MAX_N], x2[MAX_N];
int times[MAX_NUM], sum;
int res[MAX_N];

bool cmp (const query a, const query b) {return a.grp == b.grp ? a.r < b.r : a.grp < b.grp;}
int main () {
  scanf("%d%d", &N, &M);
  grp = sqrt(N);
  for (int i = 1;i <= N; ++i) {
    scanf("%d", x + i);x2[i] = x[i];
  }

  char op[5];
  int a, b;
  for (int i = 1;i <= M; ++i) {
    scanf("%s%d%d", op, &a, &b);
    if (op[0] == 'Q') {
      q[++qm] = (query){a, b, qm, 0, cm};
      q[qm].grp = q[qm].l / grp;
    }
    else {
      c[++cm] = (change){a, b, i};
    }
  }

  sort (q + 1, q + qm + 1, cmp);
  l = 1, r = 0, fre = 0;
  for (int i = 1;i <= qm; ++i) {
    
    while (l > q[i].l) {
      l--;
      if (!times[x[l]]) sum++;
      times[x[l]]++;
    }

    while (l < q[i].l) {
      times[x[l]]--;
      if (!times[x[l]]) sum--;
      l++;
    }

    while (r < q[i].r) {
      r++;
      if (!times[x[r]]) sum++;
      times[x[r]]++;
    }

    while (r > q[i].r) {
      times[x[r]]--;
      if (!times[x[r]]) sum--;
      r--;
    }

    while (fre < q[i].pre) {
      fre++;
      if (fre < l || fre > r) break;
      int &from = x[c[fre].fromid], to = c[fre].tocol;
      if (!times[to]) sum++;
      times[to]++;
      times[from]--;
      if (!times[from]) sum--;
      from = to;
    }

    while (fre > q[i].pre) {
      if (fre < l || fre > r) break;
      int &from = x[c[fre].fromid], to = c[fre].tocol;
      if (!times[from]) sum++;
      times[from]++;
      times[to]--;
      if (!times[to]) sum--;
      fre--;
      from = x2[c[fre].fromid];
    }
    
    res[q[i].id] = sum;
  }

  for (int i = 1;i <= qm; ++i) printf("%d\n", res[i]);
  return 0;
}
