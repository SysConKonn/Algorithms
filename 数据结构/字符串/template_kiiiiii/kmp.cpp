#include <cstdio>
#include <cstring>
using namespace std;

char s[MAX_N], t[MAX_N];
int fail[MAX_N], n, m;

void getfail() {
  fail[0] = fail[1] = 0;
  for (int i = 2, j = 1; i <= m; ++i) {
    while (j != 0 && t[j + 1] != t[i]) j = fail[j];
    if (t[j + 1] == t[i]) j++;
    fail[i] = j;
  }
}

int getans() {
  int res = 0;
  for (int i = 1, j = 0; i <= n; ++i) {
    while (j != 0 && t[j + 1] != s[i]) j = fail[j];
    if (t[j + 1] == s[i]) j++;
    if (j == m) {
      res++;
      j = fail[j];
    }
  }
  return res;
}
