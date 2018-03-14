#include <cstdio>
#include <cstring>
#include <iostream>
#define MAX_N 1000001
using namespace std;

char s[MAX_N], t[MAX_N];

void getNext (int len_, int maxl[]) {
  for(int i = 1, k = 0;i < len_; ++i) {
    while(k > 0 && t[i] != t[k])
      k = maxl[k - 1];
    if(t[k] == t[i])
      k++;
    maxl[i] = k;
  }
}

void print (int i, int j) {
  printf("%d\n", i - j + 1);
}

void search (int len_s, int len_t, int maxl[]) {
  for(int i = 0, j = 0;i < len_s; ++i) {
    while(j > 0 && s[i] != t[j])
      j = maxl[j - 1];
    if(s[i] == t[j])
      j++;
    if(j == len_t) print(i, j - 1);
  }
}

int main () {
  scanf("%s", s);
  scanf("%s", t);
  int len1 = strlen(s), len2 = strlen(t);
  int maxl[len1];
  memset(maxl, 0, sizeof(maxl));

  //获得匹配字符串t的next数组
  getNext(len2, maxl);
  
  search(len1, len2, maxl);
  for(int i = 0;i < len2; ++i)
    printf("%d ", maxl[i]);
  printf("\n");
  return 0;
}
