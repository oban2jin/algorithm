#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef unsigned long long lld;
char T[1000001], P[1000001];
int main() {
	gets(T); gets(P);
	int st = strlen(T); int sp = strlen(P);
	//printf("%d,%d\n",st,sp);
	lld HP = 0L; lld P_L = 1;
	for(int i=1;i<sp;i++){
		P_L = P_L*2;
	}
	for(int i=0;i<sp;i++){
		HP = HP*2 + (P[i]-'A'+1);
	}
	lld HT = 0L; vector<int> ANS;
	for(int i=0;i+sp-1<st;i++){
		if(i==0){
			for(int j=0;j<sp;j++){
				HT = HT*2 + (T[j]-'A'+1);
			}
		}else{
			HT = HT - (T[i-1]-'A'+1)*P_L;
			HT = HT*2 + (T[i+sp-1] -'A'+1);
		}
		//printf("HT=[%lld], HP=[%lld], i=%d\n",HT,HP,i);
		if(HT==HP){
			bool flag = true;
			for(int j=0;j<sp;j++){
				if(P[j]!=T[i+j]){flag = false; break;}
			}
			if(flag)ANS.push_back(i+1);
		}
	}
	printf("%d\n",ANS.size());
	for(int i=0;i<ANS.size();i++){
		printf("%d ",ANS[i]);
	}
	return 0;
}