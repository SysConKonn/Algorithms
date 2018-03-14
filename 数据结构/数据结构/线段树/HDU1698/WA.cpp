#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#define MAX_N 100010
using namespace std;

int N, M, T, Q;
int bit0[MAX_N * 2], bit1[MAX_N * 2];

void add(int *b, int i, int v) {
	printf("%d %d\n", i, v);
	while (i <= N) {
		b[i] += v;
		i += i & -i;
	}
}

int sum(int *b, int i) {
	int s = 0;
	while (i > 0) {
		s += b[i];
		i -= i & -i;
	}
	return s;
}

int main () {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		scanf("%d", &Q);
		
		for (int i = 1;i <= N; ++i) 
			add(bit0, i, 1);
		
		int l, r, x;
		for (int i = 0;i < Q; ++i) {
			scanf("%d%d%d", &l, &r, &x);
			add(bit0, l, -x * (l - 1));
			add(bit1, l, x);
			add(bit0, r + 1, x * r);
			add(bit1, r + 1, -x);
		}
		int res = 0;
		res += sum(bit0, N) + sum(bit1, N) * N;
		printf("%d\n", res);
	}
	return 0;
}