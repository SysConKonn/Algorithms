#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LL;
const int Maxn = 100005, MOD = 12580;
int sa[Maxn], x[Maxn], y[Maxn], rk[Maxn], he[Maxn], c[50];
char s[Maxn];

int idx(char c) {
  return c-'a';
}

void build_sa(int n, int m) {
  for (int i = 0; i <= m; ++i) c[i] = 0;
  for (int i = 1; i <= n; ++i) c[x[i]=idx(s[i])]++;
  for (int i = 1; i <= m; ++i) c[i] += c[i-1];
  for (int i = n; i; --i) sa[c[x[i]]--] = i;
  for (int k = 1, p; k <= n; k <<= 1) {
    p = 0;
    for (int i = 0; i <= m; ++i) c[i] = 0;
    for (int i = 1; i <= n; ++i) if (sa[i] > n-k) y[++p] = sa[i];
    for (int i = 1; i <= n; ++i) if (sa[i] > k) y[++p] = sa[i]-k;
    for (int i = 1; i <= n; ++i) c[x[y[i]]]++;
    for (int i = 1; i <= m; ++i) c[i] += c[i-1];
    for (int i = n; i; --i) sa[c[x[y[i]]]--] = y[i];
    swap(x, y);
    p = 1, x[sa[1]] = 0;
    for (int i = 2; i <= n; ++i)
      x[sa[i]] = y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k] ? p-1: p++;
    if (p >= n) break;
    m = p;
  }
}

void getheight(int n) {
  for (int i = 1; i <= n; ++i) rk[sa[i]] = i;
  for (int i = 1, k = 0; i <= n; ++i) {
    if (k) --k;
    int j = sa[rk[i]-1];
    while (s[i+k] == s[j+k]) k++;
    he[rk[i]] = k;
  }
}

int hs[Maxn], mul[Maxn];
LL s1[Maxn], smul[Maxn];

LL ask(int a, int L, int R) {
  int len = R-L+1;
  LL val = s1[R]-s1[L-1];
  val -= hs[L-1]*smul[len];
  val -= 1LL*((hs[L-1]-hs[a-1]*mul[L-a]%MOD)%MOD+MOD)%MOD*smul[len];
}

class Query {
public:
  LL p;
  int id, op;
} q[Maxn];

bool cmp(Query a, Query b) {
  return a.p < b.p;
}

LL ans[Maxn];

int main() {
  //freopen("hashnum.in", "r", stdin);
  //freopen("hashnum.out", "w', stdout);

  scanf("%s", s+1);
  int N = strlen(s+1), M;
  build_sa(N, 25);
  getheight(N);
  for (int i = 1; i <= N; ++i)
    printf("%d ", sa[i]);
  puts("");
  for (int i = 2; i <= N; ++i)
    printf("%d ", he[i]);
  puts("");
  return 0;
}
