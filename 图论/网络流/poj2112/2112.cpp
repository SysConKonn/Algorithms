#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <iostream>
#define INF 0x3f3f3f3f
#define MAX_N 300 
using namespace std;
typedef int cap_type;
#define MAX_V 200 + 30 + 16
int g[MAX_V][MAX_V];
int K, C, M, V;
#define MAX_V 200 + 30 + 16
 
// 用于表示边的结构体（终点、容量、反向边）
struct edge
{
	int to, rev;
	cap_type cap;
 
	edge(int to, cap_type cap, int rev) : to(to), cap(cap), rev(rev)
	{}
};
 
vector <edge> G[MAX_V];   // 图的邻接表表示
int level[MAX_V];      // 顶点到源点的距离标号
int iter[MAX_V];       // 当前弧，在其之前的边已经没有用了
 
// 向图中加入一条从from到to的容量为cap的边
void add_edge(int from, int to, int cap)
{
	G[from].push_back(edge(to, cap, G[to].size()));
	G[to].push_back(edge(from, 0, G[from].size() - 1));
}
 
// 通过BFS计算从源点出发的距离标号
void bfs(int s)
{
	memset(level, -1, sizeof(level));
	queue<int> que;
	level[s] = 0;
	que.push(s);
	while (!que.empty())
	{
		int v = que.front();
		que.pop();
		for (int i = 0; i < G[v].size(); ++i)
		{
			edge &e = G[v][i];
			if (e.cap > 0 && level[e.to] < 0)
			{
				level[e.to] = level[v] + 1;
				que.push(e.to);
			}
		}
	}
}
 
// 通过DFS寻找增广路
cap_type dfs(int v, int t, cap_type f)
{
	if (v == t)
	{
		return f;
	}
	for (int &i = iter[v]; i < G[v].size(); ++i)
	{
		edge &e = G[v][i];
		if (e.cap > 0 && level[v] < level[e.to])
		{
			cap_type d = dfs(e.to, t, min(f, e.cap));
			if (d > 0)
			{
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
 
	return 0;
}
 
// 求解从s到t的最大流
cap_type max_flow(int s, int t)
{
	cap_type flow = 0;
	for (;;)
	{
		bfs(s);
		if (level[t] < 0)
		{
			return flow;
		}
		memset(iter, 0, sizeof(iter));
		cap_type f;
		while ((f = dfs(s, t, 0x3f3f3f3f3f3f3f3f)) > 0)
		{
			flow += f;
		}
	}
}

bool check (int lim) {
  int s = V, t = V + 1;
  for (int i = 0; i < V + 2; i++)
    {
      G[i].clear();
    }
  for (int i = 0; i < K; ++i)
    add_edge(i, t, M);
  for (int i = K;i < V; ++i)
    add_edge(s, i, 1);
  for (int i = 0;i < K; ++i)
    for (int j = K;j < V; ++j)
      if (g[i][j] <= lim) add_edge(j, i, 1);
  return max_flow(s, t) == C;
}
int solve () {
  for (int k = 0;k < V; ++k)
    for (int i = 0;i < V; ++i)
      for (int j = 0;j < V; ++j)
	g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
  int l = 0, r = V * 200, mid;
  while (r - l > 1) {
    mid = (r + l) / 2;
    (check(mid) ? r : l) = mid;
  }
  return r;
}
int main(int argc, char *argv[])
{
	scanf("%d%d%d", &K, &C, &M);
	V = K + C;
	for (int i = 0; i < K + C; ++i)
	{
		for (int j = 0; j < K + C; ++j)
		{
			int d;
			scanf("%d", &d);
			g[i][j] = d ? d : INF;
		}
	}
	printf("%d\n", solve());
	return 0;
}

