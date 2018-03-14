#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#define MAX_N 1000100
using namespace std;

int N, pos[MAX_N], len_;
char s[MAX_N];
int buc[MAX_N], key[3][MAX_N];
int sa[MAX_N];
int rkey[3][MAX_N], rpos[MAX_N];

int rk (char c) {
  if (c >= '0' && c <= '9') return c - '0';
  else if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
  else if (c >= 'a' && c <= 'z') return c - 'a' + 36;
}

int main () {
  /*
  for (int i = 1;i <= 9; ++i) printf("%d ", rk(i));
  for (int i = 'A';i <= 'Z'; ++i) printf("%d ", rk(i));
  for (int i = 'a'; i <= 'z'; ++i) printf("%d ", rk(i));
  printf("\n");*/
  scanf("%s", s + 1);
  len_ = strlen(s + 1); printf("%d\n", len_);

  memset(buc, 0, sizeof(buc));
  for (int i = 1;i <= len_; ++i) buc[key[1][i] = rk(s[i])]++;
  for (int i = 1;i <= 61; ++i) buc[i] += buc[i - 1];
  //for (int i = len_; i > 0; --i) sa[buc[key[1][i]]--] = i;
  //for (int i = 1;i <= len_; ++i) printf("%d ", sa[i]); printf("\n");
  //for (int i = 1;i <= len_; ++i) printf("%d ", key[1][i]);printf("\n");
  
  for (int k = 1;k * 2 <= len_; k *= 2) {
    memset(buc, 0, sizeof(buc));
    //memset(key[2], 0, sizeof(key[2]));
    memset(rpos, 0, sizeof(rpos));
    for (int i = 1;i <= len_; ++i) pos[i] = i;
    for (int i = 1;i + k<= len_; ++i) {
      key[2][i] = key[1][i + k];
    }
    //printf("\n");
    for (int i = 2;i > 0; --i) {
      memset(buc, 0, sizeof(buc));
      memset(rpos, 0, sizeof(rpos));
      for (int j = 1;j <= len_; ++j) buc[key[i][j]]++;   //按第i关键字基数排序
      for (int j = 1;j <= 61; ++j) buc[j] += buc[j - 1];
      for (int j = len_;j > 0; --j) {
	rpos[buc[key[i][j]]] = pos[j];
	rkey[1][buc[key[i][j]]] = key[1][j];
	rkey[2][buc[key[i][j]]--] = key[2][j];
      }
      for (int j = 1;j <= len_; ++j) {key[1][j] = rkey[1][j],key[2][j] = rkey[2][j];pos[j] = rpos[j];}
    }
    int top = 0;
    for (int i = 1;i <= len_; ++i) {
      if (rkey[1][i] != rkey[1][i - 1] || rkey[2][i] != rkey[2][i - 1]) top++;
      key[1][pos[i]] = top;
    }
    for (int i = 0;i <= len_; ++i) printf("%d ", key[1][i]); printf("\n");
  }
  for (int i = 1;i <= len_; ++i) sa[key[1][i]] = i;
  for (int i = 1;i <= len_; ++i) printf("%d ", sa[i]); printf("\n");
  return 0;
}
