#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <ctime>
#define MAX_N 15010
#define MAX_P 32010
using namespace std;

int N, res[MAX_N];
struct node {
  node* ch[2];
  int v;
  int r;
  int s;
  int re;   //自己重复了几次
  int cmp (int x) {
    if (x == v) return -1;
    return x < v ? 0 : 1;
  }
  void maintain () {
    s = ch[0] -> s + ch[1] -> s + re;
  }
};
node *null, *root;
void init_null () {null = new node(); null -> s = null -> re = 0;null -> v = 0;}

void rot (node* &o, int d) {
  node* k = o -> ch[d];o -> ch[d] = k -> ch[d ^ 1];k -> ch[d ^ 1] = o;
  o -> maintain(); k -> maintain();
  o = k;
}

void ins (node* &o, int x) {
  int d = o -> cmp(x);
  if (o == null) {
    o = new node();
    o -> re = o -> s = 1;
    o -> ch[0] = o -> ch[1] = null;
    o -> v = x;
    o -> r = rand();
  }
  else if (d == -1) {
    o -> re++;
  }
  else {
    ins(o -> ch[d], x);
    if (o -> ch[d] -> r > o -> r) rot(o, d);
  }
  o -> maintain();
}

int sum (node* o, int x) {
  if (o == null) return 0;
  else if (x > o -> v) {
    return o -> ch[0] -> s + o -> re + sum(o -> ch[1], x);
  }
  else if (x == o -> v) {
    return o -> ch[0] -> s + o -> re;
  }
  else return sum(o -> ch[0], x); 
}

int main () {
  srand(0);
  init_null(); root = null;
  scanf("%d", &N);
  int x, y;
  for (int i = 1;i <= N; ++i) {
    scanf("%d%d", &x, &y);
    res[sum(root, x)]++;
    ins(root, x);
  }

  for (int i = 0;i < N; ++i) printf("%d\n", res[i]);
  return 0;
}
