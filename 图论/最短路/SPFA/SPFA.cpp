#include <cstdio>
#include <algorithm>
#include <queue>
#define MAX_N 10005
using namespace std;

int N, M, S;
int head[MAX_N], nxt[MAX_N], to[MAX_N], dis[MAX_N], top = 0;
int vis[MAX_N], num[MAX_N];
int f[MAX_N];
queue<int> G;

void add_(int u, v, d) {
  nxt[top] = head[u];
  head[u] = top;
  to[top] = v;
  dis[top++] = d;
}

void udate() {
  
}

int main() {
  scanf("%d%d%d", &N, &M, &S);
  int u, v, d;
  for(int i = 1;i <= M; i++)
    scanf("%d%d%d", &u, &v, &d), add_(u, v, d);
  G.push(1);
  while(!G.empty()) {
    int now = G.front;
    G.pop();
    for(int i = head[now]; i; i = nxt[i]) {
      update(i, 
    }
  }
  return 0;
}
