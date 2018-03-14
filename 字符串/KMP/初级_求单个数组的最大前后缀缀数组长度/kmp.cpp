#include <cstdio>
#include <cstring>
#include <iostream>
#define MAX_N 1000000
using namespace std;

char s[MAX_N];
int maxl[MAX_N];

void print (int tot) {
  for(int i = 0;i < tot; ++i)
    printf("%d ", maxl[i]);
}

void search () {
  maxl[0] = 0;
  int len_ = strlen(s);
  for(int i = 1, k = 0;i < len_; ++i) {
    while(k > 0 && s[k] != s[i])
      k = maxl[k - 1];
    if(s[k] == s[i])
      k++;
    maxl[i] = k;
  }
  print(len_);
}

int main () {
  scanf("%s", s);
  search();
  return 0;
}
