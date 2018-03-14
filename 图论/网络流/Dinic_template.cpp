#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define MAX_N 10001
#define INF 10000001
using namespace std;

struct Edge {
  int from, to, cap, flow;
  Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
};
vector<Edge> edges;
vector<int> G[MAX_N];
int N, M, s, t;
int cur[MAX_N], dep[MAX_N];

void add_edge (int from, int to, int cap) {
  edges.push_back(Edge(from, to, cap, 0));
  edges.push_back(Edge(to, from, 0, 0));
  int m = edges.size();
  G[from].push_back(m - 2);
  G[to].push_back(m - 1);
}

bool BFS() {
  memset(dep, 0, sizeof(dep));
  queue<int> Q;
  Q.push(s);
  dep[s] = 0;
  while (!Q.empty()) {
    int now = Q.front();
    Q.pop();
    for (int i = 0;i < G[now].size(); ++i) {
      Edge& e = edges[G[now][i]];
      if (e.to == s) continue;
      if (!dep[e.to] && e.cap > e.flow) {
	dep[e.to] = dep[now] + 1;
	Q.push(e.to);
      }
    }
  }
  return dep[t];
}

int DFS(int x, int a) {
  if (x == t || a == 0) return a;
  int flow = 0, f;
  for (int& i = cur[x];i < G[x].size(); ++i) {
    Edge& e = edges[G[x][i]];
    if (dep[e.to] == dep[x] + 1 && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
      e.flow += f;
      edges[G[x][i] ^ 1].flow -= f;
      flow += f;
      a -= f;
      if (a == 0) break;
    }
  }
  return flow;
}

int Max_Flow () {
  int flow = 0;
  while(BFS()) {
    memset(cur, 0, sizeof(cur));
    flow += DFS(s, INF);
  }
  return flow;
}

int main () {
  scanf("%d%d%d%d", &N, &M, &s, &t);
  for (int i = 1;i <= M; ++i) {
    int u, v, d;
    scanf("%d%d%d", &u, &v, &d);
    add_edge(u, v, d);
  }
  printf("%d\n", Max_Flow());
}
