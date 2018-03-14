#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#define MAX_N 1000010
typedef long long ll;
using namespace std;

int N, Q;
ll dat[MAX_N * 4], tag[MAX_N * 4], p[MAX_N];
/*
  void db() {
  int sum = 1;
  for (int i = 1;sum <= N * 4; ++i) {
  for (int j = 1;j <= pow(2, i - 1); ++j) printf("%lld ", dat[sum++]);
  printf("\n");
  }
  }
*/
long long mk_tree(int l, int r, int now) {
	if (l == r) return dat[now] = p[l];
	return dat[now] = mk_tree(l, (l + r) / 2, now * 2) + mk_tree((l + r) / 2 + 1, r, now * 2 + 1);
}

void push_down (int k, int l, int r, int val) {
	int l1 = l, l2 = (l + r) / 2 + 1, r1 = (l + r) / 2, r2 = r;
	tag[k * 2] += val;
	tag[k * 2 + 1] += val;
	dat[k * 2] += 1LL * val * (r1 - l1 + 1);
	dat[k * 2 + 1] += 1LL * val * (r2 - l2 + 1);
	tag[k] = 0;
}

void add(int a, int b, int x, int k, int l, int r) {
	if (r < a || b < l) return;
	else if (a <= l && r <= b) {
		tag[k] += x;
		dat[k] += 1LL * x * (r - l + 1);
		push_down(k, l, r, tag[k]);
		return;
	}
	else if (a <= r && l <= b) {
		//tag[k] += x;
		dat[k] += 1LL * (min(b, r) - max(a, l) + 1) * x;
		push_down(k, l, r, tag[k]);
		add(a, b, x, k * 2, l, (l + r) / 2);
		add(a, b, x, k * 2 + 1, (l + r) / 2 + 1, r);
	}
}

long long sum(int a, int b, int k, int l, int r) {
	if (r < a || b < l) return 0;
	else if (a <= l && r <= b) {
		return dat[k];
	}
	else if (a <= r && l <= b) {
		push_down(k, l, r, tag[k]);
		return sum(a, b, k * 2, l, (l + r) / 2) + sum(a, b, k * 2 + 1, (l + r) / 2 + 1, r);
	}
}

int main () {
#ifdef Cai
	freopen("s.in", "r", stdin);
#endif
	while (~scanf("%d%d", &N, &Q)) {
		memset(dat, 0, sizeof(dat));
		memset(tag, 0, sizeof(tag));
		memset(p, 0, sizeof(p));
		for (int i = 1;i <= N; ++i) scanf("%lld", &p[i]);
		dat[1] = mk_tree(1, N, 1);//db();
    
		char s[6];
		for (int i = 1;i <= Q; ++i) {
			getchar();
			scanf("%s", s);
			if (s[0] == 'C') {
				int l, r, d;
				scanf("%d%d%d", &l, &r, &d);
				add(l, r, d, 1, 1, N);
				//db();
			}
			else if (s[0] == 'Q') {
				int l, r;
				scanf("%d%d", &l, &r);
				printf("%lld\n", sum(l, r, 1, 1, N));
				//db();
			}
		}
	}
	return 0;
}
