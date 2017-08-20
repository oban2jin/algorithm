#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
typedef pair<int,int> pii;
const int MAXK = 6;
const int MAXN = 200;
const int INF = 987654321;

map<int,int> key;
vector<vector<int> > cache;
int B[MAXN+1];
int T,N,K,M;
int getValue(int& C,int k){
    int rslt = C & (15 <<((k-1)*4)); 
    return rslt >> ((k-1)*4);
}
void setValue(int& C,int k, int m){
    C = C & ~(15<<((k-1)*4));
    C = C | (m <<((k-1)*4)); 
}
void printCurC(int C){
    for(int k=1;k<=K;k++){
        printf("k=[%d]|[%d] ",k,M-getValue(C,k));
    }
}
int DP2(int curP,int& curC,int lastK){
// printf("curP=[%d],curC=[%d],lastK=[%d]\n",curP,curC,lastK);
    if(curP>N){
        return B[curP%N];
    }
    
    map<int,int>::iterator Iter = key.find(curC);
    if(Iter != key.end()){
        vector<int> &R = cache[key[curC]];
        if(R[curP]!=-1){
            //printf("Hit the cache curP:[%d]/curC:[%d]=[%d]\n",curP,curC,R[curP]);
            return R[curP];
        }
    }else{
        cache.push_back(vector<int>(N+1,-1));
        key[curC]=cache.size()-1;
    }

    int rslt = INF; 
    for(int k=1;k<=K;k++){
        int m = getValue(curC,k); 
        if(m>0 && k!=lastK){
            setValue(curC,k,--m); setValue(curC,MAXK+1,k);
            int candidate = DP2(curP+k,curC,k);
            setValue(curC,k,++m); 
            rslt = min(rslt,candidate+B[curP+k]);
            if(curP==1){
                printf("k=[%d],rslt=[%d],candidate=[%d],B[%d]=[%d]\n",k,rslt,candidate,curP+k,B[curP+k]);
            }
        }
    }
    setValue(curC,MAXK+1,lastK);
    cache[key[curC]][curP]=rslt;
    return rslt;
}
int DP(int curP,vector<int>& curC,int lastK){
    int rslt=INF;
    if(curP>N){
        return B[curP%N];
    }

    for(int k=1;k<=K;k++){
        if(curC[k]>0 && k!=lastK){
            --curC[k];
            int candidate = DP(curP+k,curC,k);
            // rslt = min(rslt,DP(curP+k,curC,k) + B[curP+k]);
            ++curC[k];
            rslt = min(rslt,candidate+B[curP+k]);
            if(curP==1){
                printf("k=[%d],rslt=[%d],candidate=[%d],B[%d]=[%d]\n",k,rslt,candidate,curP+k,B[curP+k]);
            }
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
        int CC = 0; for(int k=0;k<K;k++){
             CC = CC | (M << (k*4));
        }

        vector<int> C = vector<int>(K+1,M);
        int ans = DP(1,C,0);
        printf("#%d %d\n",t,ans);

        key.clear(); cache.clear();
        int ans2 = DP2(1,CC,0);
        printf("#%d %d\n",t,ans2);  
        
        // for(int i=0;i < (1<<24);i++){
        //     map<int,int>::iterator Iter = key.find(i);
        //     if(Iter!=key.end()){
        //         vector<int>& x = cache[key[i]];
        //         printCurC(i);
        //         for(int n=1;n<=N;n++)printf("%d ",x[n]);
        //         printf("\n");
        //     }
        // }
    }
    return 0;
}
