#include <cstdio>
#include <set>
#include <cmath>
#define MAX_N 100100
#define INF 2147483647
using namespace std;

int N, a, g;
struct node {
  int s, id;
  node (int s_, int id_) : s(s_), id(id_) {}
  bool operator < (const node& rhs) const {
    return s < rhs.s;
  }
};
set<node> s;

int min_ (set<node>::iterator a, set<node>::iterator b) {
  if (a -> s < b -> s) return a -> id;
  else if (a -> s > b -> s) return b -> id;
  else return a->id < b->id ? a -> id : b -> id;
}

int main () {
  while (scanf("%d", &N) == 1 && N != 0) {
    s.clear();
    scanf("%d%d", &a, &g);
    printf("%d %d\n", a, 1);
    s.insert(node(a, g));
    for (int i = 3;i <= N + 1; ++i) {
      scanf("%d%d", &a, &g);
      set<node>::iterator pre_ = s.upper_bound(node(a, g))--;
      printf("  %d %d \n", pre_ -> id, pre_ -> s);
      set<node>::iterator nxt_ = s.lower_bound(node(a, g));
      printf("nxt:%d %d\n", nxt_ -> id, nxt_ -> s);
      if (abs(pre_ -> s - g) > abs(nxt_ -> s - g)) printf("%d %d\n", a, nxt_ -> id);
      else if (abs(pre_ -> s - g) < abs(nxt_ -> s - g)) printf("%d %d\n", a, pre_ -> id);
      else printf("%d %d\n", a, min_(pre_, nxt_ ));
      s.insert(node(a, g));
    }
  }
  return 0;
}
