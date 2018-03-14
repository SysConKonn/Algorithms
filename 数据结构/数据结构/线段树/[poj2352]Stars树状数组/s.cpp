#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX_N 15010
#define MAX_P 32010
using namespace std;

int N, max_, x[MAX_P], y[MAX_P];
int bit[MAX_P];
int res[MAX_N];

void add (int i) {
  while (i <= MAX_P) {
    bit[i]++;
    i += i & -i;
  }
}

void sum (int i) {
  int s = 0;
  while (i > 0) {
    s += bit[i];
    i -= i & -i;
  }
  res[s]++;
}

int main () {
  scanf("%d", &N);

  for (int i = 1;i <= N; ++i) scanf("%d%d", x + i, y + i);
  for (int i = 1;i <= N; ++i) {
    sum(++x[i]);
    add(x[i]);
  }

  for (int i = 0;i < N; ++i) printf("%d\n", res[i]);
  return 0;
}
