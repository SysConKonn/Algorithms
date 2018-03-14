#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#define MAX_N 1000010
using namespace std;

int N;
char s[MAX_N];
int fail[MAX_N];

int main () {
	int cnt = 1;
	while (1) {
		memset(fail, 0, sizeof(fail));
		scanf("%d", &N);
		if (N == 0) break;
		printf("Test case #%d\n", cnt++);
		scanf("%s", s + 1);
		int len_ = strlen(s + 1);
		fail[1] = 0;  
 		int j = 0;  
   		 for (int i = 2; i <= len_; i++) {  
    	    while (j && s[i] != s[j + 1]) j = fail[j];  
        	if (s[i] == s[j + 1]) j++;  
      		fail[i] = j;  
    	}  

		for (int i = 2;i <= len_; ++i) {
			if (!fail[i]) continue;
			int x = i - fail[i];
			//if (x <= 0) continue;
			if (i % x == 0) printf("%d %d\n", i, i / x);
		}
		printf("\n");
	}
	return 0;
}