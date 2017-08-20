#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXN = 200;
const int INF = 987654321;

int B[MAXN+1];
int T,N,K,M;
int DP(int curP,vector<int>& curC,int lastK){
    int rslt=INF;
    if(curP>N){
        return B[curP%N];
    }

    for(int k=1;k<=K;k++){
        if(curC[k]>0 && k!= lastK){
            --curC[k];
            rslt = min(rslt,DP(curP+k,curC,k) + B[curP+k]);
            ++curC[k];
        }
    }

    return rslt;
}
int main(){
    freopen("./sample.txt","r",stdin);
    cin >> T;
    for(int t=1;t<=T;t++){
        memset(B,0,sizeof(B));
        cin >> N >> K >> M; 
        for(int n=1;n<=N;n++)cin >> B[n];

        vector<int> C = vector<int>(K+1,M);
        
        int ans = DP(1,C,0);
        printf("#%d %d\n",t,ans);
    }
    return 0;
}
