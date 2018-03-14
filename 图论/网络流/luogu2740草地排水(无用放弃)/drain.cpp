#include <cstdio>
#include <csting>
#include <algorithm>
#include <vector>
#include <queue>
#define MAX_N 300
using namespace std;
struct Edge {
  int from, to, cap, flow;
  Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
};
Edge edges;
vector <int> G[MAX_N];
int N, V, s, t;
int dep[MAX_N], tier[MAX_N];

void BFS() {
  queue<int> Q;
  Q.push(t);
  d[t] = 0;
  while (!Q.empty()) {
    int x = Q.front();
    for (int i = 0;i < G[x].size(); ++i) {
      Edge& e = edges[G[x][i]];
      if(!dep[e] && 
    }
  }
}

void solve (int s, int t) {
  int flow = 0;
  BFS();
  memset(tier, 0, sizeof(tier));
  for (int i = 1;i <= N; ++i) tier[d[i]]++;
  int now = s;
  while (d[s] < n) {
    
  }
}

void add_edge(int from, int to, int cap) {
  edges.push_back(Edge(from, to, cap, 0));
  edges.push_back(Edge(to, from, 0, 0));
  int m = edges.size();
  G[from].push_back(m - 2);
  G[to].push_back(m - 1);
}

int main () {
  scanf("%d%d", &V, &N);
  s = 1, t = N;
  for (int i = 1;i < V; ++i) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    add_edge(u, v, c);
  }
  solve (s, t);
  return 0;
}
