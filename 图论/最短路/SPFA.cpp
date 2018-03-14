#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#define MAX_N 10010
#define MAX_M 500010
#define INF 2147483647
typedef long long ll;
using namespace std;
struct Edge {
	int from, to, dist;
	Edge(int u, int v, int d) : from(u), to(v), dist(d) {}
};
vector <Edge> edges;
vector <int> G[MAX_M];

int N, M, s;
bool vis[MAX_N];
ll d[MAX_N];

void add_edge (int from, int to, int dist) {
	edges.push_back(Edge(from, to, dist));
	int m = edges.size();
	G[from].push_back(m - 1);
}

void spfa (int s) {
	memset(vis, false, sizeof(vis));
	queue<int> Q;
	Q.push(s);
	fill (d, d + N + 1, INF);
	d[s] = 0;
	while (!Q.empty()) {
		int x = Q.front();
		Q.pop();
		for (int i = 0;i < G[x].size(); ++i) {
		 	Edge& e = edges[G[x][i]];
			if (d[e.to] > d[x] + e.dist) {
				d[e.to] = d[x] + e.dist;
				if (!vis[e.to]) {
					vis[e.to] = true;
					Q.push(e.to);
				}
			}		 	
		}
		vis[x] = false;
		//printf("\n");
	}

	for (int i = 1;i <= N; ++i) printf("%lld ", d[i]);
	printf("\n");
}

int main () {
	scanf("%d%d%d", &N, &M, &s);
	for (int i = 1;i <= M; ++i) {
		int u, v, d;
		scanf("%d%d%d", &u, &v, &d);
		add_edge(u, v, d);
	}
	spfa(s);
	return 0;
}