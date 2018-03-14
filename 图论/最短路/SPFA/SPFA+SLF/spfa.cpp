#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#define MAX_N 10000 + 10
#define MAX_M 500000 + 10
#define INF 2147483647
using namespace std;

int N, M, s;
int head[MAX_N], to[MAX_M], nxt[MAX_M], dis[MAX_M], top;
int d[MAX_N];
bool vis[MAX_N];

inline void add_edge (int u, int v, int w) {
    nxt[++top] = head[u];
    head[u] = top;
    to[top] = v;
    dis[top] = w;
}

void spfa () {
    memset(vis, 0, sizeof(vis));
    deque<int> q;
    for (int i = 1;i <= N; ++i) d[i] = i == s ? 0 : INF;
    q.push_front(s), vis[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        for (int i = head[u]; i; i = nxt[i]) {
            int to_ = to[i];
            if (d[to_] > d[u] + dis[i]) {
                d[to_] = d[u] + dis[i];
                if (!vis[to_]) {
                    vis[to_] = true;
                    if (d[q.front()] > d[to_]) q.push_front(to_);
                    else q.push_back(to_);
                }
            }
        }
        vis[u] = false;
    }
}

int main () {
    scanf("%d%d%d", &N, &M, &s);
    int u, v, w;
    for (int i = 1;i <= M; ++i) scanf("%d%d%d", &u, &v, &w), add_edge (u, v, w);
    spfa();
    for (int i = 1;i <= N; ++i) printf("%d ", d[i]); printf("\n");
    return 0;
}