#include <cstdio>
#include <stack>
#include <cstring>
#define MAX_N 10010
using namespace std;

struct str {
  char s;
  bool book = false;
};
stack<str> stk;

char t[MAX_N];
int ch[1000][1000], sz = 1, fa[MAX_N];

int idx (char c) {return c - 'a';}

void Read () {
  int len_ = strlen(t);
  int u = 0;
  for (int i = 0;i < len_; ++i) {
    //printf("%d\n", len_);
    int c = idx(t[i]);
    if (t[i] == 'P') stk.top().book = true;
    else if (t[i] == 'B') {
      if (stk.top().book = true) {  //当前删除的是合法的点，不用烧边，把正确标记移至下一个字符
	stk.pop();
	stk.top().book = true;
	u = fa[u];  //向上到上一层点
      }
      else {
	stk.pop();
	ch[fa[u]][u] = 0;   //它的上一层向它无边(烧边)
	u = fa[u];
	sz--;  //这条边不算数
      }
    }
    else {
      //if (ch[u][c]) continue;
      //printf("%d %c %d\n", u, t[i], ch[u][c]);
      ch[u][c] = sz++;  //加一条边
      fa[sz - 1] = u;  //记录它的上层节点编号，以便于删除时向上
      stk.push((str){t[i], false});   //将当前字符串压入栈中，初始值为false因为当时还没有P是一个不合法的值
      u = ch[u][c];  //跳到下一个点
    }
  }

  for (int i = 0;i < sz; ++i)
    for (int j = 0;j < 26; ++j)
      if (ch[i][j]) printf("%d %c %d\n", i, j + 'a', ch[i][j]);
}

int main () {
  scanf("%s", t);
  Read();
  return 0;
}
