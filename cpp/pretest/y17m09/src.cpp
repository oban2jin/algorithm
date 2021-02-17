#include <iostream>
#include <string.h>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;
typedef pair<int,int> pii; 
const int MAXK = 6;
const int MAXN = 200;
const int MAXM = 10;
const int INF = 987654321;
const int CACHE_DEPTH = 0;

int POW[MAXK+1];
int MINVALUE;
int CACHE[1800000][MAXK];
//int CACHE[1<<24][MAXK];
//pii CACHE[MAXM+1][MAXM+1][MAXM+1][MAXM+1][MAXM+1][MAXM+1][MAXK+1];
int B[MAXN + 1];
int T, N, K, M;
int getValue(int& C, int k) {
    //int rslt = C & (15 << ((k - 1) * 4));
    //return rslt >> ((k - 1) * 4);
    int rslt = C/POW[k-1]; rslt %= (M+1);
    return rslt;
}
void setValue(int& C, int k, int m) {
     //C = C & ~(15 << ((k - 1) * 4));
     //C = C | (m << ((k - 1) * 4));
    C = C + m*POW[k-1];
}
int DP2(int curP, int& curC, int lastK) {
    //printf("DP2...curP=[%d],curC=[%d],lastK=[%d]\n", curP, curC, lastK);
    //printf("curP=[%d],curC=[%d],lastK=[%d]\n",curP,curC,lastK);
    if (curP>N) {
        return 0;
    }
    //int k1 = getValue(curC,1); int k2 = getValue(curC,2); int k3 = getValue(curC,3);
    //int k4 = getValue(curC,4); int k5 = getValue(curC,5); int k6 = getValue(curC,6);

    int& rslt = CACHE[curC][lastK];
    //pii& rslt = CACHE[k1][k2][k3][k4][k5][k6][lastK];
    if(rslt!=-1)return rslt;

    rslt = INF; int nextK = 0; int minK = 0;
    for (int k = 1; k <= K; k++) {
        nextK = (lastK + k) % K; nextK = nextK == 0 ? K : nextK;
        int nextP = curP + nextK; if(nextP>N) nextP=nextP-N;
        int m = getValue(curC, nextK); 
        if (nextK != lastK && m > 0) {
            setValue(curC, nextK, -1);
            int candidate = DP2(curP + nextK, curC, nextK) + B[nextP];
            if(candidate < rslt){
                rslt = candidate; minK = nextK;
            }
            setValue(curC, nextK, 1);
        }
    }

    return rslt;
}
void DP3(int curP, int& curC, int lastK, int costsum) {
    //printf("curP=[%d],curC=[%d],lastK=[%d],costsum=[%d]\n", curP, curC, lastK, costsum);
    if (curP>N) {
        MINVALUE = min(MINVALUE, costsum + B[curP%N]);
        return;
    }
    if (CACHE_DEPTH < curP) {
        int candidate = DP2(curP, curC, lastK); 
        MINVALUE = min(MINVALUE, costsum+candidate);
        return;
    }
    int nextK = 0;
    for (int k = 1; k <= K; k++) {
        nextK = (lastK + k) % K;  nextK = nextK == 0 ? K : nextK;
        int m = getValue(curC, nextK); 
        if (MINVALUE <= costsum + B[curP + nextK])continue;
        if (nextK != lastK && m > 0) {
            setValue(curC, nextK, -1);
            DP3(curP + nextK, curC, nextK, costsum + B[curP + nextK]);
            setValue(curC, nextK, 1);
        }
    }
}
int getHuristic(int n) {
    int rslt = 0; int lastK = 0;
    vector<int> card = vector<int>(K + 1, M);
    while (n <= N) {
        int T = INF; int mink = 0;
        for (int k = 1; k <= K; k++) {
            if (k == lastK)continue;
            int next = n + k;
            if (next > N)next = next%N;
            if (B[next] < T && card[k]>0) { mink = k; T = B[next]; }
        }
        rslt += T; n += mink; lastK = mink; --card[lastK];
    }
    return rslt;
}
void PreCal(){
    for(int k=0;k<=MAXK;k++){
        if(k==0)POW[k]=1;
        else{
            POW[k]=POW[k-1]*(M+1);
        }
        //printf("POW[%d]=%d\n",k,POW[k]);
    }
}
int main() {
    freopen("./sample_input.txt", "r", stdin);
    //freopen("../../out.txt", "w", stdout);
    clock_t startTime = clock();
    cin >> T;
    for (int t = 1; t <= T; t++) {
        memset(B, 0, sizeof(B));
        cin >> N >> K >> M;  
        PreCal();
        for (int n = 1; n <= N; n++)cin >> B[n];
        int CC = POW[K]-1; 
        // int CC = 0; for (int k = 1; k<=K; k++) {
        //  setValue(CC, k, M);
        // }
        //for(int i=0;i<MAXK+1;i++)CACHE[i].clear();
        memset(CACHE,-1,sizeof(CACHE));
        //MINVALUE = INF; 
        MINVALUE = getHuristic(1);

        DP3(1, CC, 0, 0);
        printf("#%d %d\n", t, MINVALUE);

    }
    clock_t endTime = clock();
    printf("Elapsed Time = %.3f\n",(double)(endTime-startTime)/CLOCKS_PER_SEC);
    return 0;
}