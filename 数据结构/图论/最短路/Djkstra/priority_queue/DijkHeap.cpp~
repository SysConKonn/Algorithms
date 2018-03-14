#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#define MAX_N 5000
#define INF 2147483647
using namespace std;

struct Edge {
  int from, to, dist;
  Edge(int u, int v, int w) : from(u), to(v), dist(w) {}
};

struct HeadNode {
  int d, u;
  bool operator < (const HeadNode& rhs) const {
    return d > rhs.d;
  }
};

struct Djkstra {
  int n, m; // point num:n, edge num: m
  vector<Edge> edges; // the detail information
  vector<int> G[MAX_N]; // the serial number number of every edge
  bool done[MAX_N];
  int d[MAX_N]; // every distance from u
  int p[MAX_N]; // arc of the graph
  vector<int> t;

  void init (int n) {
    this->n = n;
    for (int i = 0;i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge (int from, int to, int dist) {
    edges.push_back(Edge(from, to, dist));
    int ml = edges.size();
    G[from].push_back(ml - 1);
    return;
  }

  void AddTime (int time) {
    t.push_back(time);
  }

  int find (int s) {
    priority_queue<HeadNode> Q;
    for(int i = 0;i < n; i++) d[i] = INF;
    d[s] = 0;
    memset(done, 0, sizeof(done));
    Q.push((HeadNode){0, s});

    while (!Q.empty()) {
      HeadNode x = Q.top();Q.pop();
      int u = x.u;
      if(done[u]) continue;
      done[u] = true;
      for(int i = 0;i < G[u].size(); i++) {
	Edge& e = edges[G[u][i]];
	//if(tl > t[e.from] || tl > t[e.to]) continue;
	if(d[e.to] > d[u] + e.dist) {
	  d[e.to] = d[u] + e.dist;
	  Q.push((HeadNode){d[e.to], e.to});
	}
      }
    }

    for(int i = 0;i < n; i++) printf("%d ", d[i]);
    printf("\n");
  }
};

int main() {
  Djkstra p;
  scanf("%d%d", &p.n, &p.m);
  int from, to, dist;
  for(int i = 0;i < p.m; i++) {
    scanf("%d%d%d", &from, &to, &dist);
    p.AddEdge(from, to, dist);
    p.AddEdge(to, from, dist);
  }
  for(int i = 0;i < p.n; i++) p.find(i);
  return 0;
}
