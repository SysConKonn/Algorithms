#include <bits/stdc++.h>
#define MAX_N 10000100
#define INF 1 << 31 - 1
using namespace std;

int N, M;
bool check[MAX_N], is_prime[MAX_N];
int prime[MAX_N];
int tot;

int main () {
  scanf("%d%d", &N, &M);
  for (int i = 2; i <= N; ++i) {
    if (!check[i]) is_prime[i] = true, prime[++tot] = i;
    for (int j = 1;j <= tot; ++j) {
      if (i * prime[j] > N) break;
      check[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }

  int q;
  for (int i = 1;i <= M; ++i) {
    scanf("%d", &q);
    if (is_prime[q]) printf("Yes\n");
    else printf("No\n");
  }
  return 0;
}
