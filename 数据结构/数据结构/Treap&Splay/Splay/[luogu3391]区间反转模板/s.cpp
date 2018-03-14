#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#define MAX_N 100100
#define INF 2147483647
using namespace std;
int N, M;

struct node {
  node* ch[2];
  node* pre[2];
  int v, id;
  int book;
  int cmp (int x) {if (x == v) return -1; return x < v ? 0 : 1;}
  void pushdown () {
    ch[0] -> book ^= book;
    ch[1] -> book ^= book;
  }
};
node *null, *root;
void init_null() {null = new node(); null -> v = INF;}
void init_root() {root = null; root -> pre = null;}

void rot (node* &o , int d) {
  node* k = o -> ch[d];
  o -> ch[d] = k -> ch[d ^ 1];o -> ch[d] -> pre = o;
  k -> ch[d ^ 1] = o;o -> pre = k;
  o = k;
}

void ins (node* &o, int x, int id_) {
  if (o == null) {
    o = new node();
    o -> ch[0] = o -> ch[1] = null;
    o -> v = x;
    o -> id = id_;
    o -> ch[0] -> pre = o;
    o -> ch[1] -> pre = o;
  }
  else {
    int d = o -> cmp(x);
    ins (o -> ch[d], x);
  }
}

void to_root (node* &o, int l) {
  if (o -> pre == null) return;
  else if (o -> id == l) {
    if (o -> pre -> pre == null) { //该结点只需要旋转一次了
      int d = o -> pre -> cmp(o -> id);
      rot(o -> pre, d);
    }
    else {
      int id1 = o -> id, id2 = o -> pre -> id;
      node *fa = o -> pre, *g = fa -> pre;
      int d1 = fa -> cmp(id1);
      int d2 = g -> cmp(id2);
      if (d1 = d2) {
	rot(g, d2);
	rot(fa, d1);
      }
      else if (d1 ^ d2 = 1) { //扭曲，自己旋转两次
	rot(fa, d1);
	rot(g, d2);
      }
    }
    root = o;
  }
  else {
    int d = o -> cmp(l);
    to_root(o -> ch[d], l);
  }
}

void to_right (node* &o, int r) {
  if (o -> pre == root) return;
  else if (o -> id == r) {
    
  }
  else {
    int d = o -> cmp(r);
    to_right(o -> ch[d], r);
  }
}

int main () {
  init_null(); init_root();
  scanf("%d%d", &N, &M);

  for (int i = 0;i <= M; ++i) ins(root, i, i);
  
  for (int i = 1;i <= M; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    l--, r--;
    to_root(root, l);
  }
  return 0;
}
