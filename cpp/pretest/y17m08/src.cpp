//
//  main.cpp
//  PreTest for Y17M08
//
//  Created by JONGHAE JIN on 2017. 7. 15..
//  Copyright © 2017년 JONGHAE JIN. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long lld;

const int MAXN=10000+1;
const int INF = 987654321;

int P[MAXN],C[MAXN],D[MAXN];
int dp[MAXN][MAXN];

vector<int> TS[MAXN], dpth[MAXN];

int T,N,root;

int getSubTMin(int n,int c){
    int rslt=INF;
    
    if(C[n]==0){
        if(c==1)return 2;
        else return 1;
    }else {
        for(int cc=1;cc<=C[n]+1;cc++){
            if(c!=cc){
                rslt = min(rslt,dp[n][cc]);
            }
        }
    }

    return rslt;
}
int DP(int MaxD){
    int rslt=INF;

    for(int d=MaxD; 0<=d;d--){
        for(int &n : dpth[d]){
            if(C[n]!=0){
                for(int c=1;c<=C[n]+1;c++){
                    for(int &sn : TS[n]){
                        // printf("getSubTMin(%d,%d)=%d\n",sn,c,getSubTMin(sn,c));
                        dp[n][c] = dp[n][c]+getSubTMin(sn,c);
                    }
                    dp[n][c] = dp[n][c] + c;
                    //printf("dp[%d][%d]=%d\n",n,c,dp[n][c]);
                }
            }
        }
    }
    
    for(int c=1;c<=C[root]+1;c++){
        rslt=min(rslt,dp[root][c]);
    }
    return rslt;
}
int main() {
#ifndef _SWCERTIFICATE
    freopen("./sample_input.txt","r",stdin);
#endif    
    cin >> T;for(int t=1;t<=T;t++){
        for(int n=0;n<MAXN;n++){
            TS[n].clear(); dpth[n].clear();
        }
        memset(P,-1,sizeof(P)); memset(C,0,sizeof(C)); memset(dp,0,sizeof(dp)); memset(D,0,sizeof(D));
        scanf("%d",&N); for(int n=0;n<N;n++){
            int p; scanf("%d",&p); P[n]=p;
            if(p!=-1){TS[p].push_back(n); ++C[p];}
            else{root=n;}
        }

        // printf("root=[%d]\n",root);

        queue<int> Q; int DPTH=0; dpth[0].push_back(root); Q.push(root);
        while(!Q.empty()){
            int here = Q.front(); Q.pop();
            // printf("here=[%d]/D[%d]=%d\n",here,here,D[here]);
            for(int &there : TS[here]){
                D[there]=D[here]+1; dpth[D[there]].push_back(there);
                DPTH=max(DPTH,D[there]);
                Q.push(there);
            }
        }
        int ans = DP(DPTH);
        printf("#%d %d\n",t,ans);
    }
    
    return 0;
}
