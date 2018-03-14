#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#define MAX_N 300010
#define MAX_Q 1000040
#define INF 2147483647
using namespace std;

int N, Q;
long long ST_Max[MAX_N * 4 + 1];
long long H[MAX_N];
int top = 0;
int pos[MAX_N], max_;

long long _max(long long a, long long b) {
  return a < b ? b : a;
}

int AT_Max(int l, int r, int now) {
  max_ = _max(max_, now);
  if(l == r) {pos[l] = now;return ST_Max[now] = H[l];}
  return ST_Max[now] =  _max(AT_Max(l, (l + r) / 2, now * 2), AT_Max((l + r) / 2 + 1, r, now * 2 + 1));
}

long long find_Max(int l, int r, int lsum, int rsum, int now) {
  if(l > rsum || r < lsum) return -INF;
  if(l >= lsum && r <= rsum) return ST_Max[now];
  return _max(find_Max(l, (l + r) / 2, lsum, rsum, now * 2), find_Max((l + r) / 2 + 1, r, lsum, rsum, now * 2 + 1));
}

void cag (int x, int a) {
  x = pos[x];
  ST_Max[x] = a;
  while (x > 0) {
    //printf("%d\n", x);
    x = (x ^ 1) / 2;
    ST_Max[x] = _max(ST_Max[x * 2], ST_Max[x * 2 + 1]);
  }
}

void find_() {
  int l, r;
  scanf("%d%d", &l, &r);
  long long res = find_Max(1, N, l, r, 1);
  printf("%lld\n", res);
}

void change() {
  int x, a;
  scanf("%d%d", &x, &a);
  cag(x, a);
}

void print() {
  int sum = 1;
  for (int i = 1;sum <= max_; ++i) {
    for (int j = 1;j <= pow(2, i - 1); ++j) printf("%lld ", ST_Max[sum++]);
    printf("\n");
  }
}

int main() {
  while(scanf("%d%d", &N, &Q) == 2) {
    memset(H, 0, sizeof(H));
    memset(ST_Max, 0, sizeof(ST_Max));
    memset(pos, 0, sizeof(pos));
    for(int i = 1;i <= N; i++) scanf("%lld", &H[i]);
    ST_Max[1] = AT_Max(1, N, 1);
    for (int i = 1;i <= Q; ++i) {
      char c[20];
      scanf("%s", c);
      //print();
      if (c[0] == 'Q') find_();
      else change();
    }
  }
  return 0;
}
