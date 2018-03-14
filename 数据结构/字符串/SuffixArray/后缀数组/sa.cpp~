#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#define MAX_N 1000100
using namespace std;

char s[MAX_N];
int buc[MAX_N], x[MAX_N], y[MAX_N], sa[MAX_N];
int N, M = 128;

int main () {
  scanf("%s", s);
  N = strlen(s);
  memset(buc, 0, sizeof(buc));
  for (int i = 0;i < N; ++i) buc[x[i] = s[i]]++;
  for (int i = 0;i < M; ++i) buc[i] += buc[i - 1];  //求前缀和
  for (int i = N - 1;i >= 0; --i) sa[--buc[x[i]]] = i;

  for (int k = 1;k <= N; k *= 2) {
    int p = 0;
    //算出第二元
    for (int i = N - k;i < N; ++i) y[p++] = i;
    for (int i = 0;i < N; ++i) if (sa[i] >= k) y[p++] = sa[i] - k;

    //基数排序
    memset(buc, 0, sizeof(buc));
    for (int i = 0;i < N; ++i) buc[x[y[i]]]++;
    for (int i = 0;i < M; ++i) buc[i] += buc[i - 1];
    for (int i = N - 1;i >= 0; --i) sa[--buc[x[y[i]]]] = y[i];

    //得出新的x数组
    swap(x, y);  //y数组无用了，x数组需要新的，但还需用原来的，把x附到y废品回收
    p = 1;x[sa[0]] = 0;
    for (int i = 1;i < N; ++i) {
      x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
    }
    if (p >= N) break;
    M = p;
  }

  for (int i = 0;i < N; ++i) printf("%d ", sa[i] + 1);
  printf("\n");
  return 0;
}
