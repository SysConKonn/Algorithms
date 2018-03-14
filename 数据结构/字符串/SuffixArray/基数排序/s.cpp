#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 1000100
using namespace std;

int N, maxx;
int buc[10];
struct num {
  int x, pos;
}a[MAX_N];
num ar[MAX_N];

int getlen (int x) {
  char sc[10];
  sprintf(sc, "%d", x);
  return strlen(sc);
}

int main () {
  scanf("%d", &N);
  for (int i = 1;i <= N; ++i) {
    scanf("%d", &a[i].x);a[i].pos = i;
    int len_ = getlen(a[i].x);
    maxx = max(len_, maxx);
  }

  for (int i = 1;i <= maxx; ++i) {
    memset(buc, 0, sizeof(buc));
    int dev = pow(10, i - 1);
    int maxp = 0;
    for (int j = 1;j <= N; ++j) {
      int now = a[j].x % (dev * 10) / dev;
      buc[now]++;
      maxp = max(maxp, now);
    }  
    for (int j = 1;j <= maxp; ++j) buc[j] += buc[j - 1];
    for (int j = N;j > 0; --j) {
      int now = a[j].x % (dev * 10) / dev;
      ar[buc[now]--] = a[j];
    }
    for (int i = 1;i <= N; ++i) a[i] = ar[i];
  }

  for (int i = 1;i <= N; ++i) printf("%d ", a[i].x);
  printf("\n");
  return 0;
}
