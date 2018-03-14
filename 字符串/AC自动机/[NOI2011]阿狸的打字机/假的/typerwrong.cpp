// 用树状数组代替麻烦的大法师(DFS)搜寻fail树
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>
#define MAX_N 100010
#define INF 2147483647
using namespace std;

int ch[MAX_N][30], sz = 1, book[MAX_N], fa[MAX_N], flag;

char t[MAX_N], s[1000][1000], stk[MAX_N];
int cap, M;

int head[MAX_N];

int fail[MAX_N];

void _print (int k) {
  for (int i = 0;i <= k; ++i) 
    s[cap][i] = stk[i];
  cap++;
}


int idx (char c) {return c - 'a';}

void del (int& x, char c) {
  int a = x;
  //printf(" %d %c %d\n", x, c, fa[x]);
  x = fa[x];
  if (!flag) return;
  //printf("  %d %c %d\n", a, c, x);
  ch[x][idx(c)] = 0;
  sz--;
}

void Read () {
  char now;
  int _ipos[MAX_N];
  memset(_ipos, 0, sizeof(_ipos));
  int len_ = strlen(t), u = 0;
  for (int i = 0;i < len_; ++i) {
    if (t[i] == 'B') {del(u, ); flag--; continue;}
    else if (t[i] == 'P') {book[cap++] = u;flag = 0;continue;}
    int c = idx(t[i]);
    if (ch[u][c]) continue;
    //printf("%d %c %d\n", u, t[i], sz);
    flag++;
    now = t[i];
    memset(ch[sz], 0, sizeof(ch[sz]));
    ch[u][c] = sz++;
    fa[sz - 1] = u;
    //printf("%d %c %d\n", u, t[i], ch[u][c]);
    u = ch[u][c];
  }
  
  for (int i = 0;i < sz; ++i)
    for (int j = 0;j < 26; ++j)
      if (ch[i][j]) printf("%d %c %d\n", i, j + 'a', ch[i][j]);
  
}

void getfail () {
  queue<int> q;
  fail[0] = 0;
  for (int i = 0;i < 26; ++i) {
    int u = ch[0][i];
    if (u) q.push(u), fail[u] = 0;
  }

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int i = 0;i < 26; ++i) {
      if (!ch[u][i]) continue;
      q.push(ch[u][i]);
      int v = fail[u];
      while (v && !ch[v][i]) v = fail[v];
      fail[ch[u][i]] = ch[v][i];
    }
  }

  for (int i = 0;i < sz; ++i) printf("%d\n", fail[i]);
}

int main () {
  scanf("%s", t);
  Read();

  scanf("%d", &M);
  // for (int i = 1;i <= M; ++i)

  getfail();

  return 0;
}
