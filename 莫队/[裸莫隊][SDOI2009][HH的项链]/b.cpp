#include <bits/stdc++.h>
#define MAX_N 50010
#define MAX_M 200010
#define MAX_NUM 1000100
using namespace std;
struct query {
  int l, r;
  int id, grp;
}q[MAX_M];

int N, M;
int x[MAX_N];
int grp;
int sum, times[MAX_NUM];
int res[MAX_M];

bool cmp (const query a, const query b) {
  return a.grp == b.grp ? a.r < b.r : a.grp < b.grp;
}

int main () {
  scanf("%d", &N);
  grp = sqrt(N);
  for (int i = 1;i <= N; ++i) 
    scanf("%d", x + i);
  
  scanf("%d", &M);
  for (int i = 1;i <= M; ++i) {
    scanf("%d%d", &q[i].l, &q[i].r);
    q[i].id = i;
    q[i].grp = q[i].l / grp;
  }
  
  sort(q + 1, q + M + 1, cmp);
  
  for (int i = q[1].l;i <= q[1].r; ++i) {
    if (!times[x[i]]) sum++;
    times[x[i]]++;
  }
  res[q[1].id] = sum;
  int l = q[1].l, r = q[1].r;

  for (int i = 2;i <= M; ++i) {
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
    
    res[q[i].id] = sum;
  }

  for (int i = 1;i <= M; ++i) {
    printf("%d\n", res[i]);
  }
  
  return 0;
}
