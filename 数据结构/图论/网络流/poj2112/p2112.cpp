#include <bits/stdc++.h>
#define MAX_N 300
#define INF 2147483647
using namespace std;
struct Edge {
  int to, cap, rev;
  Edge(int v, int c, int r) : to(v), cap(c), rev(r) {}
};
vector <Edge> edges[MAX_N];

int K, C, M, V;
int dis[MAX_N][MAX_N];
int dep[MAX_N], idep[MAX_N];
int s, t;

void bfs (int s) {
  memset(dep, -1, sizeof(dep));
  memset(idep, 0, sizeof(idep));
  queue<int> Q;
  while (!Q.empty()) Q.pop();
  dep[s] = 0;
  idep[0]++;
  Q.push(s);
  while (!Q.empty()) {
    int now = Q.front();
    Q.pop();
    for (int i = 0;i < edges[now].size(); ++i) {
      Edge& e = edges[now][i];
      if(e.cap > 0 && dep[e.to] < 0) {
	dep[e.to] = dep[now] + 1;
	idep[dep[e.to]]++;
	Q.push(e.to);
      }
    }
  }
}

int find_ (int x, int u) {
  for (int i = 0;i < edges[u].size(); ++i)
    if(edges[u][i].to == x) return i;
}

int dfs (int now, int flow) {
  //printf("OK");
  if(now == t) return flow;
  for(int i = 0;i < edges[now].size(); ++i) {
    Edge& e = edges[now][i];
    if((dep[e.to] == dep[now] + 1) && (e.cap > 0)) {
      int f = dfs(e.to, min(flow, e.cap));
      if(f > 0) {
	e.cap -= f;
	edges[e.to][find_(now, e.to)].cap += f;
	return f;
      }
    }
  }
  return 0;
}

int dinic (int s, int t) {
  int res = 0;
  int d = 0;
  for (;;) {
    bfs(s);
    if(dep[t] < 0) return res;
    while(d = dfs(s, INF)) res += d;
  }
  return res;
}

void add_(int from, int to, int cap) {
  edges[from].push_back(Edge(to, cap, edges[to].size()));
  edges[to].push_back(Edge(from, 0, edges[from].size() - 1));
}

bool check (int maxx) {
  s = V + 1, t = V + 2;
  for (int i = 1;i <= t; ++i) edges[i].clear();

  //set path
  for (int i = 1;i <= K; ++i)
    add_(i, t, M);
  for (int i = K + 1;i <= V; ++i)
    add_(s, i, 1);
  for (int i = 1;i <= K; ++i)
    for (int j = K + 1;j <= V; ++j)
      if (dis[i][j] <= maxx) add_(j, i, 1);
  if (dinic(s, t) == C) return true;
  return false;
}

int solve () {
  //Floyd
  for (int k = 1;k <= V; ++k)
    for (int i = 1;i <= V; ++i)
      for (int j = 1;j <= V; ++j)
	dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

  //BinSearch
  int l = 0, r = V * 200, mid;
  //printf("%d %d\n", l, r);
  while (r - l > 1) {
    
    mid = (l + r) / 2;
    printf("%d %d %d\n", l, r, mid);
    if (check(mid)) r = mid;
    else l = mid;
  }
  printf("%d %d %d\n", l, r, mid);
  return r;
}

int main () {
  scanf("%d%d%d", &K, &C, &M);
  V = K + C;
  for (int i = 1;i <= V; ++i)
    for (int j = 1;j <= V; ++j) {
      int d;
      scanf("%d", &d);
      dis[i][j] = d ? d : INF;
    }
  int ress = solve();
  printf("%d\n", ress);
  return 0;
}
