#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAX_N 10001
#define INF 2147483647
using namespace std;

int root = 1, tot = 1;
int s[MAX_N][2], fa[MAX_N];
int siz[MAX_N];
int w[MAX_N], aux[MAX_N];

int up (int& i) {return siz[s[i][0]] + siz[s[i][1]];}

void rot (int& x) {
  int y = fa[x], g = fa[y], c = s[y][1] == x;
  s[y][c] = s[x][c ^ 1], fa[s[y][c]] =  y;
  s[x][c ^ 1] = y, fa[y] = x;
  fa[x] = g;
  if (g) {
    s[g][s[g][1] == y] = x;
  }
  up(y), up(x), up(g);
}

void ins (int x, int& i, int fa_) {
  //printf("%d %d -fa-> %d\n", x, i, fa_);
  if (!i) {
    i = ++tot;
    fa[i] = fa_;
    s[fa[i]][x >= w[fa_]] = i;
    siz[i] = 1;
    w[i] = x;
    aux[i] = rand();
    //printf("new!: %d -fa-> %d size:%d w:%d aux:%d s[%d][%d]:i\n", i, fa[i], siz[i], w[i], aux[i], fa[i], x >= w[fa_]);
    return;
  }
  siz[i]++;
  if (x < w[i]) {
    ins(x, s[i][0], i);
    //if (aux[s[i][0]] > aux[i]) rot(i);
  }
  else {
    //printf("%d %d\n", i, fa[i]);
    ins(x, s[i][1], i);
    //if (aux[s[i][1]] > aux[i]) rot(i);
  }
}

void del (int x, int& i) {
  if (w[i] == x) {
    if (s[i][0] * s[i][1] == 0) {
      i = s[i][0] + s[i][1];
      return;
    }
    else if (aux[s[i][0]] < aux[s[i][1]]) {
      aux[i] = INF;
      rot(s[i][0]);
      del(x, s[i][0]);
    }
    else {
      aux[i] = INF;
      rot(s[i][1]);
      del(x, s[i][1]);
    }
  }
  else if (w[i] > x) siz[i]--, del(x, s[i][0]);
  else siz[i]--, del(x, s[i][1]);
  up (i);
}

int find_ (int x, int i) {
  //printf("%d %d size:%d\n", x, i, siz[i]);
  if (!i) return 1;
  if (w[i] >= x) return find_(x, s[i][0]);
  return find_(x, s[i][1]) + siz[s[i][0]] + 1;
}

int query (int x, int i) {
  if (siz[s[i][0]] == x - 1) return w[i];
  if (siz[s[i][0]] >= x) return query(x, s[i][0]);
  return query(x - siz[s[i][0]] - 1, s[i][1]);
}

int get_pre (int x, int i) {
  if (!i) return -INF;
  if (w[i] < x) return max(w[i], get_pre(x, s[i][1]));
  else return get_pre(x, s[i][0]);
}

int get_nxt (int x, int i) {
  if (!i) return INF;
  if (w[i] > x) return min(w[i], get_nxt(x, s[i][0]));
  else return get_nxt(x, s[i][1]);
}

int main () {
  //freopen ("in.txt", "r", stdin);
  //srand(time(0));
  int T;
  scanf("%d", &T);
  while (T--) {
    int op, x;
    scanf("%d%d", &op, &x);
    if (op == 1) {
      if (!w[root]) {
	w[root] = x;
	siz[root] = tot;
	aux[root] = rand();
      }
      else ins(x, root, 0);
    } 
    else if (op == 2) {
      del(x, root);
    }
    else if (op == 3) {
      printf("%d\n", find_(x, root));
    }
    else if (op == 4) {
      printf("%d\n", query(x, root));
    }
    else if (op == 5) {
      printf("%d\n", get_pre(x, root));
    }
    else if (op == 6) {
      printf("%d\n", get_nxt(x, root));
    }
  }
  return 0;
}
