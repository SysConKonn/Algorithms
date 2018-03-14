#include <cstdio>
#include <iostream>
using namespace std;

int N, op, x;

void print (int i, int op ,int x) {
  printf("%d %d %d\n", i, op, x);
}

int main () {
  scanf("%d", &N);
  int top = 0;
  for (int i = 1; i <= N; ++i) {
    scanf("%d%d", &op, &x);
    if (op >= 3) {
      top++;
      if (top == 1390) print(i, op, x);
      if (top == 1746) print(i, op, x);
      if (top == 3158) print(i, op ,x);
      if (top == 3416) print(i, op, x);
      if (top == 3860) print(i, op, x);
    }
    
    
  }
  return 0;
}
