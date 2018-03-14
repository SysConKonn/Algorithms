#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int Max_n = 1050, SZ = 27;
struct ST{
	int TMS;
	char s[81];
};
ST in[Max_n];
int ch[Max_n*Max_n][SZ], val[Max_n*Max_n], sz,f[Max_n*Max_n],last[Max_n*Max_n];
inline int idx(char c){return c - 'a';}
inline bool cmp(ST x, ST y){return x.TMS > y.TMS;}
void add(int node){
	if (node){
//		printf("%d\n", val[node]);
		in[val[node]].TMS++;
		add(last[node]);
	}
}
void insert(char *s, int v){
	int u = 0, n = strlen(s);
	for(int i = 0; i < n; ++i){
		int c = idx(s[i]);
		if(!ch[u][c]){
			memset(ch[sz], 0, sizeof(ch[sz]));
			++sz;
			val[sz] = 0;
			ch[u][c] = sz;
		}
		u = ch[u][c];
	}
	val[u] = v;
}
void find (char* T){
	int n = strlen(T);
	int j = 0;
	for(int i = 0; i < n; ++i){
		int c = idx(T[i]);
		j = ch[j][c];
		if (val[j]) add(j);
//		else add(last[j]);
	}
}
void getfail (){
	queue<int> q;
	f[0] = 0;
	for (int c= 0; c < SZ; ++c){
		int u = ch[0][c];
		if (u) {f[u] = 0; q.push(u); last[u] = 0;}
	}
	while (!q.empty()){
		int r = q.front(); q.pop();
		for (int c = 0; c < SZ; c++){
			int u = ch[r][c];
			if (!u) {ch[r][c] = ch[f[r]][c];continue;}
			q.push(u);
			int v = f[r];
			while(v && !ch[v][c]) v = f[v];
			f[u] = ch[v][c];
			last[u] = val[f[u]] ? f[u] : last[f[u]];
		}
	}
}
int main (){
//	freopen ("B.in", "r", stdin);
	int n;
	while (1){
		scanf ("%d", &n);
		if (n == 0) break;
		memset(ch, 0, sizeof(ch)), sz = 0;
		memset(in, 0, sizeof(in));
		char s[170][90], t[1000050];
		for (int i = 1; i <= n; ++i) scanf ("%s",in[i].s), insert(in[i].s, i);
		scanf ("%s", t);
		getfail();
		find(t)
	}
	return 0;
}
