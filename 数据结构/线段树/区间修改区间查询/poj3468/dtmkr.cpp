#include <bits/stdc++.h>
using namespace std;

int main () {
  freopen("p.in", "w", stdout);
  srand(time(0));
  int N, Q;
  N = rand() % 1000;
  Q = rand() % 1000;
  printf("%d %d\n", N, Q);
  for (int i = 1;i <= N; ++i) {
    int a = rand() % 10000000;
    printf("%d ", a);
  }
  printf("\n");
  for (int i = 1;i <= Q; ++i) {
    int cnt = rand()%6;
    if (cnt % 2 == 1) {
      int a = rand() % N, b = rand() % N, c = rand() % 10000000;
      printf("C %d %d %d\n", a, b, c);
    }
    else {
      int a = rand() % N, b = rand() % N;
      printf("Q %d %d\n", a, b);
    }
  }
  return 0;
}
