#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#define MAX_N 1005
using namespace std;

// problem
int N;
double matr[MAX_N][MAX_N];

// record
double free_line[MAX_N];

void cal () {
  matr[N][N + 1] /= matr[N][N];
  for(int i = N - 1;i > 0; --i) {  // 处理每一行
    double sum = 0;
    for(int j = i + 1; j <= N; ++j) {
      sum += matr[i][j] * matr[j][N + 1];
      //printf("%lf  %lf  %lf\n", matr[i][j], matr[j][N + 1], sum);
    }
    matr[i][N + 1] = (matr[i][N + 1] - sum) / matr[i][i];
  }

  for(int i = 1;i <= N; ++i)
    printf("%.2lf\n", matr[i][N + 1]);
}

void solve () {
  /*
  for(int i = 1;i <= N; ++i) {
    for(int j = 1;j <= N + 1; ++j)
      printf("%lf ", matr[i][j]);
    printf("\n");
  }
  */

  for(int tot = 1;tot < N; ++tot) {
    double stan = matr[tot][tot];
    for(int i = tot + 1;i <= N; ++i) {   //把tot列的元都消掉
      if(matr[i][tot] == 0) continue;
      double now = matr[i][tot] / stan;
      //printf("%lf\n", now);
      for(int j = 1;j <= N + 1; ++j) {
	matr[i][j] -= matr[tot][j] * now;
	//printf(" %lf\n", matr[tot][j] * now);
      }
    }
  }
  /*
  for(int i = 1;i <= N; ++i) {
    for(int j = 1;j <= N + 1; ++j)
      printf("%lf ", matr[i][j]);
    printf("\n");
  }
  */

  if(matr[N][N] == 0) {printf("No Solution\n");exit(0);}
  else cal();
}

int main () {
  scanf("%d", &N);
  for(int i = 1;i <= N; ++i)
    for(int j = 1;j <= N + 1; ++j) {
      scanf("%lf", &matr[i][j]);
      if(matr[i][j] == 0) free_line[j]++;
    }

  // special situation
  for(int i = 1;i <= N; ++i)
    if(free_line[i] == N) {
      printf("No Solution\n");
      return 0;
    }

  solve();
  return 0;
}
