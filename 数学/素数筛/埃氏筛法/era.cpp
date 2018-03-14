#include <bits/stdc++.h>
#define MAX_N 10000010
#define MAX_M 100100
#define INF 1 << 31 - 1

int N, M;
bool check[MAX_N], prime[MAX_N];
int tot;

int main () {
  scanf("%d%d", &N, &M);

  for (int i = 2;i <= N; ++i) {
    if (!check[i]) {
      prime[i] = true;
      for (int j = i * 2;j <= N; j += i) {
	check[j] = true;
      }
    }
  }

  int q;
  for (int i = 1;i <= M; ++i) {
    scanf("%d", &q);
    if (prime[q]) printf("Yes\n");
    else printf("No\n");
  }
  return 0;
}
