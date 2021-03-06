#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define MAX_N 1000100
using namespace std;

char s[MAX_N];
int N, M = 128;
int buc[MAX_N], sa[MAX_N], x[MAX_N], y[MAX_N];

int main () {
  scanf("%s", s);
  N = strlen(s);
  memset(buc, 0, sizeof(buc));
  for (int i = 0;i < N; ++i) buc[x[i] = s[i]]++;
  for (int i = 0;i < M; ++i) buc[i] += buc[i - 1];
  for (int i = N - 1;i >= 0; --i) sa[--buc[x[i]]] = i;
  for (int i = 0;i < N; ++i) printf("%d ", sa[i]); printf("\n");

  for (int k = 1;k <= N; k *= 2) {
    int p = 0;
    // 先求出y
    for (int i = N - k;i < N; ++i) y[p++] = i;
    for (int i = 0;i < N; ++i) if (sa[i] >= k) y[p++] = sa[i] - k;

    memset(buc, 0, sizeof(buc));
    for (int i = 0;i < N; ++i) buc[x[y[i]]]++;
    for (int i = 0;i < M; ++i) buc[i] += buc[i - 1];
    for (int i = N - 1;i >= 0; --i) sa[--buc[x[y[i]]]] = y[i];
    for (int i = 0;i < N; ++i) printf("%d ", x[i]); printf("\n");

    // 得出新的x
    swap(x, y);
    p = 1, x[sa[0]] = 0;
    for (int i = 1;i < N; ++i) {
      x[sa[i]] = y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? p - 1 : p++;
    }
    if (p >= N) break;
    M = p;
  }

  for (int i = 0;i < N; ++i) printf("%d ", sa[i] + 1); printf("\n");
  return 0;
}
