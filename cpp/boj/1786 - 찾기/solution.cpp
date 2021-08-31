#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 1000001;
char W[MAXN], S[MAXN];
int main(){
	gets(S); gets(W);
	int N = strlen(S); int M = strlen(W);

	//W[]에서 W[]를 KMP로 검색하는 방식으로 fail[]을 채운다
	int fail[MAXN] = {0};
	for(int i=1,j=0;i<N;i++){
		while(0<j && W[i]!=W[j])j=fail[j-1];
		if(W[i]==W[j])fail[i]=++j;
	}
	vector<int> ANS;
	
	for(int i=0,j=0;i<N;i++){
		while(0<j && S[i]!=W[j])j=fail[j-1];
		if(S[i]==W[j]){
			if(j==M-1){
				ANS.push_back(i-j+1);
				j=fail[j];
			}else{
				++j;
			}	
		}
	}
	
	printf("%d\n",ANS.size());
	for(int i=0;i<ANS.size();i++){
		printf("%d ",ANS[i]);
	}	
	return 0;
}