#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 200010
#define INF 2147483647
typedef long long ll;
using namespace std;
struct Point {
	ll val;
	int pos;
};
Point pit[MAX_N];

int N;
ll bit[MAX_N];
ll res[MAX_N];

ll sum_(int i) {
	ll s = 0;
	while (i > 0) {
		s += bit[i];
		i -= i & -i;
	}
	return s;
}

void add(int i, int x) {
	while (i <= N) {
		bit[i] += x;
		i += i & -i;
	}
}

void init () {
	memset(pit, 0, sizeof(pit));
	memset(bit, 0, sizeof(bit));
	memset(res, 0, sizeof(res));
}

void solve(Point x) {
	int sum = sum_(x.pos);
	for (;;) {
		int sum2 = sum_(sum + x.pos);
		if (sum2 == sum) break;
		sum = sum2;
	}
	res[sum + x.pos] = x.val;
	add(sum + x.pos, 1);
}

int main () {
	while (scanf("%d", &N) == 1) {
		init();
		for (int i = 1;i <= N; ++i) scanf("%d%lld", &pit[i].pos, &pit[i].val);
		for (int i = 1;i <= N; ++i) pit[i].pos++;
		for (int i = N;i > 0; --i) solve(pit[i]);			
		for (int i = 1;i <= N; ++i) printf("%lld ", res[i]);
		printf("\n");
	}
	return 0;
}