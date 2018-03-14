#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#define MAX_N 30
using namespace std;

int fr[MAX_N], be[MAX_N];
int A[MAX_N][MAX_N], B[MAX_N];
int free_x[MAX_N];
int N;

int check_ () {
  for(int i = 1;i <= N; ++i) {
    int sum = 0;
    for(int j = 1;j <= N; ++j) if(A[i][j] == 0) sum++;
    if(sum == N && B[i] == 1) return 1;
  }
  return 0;
}

void print_false () {
  printf("Oh,it's impossible~!!\n");
}

void cal () {
  int res = 1;
  
  for(int i = 1;i <= N; ++i)
    if(free_x[i]) res *= 2;
  printf("%d\n", res);
}

void gauss () {
  memset(free_x, 0, sizeof(free_x));
  for(int i = 1;i <= N; ++i) {
    int k = i;
    for (int j = i+1; j <= N; ++j)
      if (A[j][i] > A[k][i]) k = j;
    if(A[k][i] == 0) free_x[i] = 1;
    if (k != i){
      for (int j = 1; j <= N; ++j) std::swap(A[i][j], A[k][j]);
      std::swap(B[i], B[k]);
    }
    
    for(int j = i + 1;j <= N; ++j) {
      if(A[j][i] == 0) continue;
      for(int k = 1;k <= N; ++k)
	A[j][k] ^= A[i][k];
      B[j] ^= B[i];
    }
  }
  if(check_() == 1) print_false();
  else cal();
}

void solve () {
  //Read()
  scanf("%d", &N);
  for(int i = 1;i <= N; ++i)
    scanf("%d", &fr[i]);
  for(int i = 1;i <= N; ++i) {
    scanf("%d", &be[i]);
    B[i] = fr[i] ^ be[i];
  }

  int a, b;
  for(int i = 1;i <= N; ++i) A[i][i] = 1;
  while(scanf("%d%d", &a, &b) == 2 && a != 0 && b != 0) 
    A[b][a] = 1;

  gauss();
}

void init () {
  memset(fr, 0, sizeof(fr));
  memset(be, 0, sizeof(be));
  memset(A, 0, sizeof(A));
  memset(B, 0, sizeof(B));
}

int main () {
  int ntot;
  scanf("%d", &ntot);
  while(ntot--) {
    init();
    solve();
  }
  return 0;
}
