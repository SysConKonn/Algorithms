#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#define MAX_N 10010
using namespace std;

struct str {
  char s;
  bool book = false;
};
stack<str> stk;

char t[MAX_N];
int ch[1000][1000], sz = 1, fa[MAX_N];
int strin[MAX_N], strsum;

int M;
int head[MAX_N], to[MAX_N], nxt[MAX_N], ttop;

int fail[MAX_N];
int fail_head[MAX_N], fail_to[MAX_N], fail_nxt[MAX_N], failtop;

bool need_search[MAX_N];
int bit[MAX_N * 2];

int idx (char c) {return c - 'a';}

void Read () {
  int len_ = strlen(t);
  int u = 0;
  for (int i = 0;i < len_; ++i) {
    int c = idx(t[i]);
    if (t[i] == 'P') {
      stk.top().book = true;
      strin[++strsum] = stk.size();
    }
    else if (t[i] == 'B') {
      if (stk.top().book == true) {  //当前删除的是合法的点，不用烧边，把正确标记移至下一个字符
	stk.pop();
	if (!stk.empty()) stk.top().book = true;
	u = fa[u];  //向上到上一层点
      }
      else {
	ch[fa[u]][stk.top().s - 'a'] = 0;   //它的上一层向它无边(烧边)
	stk.pop();
	u = fa[u];
	sz--;  //这条边不算数
      }
    }
    else {
      if (ch[u][c]) {u = ch[u][c];continue;}
      ch[u][c] = sz++;  //加一条边
      fa[sz - 1] = u;  //记录它的上层节点编号，以便于删除时向上
      stk.push((str){t[i], false});   //将当前字符串压入栈中，初始值为false因为当时还没有P是一个不合法的值
      u = ch[u][c];  //跳到下一个点
    }
  }
  
  for (int i = 0;i < sz; ++i)
    for (int j = 0;j < 26; ++j)
      if (ch[i][j]) printf("%d %c %d\n", i, j + 'a', ch[i][j]);
  for (int i = 1;i <= strsum; ++i) printf("%d ", strin[i]);
  printf("\n");
  
}

void fail_AddEdge (int _from_, int _to_) {
  //printf("fail_tree : %d %d\n", _from_, _to_);
  fail_nxt[++failtop] = fail_head[_from_];
  fail_head[_from_] = failtop;
  fail_to[failtop] = _to_; 
}

void getfail () {
  queue<int> q;
  fail[0] = 0;
  for (int i = 0;i < 26; ++i) 
    if (ch[0][i]) {
      //AddEdge
      fail_AddEdge(0, ch[0][i]);
      q.push(ch[0][i]);
    }

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int c = 0;c < 26; ++c) {
      if (!ch[u][c]) continue;
      q.push(ch[u][c]);
      int v = fail[u];
      while (v && !ch[v][c]) v = fail[v];
      fail[ch[u][c]] = ch[v][c];

      //AddEdge
      int _from_ = ch[v][c], _to_ = ch[u][c];
      fail_AddEdge(_from_, _to_);
    }
  }
  /*
  for (int i = 0;i < sz; ++i) printf("%d ", fail[i]);
  printf("\n");
  */
}

int tot;
int l[MAX_N], r[MAX_N], order_[MAX_N];
void get_dfs_order (int x, int fa) {
  l[x] = ++tot;
  order_[tot] = x;
  for (int now = fail_head[x]; now; now = fail_nxt[now]) {
    int _to = fail_to[now];
    //printf("dfs : %d %d\n", x, _to);
    if (_to == fa) continue;
    get_dfs_order(_to, x);
  }
  r[x] = tot;
}

void query (int end) {
  //int len_ = strlen(s);
  //for (int i = 0;
}

int main () {
  scanf("%s", t);
  Read();

  getfail();

  scanf("%d", &M);
  for (int i = 1;i <= M; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    //printf("query : %d %d\n", a, b);

    nxt[++ttop] = head[b];
    head[b] = ttop;
    to[ttop] = a;
    need_search[b] = true;
  }

  get_dfs_order(0, 0);
  /*
  for (int i = 1;i <= tot; ++i) 
    printf("%d : l:%d  r:%d\n", order_[i], l[order_[i]], r[order_[i]]);
  printf("\n");
  */
  /*
  for (int i = 1;i <= strsum; ++i) {
    if (need_search[i])
      search(strin[i]);
    for (int x = head[i]; x; x = nxt[x]) {
      query(to[x]);
    }
  }
  */
  return 0;
}
