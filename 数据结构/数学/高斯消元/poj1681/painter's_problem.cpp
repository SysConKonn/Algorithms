#include <cstdio>
#include <algorithm> 
#include <cstring>
#include <cmath>
#define MAX_N 230
#define INF 1e8
using namespace std;
int T, N;
int matr[16][16], A[MAX_N][MAX_N], B[MAX_N];
int free_x[MAX_N], free_[MAX_N], cnt = 1, res[MAX_N];
int ans = INF;

void cal() {
  memset(res, 0, sizeof(res));
  int num[MAX_N][MAX_N], b[MAX_N];
  memset(b, 0, sizeof(b));
  memset(num, 0, sizeof(num));
  int sum = 1;

  for (int i = 1;i <= N * N; ++i)
    num[i][i] = A[i][i] == 0 ? free_[sum++] : A[i][i];
  //for (int i = 1;i <= N * N; ++i) printf("%d ", num[i][i]);printf("\n");
  for (int i = 1;i <= N * N; ++i) b[i] = B[i];
  //for (int i = 1;i <= N * N; ++i) printf("%d ", num[i][i]);printf("\n");
  for (int i = N * N; i; --i) {
    for (int j = N * N; j > i; --j) b[i] ^= A[i][j] * res[j];
    res[i] = b[i];
  }
  //for (int i = 1;i <= N * N; ++i) printf("%d ", res[i]);printf("\n");
  int min_ = 0;
  for (int i = 1;i <= N * N; ++i) min_ += res[i];
  ans = min(ans, min_);
  //printf("%d %d\n", ans, min_);
}

void dfs(int now) {
  //printf("%d %d  ", now, cnt);
  if (now >= cnt) {cal();return;}
  for (int i = 0;i <= 1; ++i) {
    free_[now] = i;
    dfs(now + 1);
  }
}

void print_false() {
  printf("inf\n");
}

int check_ () {
  for(int i = 1;i <= N * N; ++i) {
    int sum = 0;
    for(int j = 1;j <= N * N; ++j) if(A[i][j] == 0) sum++;
    if(sum == N * N && B[i] == 1) return 1;
  }
  return 0;
}


void gauss () {
  
  memset(free_x, 0, sizeof(free_x));
  for(int i = 1;i <= N * N; ++i) {
    int k = i;
    for (int j = i+1; j <= N * N; ++j)
      if (A[j][i] > A[k][i]) k = j;
    if(A[k][i] == 0) free_x[i] = 1, free_[cnt++] = i;
    if (k != i){
      //printf("%d %d\n", i, k);
      for (int j = 1; j <= N * N ; ++j) swap(A[i][j], A[k][j]);
      swap(B[i], B[k]);
    }
    
    for(int j = i + 1;j <= N * N; ++j) {
      if(A[j][i] == 0) continue;
      for(int k = 1;k <= N * N; ++k)
	A[j][k] ^= A[i][k];
      B[j] ^= B[i];
    }
  }
  /*
  for (int i = 1;i <= N * N; ++i) {
    for (int j = 1;j <= N * N; ++j) printf("%d ", A[i][j]);
    printf("%d\n", B[i]);
  }
  */
  if(check_() == 1) print_false();
  else {
    /*
    int m = N * N;
    A[m - 1][m - 1] = 1;
    A[m][m] = 1;
    
    for (int i = N * N; i; --i) {
      for (int j = N * N; j > i; --j) B[i] ^= A[i][j] * res[j];
      res[i] = B[i];
    }
    for (int i = 1;i <= N * N; ++i) printf("%d ", res[i]);printf("\n");
    */
    dfs(1);
  }
}

void solve() {
  for (int i = 1;i <= N; ++i) 
    for (int j = 1;j <= N; ++j) 
      for (int k1 = -1;k1 <= 1; ++k1)
	for (int k2 = -1;k2 <= 1; ++k2)
	  if ((i + k1 > 0 && i + k1 <= N && j + k2 > 0 && j + k2 <= N) && (k1 == 0 || k2 == 0))
	    A[matr[i + k1][j + k2]][matr[i][j]] = 1;
  /*
  for (int i = 1;i <= N * N; ++i) {
    for (int j = 1;j <= N * N; ++j) printf("%d ", A[i][j]);
    printf("%d\n", B[i]);
  }
  printf("\n");
  */
  gauss();
  printf("%d\n", ans);
}

void Read () {
  int c;
  for (int i = 1;i <= N; ++i) {
    c = getchar();
    for (int j = 1;j <= N; ++j) {
      c = getchar();
      if (c == 'w') B[matr[i][j]] = 1;
    }
  }
  //for (int i = 1;i <= N * N; ++i) printf("%d ", B[i]);
  //printf("\n");
}

void init() {
 memset(matr, 0, sizeof(matr));
 memset(A, 0, sizeof(A));
 memset(B, 0, sizeof(B));
 memset(free_x, 0, sizeof(free_x));
 memset(free_, 0, sizeof(free_));
 memset(res, 0, sizeof(res));
  int sum = 1;
  for (int i = 1;i <= N; ++i)
    for (int j = 1;j <= N; ++j)
      matr[i][j] = sum++;
}

int main () {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &N);
    init();
    Read();
    solve();
  }
  return 0;
}
