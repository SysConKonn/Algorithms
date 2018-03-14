#include <bits/stdc++.h>
#define MAX_L 50000010
#define INF 1 << 31 - 1
using namespace std;

char s[MAX_L], s2[MAX_L];
int rl[MAX_L], maxright, pos;
int N, tot = 1;
int res;

int main () {
  scanf("%s", s2 + 1);
  N = strlen(s2 + 1);
  for (int i = 1;i <= N;i++, tot += 2)
    s[tot - 1] = '#', s[tot] = s2[i];
  s[--tot] = '#';

  maxright = pos = 0;
  fill(rl, rl + tot + 1, 0);
  
  for (int i = 0;i <= tot; ++i) {
    if (i < maxright) rl[i] = min(maxright - i, rl[pos * 2 - i]);
    else rl[i] = 1;

    while (i - rl[i] >= 0 && i + rl[i] <= tot && (s[i + rl[i]] == s[i - rl[i]])) rl[i]++;
    if (rl[i] + i - 1> maxright) {
      maxright = rl[i] + i - 1;
      pos = i;
    }
    res = max(res, rl[i]);
  }

  printf("%d\n", res - 1);
  return 0;
}
