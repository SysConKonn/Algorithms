#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
#define MAX_node 300
#define sig_size 30
using namespace std;

struct trie {
	int ch[MAX_node][sig_size];
	int val[MAX_node];
	int sz;
	trie() {sz = 1; memset(ch[0], 0, sizeof(ch[0]));}
	int idx(char c) {return c - 'a';}

	void insert (char* s, int v) {
		int u = 0, n = strlen(s);
		for (int i = 0;i < n; ++i) {
			int c = idx(s[i]);
			if (!ch[u][c]) {
				memset(ch[sz], 0, sizeof(ch[sz]));
				val[sz] = 0;
				ch[u][c] = sz++;
			}
			u = ch[u][c];
		}
		val[u] = v;
	}

	int find (char* s) {
		int len_ = strlen(s), u = 0;
		for (int i = 0;i < len_; ++i) {
			int c = idx(s[i]);
			if(!ch[u][c]) 
				return 0;
			u = ch[u][c];
		}
		return val[u];
	}
};
trie tree;

int main () {
	char s[MAX_node];
	while (1) {
		scanf("%s", s);
		tree.insert(s, 1);
		int c = getchar();
		if  (cin.peek() == '\n') break;
	}
	while (scanf("%s", s) == 1) {
		printf("%d\n", tree.find(s));
	}
	return 0;
} 