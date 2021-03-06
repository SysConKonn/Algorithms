#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MOD 9875321
#define MAX_N 150010
using namespace std;

int N, M;
char s[MAX_N];
int p[MAX_N], id[MAX_N], sz[MAX_N], size, fa[MAX_N], c[MAX_N][2];
int v[MAX_N], h[MAX_N];
int root;

void build (int, int, int);
void update (int );
void splay (int, int&);
void rotate (int, int&);
int query (int, int);
int find (int, int);
int split (int, int);
int lcq (int, int);
void change (int, char);
void insert(int, char);

int main () {
    scanf("%s", s + 2);
    N = strlen(s + 2);
    //for (int i = 0;i <= N; ++i) printf("%c", s[i]); printf("\n");
    p[0] = 1; for (int i = 1;i <= MAX_N; ++i) p[i] = p[i - 1] * 27 % MOD;
    for (int i = 1;i <= N + 2; ++i) id[i] = i;
    build (1, N + 2, 0);
    size = N + 2, root = (N + 3) >> 1;
    scanf("%d", &M);
    char op[2];
    for (int i = 1;i <= M; ++i) {
    scanf("%s", op);
    //printf(" %c\n", op[0]);
    if (op[0] == 'Q') {
        int l, r;
        scanf("%d%d", &l, &r);
        // printf("  %d %d\n", l, r);
        printf("%d\n", query(l, r));
    }
    else if (op[0] == 'R') {
        int pos; char cc[2];
        scanf("%d%s", &pos, cc + 1);
        change(pos, cc[1]);
    }
    else if (op[0] == 'I') {
        int pos; char cc[2];
        scanf("%d%s", &pos, cc);
        insert(pos, cc[0]);
    }
    }
    return 0;
}

void build (int l, int r, int f) {
    if (l > r) return;
    int mid = (l + r) >> 1, now = id[mid], last = id[f];
    fa[now] = last;
    if (l == r) {
    v[now] = h[now] = s[mid] - 'a' + 1;
    fa[now] = last; sz[now] = 1;
    c[last][mid >= f] = now;
    return;
    }
    build(l, mid - 1, mid), build(mid + 1, r, mid);
    v[now] = s[mid] - 'a' + 1, fa[now] = last;
    update(now);
    c[last][mid >= f] = now;
}

void update (int x) {
    int l = c[x][0], r = c[x][1];
    sz[x] = sz[l] + sz[r] + 1;
    h[x] = h[l] + (long long) v[x] * p[sz[l]] % MOD + (long long) p[sz[l] + 1] * h[r] % MOD;
    h[x] %= MOD;
}

void splay (int x, int& k) {
    while (x != k) {
    int y = fa[x], z = fa[y];
    if (y != k)
        if (c[y][0] == x ^ c[z][0] == y) rotate (x, k);
        else rotate(y, k);
    rotate(x, k);
    }
}

void rotate (int x, int& k) {
    int y = fa[x], z = fa[y];
    int l = c[y][1] == x, r = l ^ 1;
    if (y == k) k = x;
    else c[z][c[z][1] == y] = x;
    fa[x] = z, fa[y] = x, fa[c[x][r]] = y;
    c[y][l] = c[x][r], c[x][r] = y;
    update(y), update(x);
}

int find (int x, int k) {
    int l = c[x][0], r = c[x][1];
    if (sz[l] + 1 == k) return x;
    else if (sz[l] >= k) return find(l, k);
    else return find(r, k - sz[l] - 1);
}

int split (int l, int r) {
    int x = find(root, l), y = find(root, r);
    // printf("split%d %d\n", x, y);
    splay(x, root);splay(y, c[root][1]);
    return c[y][0];
}

int query (int x, int y) {
    int l = 1, r = min(size - x, size - y) - 1, mid, ans = 0;
    while (l <= r) {
        mid = (l + r) >> 1;
    if (lcq(x, mid) == lcq(y, mid)) ans = mid, l = mid + 1;
    else r = mid - 1;
    }
    return ans;
}

void print (int x) {
    if (!x) return;
    print(c[x][0]);
    printf("%d %c\n", x - 1, v[x] + 'a' - 1);
    print(c[x][1]);
}

int lcq (int k, int tot) {
    int x = split(k, k + tot + 1);
    //printf("%d %d:\n", k, k + tot - 1);
    //print(x);printf("  %d\n", h[x]);
    //printf(" %d %c\n", x, v[x] + 'a' - 1);
    return h[x];
}

void change (int pos, char c) {
    int x = find(root, pos + 1);
    splay(x, root);
    v[root] = c - 'a' + 1;
    update(root);
}

void insert (int pos, char cc) {
    int x = find(root, pos + 1), y = find(root, pos + 2);
    splay(x, root);splay(y, c[root][1]);
    int z = ++size;
    v[z] = cc - 'a' + 1;
    fa[z] = y, c[y][0] = z;
    update(z), update(y), update(x);
}
