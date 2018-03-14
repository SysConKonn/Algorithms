#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAX_N 100010
#define INF 2147483647
using namespace std;
struct Node {
  Node* ch[2];
  int r;
  int v;
  int sz;
  int cmp (int x) {
    if (x == v) return -1;
    else return x < v ? 0 : 1;
  }
  void maintain () {
    sz = 1;
    if (ch[0] != NULL) sz += ch[0] -> sz;
    if (ch[1] != NULL) sz += ch[1] -> sz;
  }
};

void rot (Node* &o, int d) {
  Node* k = o -> ch[d]; o -> ch[d] = k -> ch[d ^ 1]; k -> ch[d ^ 1] = o; o = k;
  o -> maintain(); k -> maintain();
  o = k;
}

int root, 

int main () {
  
  return 0;
}
