#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 100110
using namespace std;

int T, N, Q;
int dat[MAX_N * 4], tme[MAX_N * 4];

void add (int a, int b, int d, int k, int l, int r, int time) {
	if (l > b || r < a) return;
	if (l == r) {
		dat[k] = d;
		tme[k] = time;
		return;
	}
	if (a <= l && r <= b) {
		dat[k] = d;
		tme[k] = time;
		return;
	}
	add(a, b, d, k * 2, l, (l + r) / 2, time);
	add(a, b, d, k * 2 + 1, (l + r) / 2 + 1, r, time);
	return;
}
		
void update (int l1, int r1, int k1, int l2, int r2, int k2) {
	if (tme[k1] > tme[k2]) {
		tme[k2] = tme[k1];
		dat[k2] = dat[k1];
	}
}
		
int sum_ (int a, int b, int k, int l, int r) {
	if (l > b || r < a) return 0;
	if (a <= l && r <= b) return dat[k] * (r - l + 1);
	update(l, r, k, l, (l + r) / 2, k * 2);
	update(l, r, k, (l + r) / 2 + 1, r, k * 2 + 1);
	return sum_(a, b, k * 2, l, (l + r) / 2) + sum_(a, b, k * 2 + 1, (l + r) / 2 + 1, r);
}

void init() {
	memset(dat, 0, sizeof(dat));
	memset(tme, 0, sizeof(tme));
}

int main () {
	scanf("%d", &T);
	int cnt = 1;
	while (T--) {
		init();
		scanf("%d%d", &N, &Q);
		int sum = 0;
		for (int i = 1;i <= N; ++i) add(i, i, 1, 1, 1, N, sum);
		for (int i = 1;i <= Q; ++i) {
			int l, r, d;
			scanf("%d%d%d", &l, &r, &d);
			add(l, r, d, 1, 1, N, ++sum);
		}
		int res = 0;
		for (int i = 1;i <= N; ++i) res += sum_(i, i, 1, 1, N);
		printf("Case %d: The total value of the hook is %d.\n", cnt++, res);
	}
	return 0;
}