#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int nodeCnt,sccCnt;
int N,M;

vector< vector<int> > adj;
vector<int> sccId,discovered;
stack<int> S;

int scc(int n){
    int here = n; S.push(here);
    int rslt=discovered[here] = nodeCnt++;
    
    for(int &there : adj[here]){
        if(discovered[there]==-1)
            rslt=min(rslt,scc(there));
        else if(sccId[there]==-1)
            rslt=min(rslt,discovered[there]);
    }

    if(rslt==discovered[here]){
        while(true){
            int nxt = S.top(); S.pop();
            sccId[nxt]=sccCnt;
            if(nxt==here) break;
        }
        ++sccCnt;
    }

    return rslt;
}
int main(){
    freopen("./sample.txt","r",stdin);
    cin >> N >> M;
    adj = vector< vector<int> >(N+1);
    for(int m=0;m<M;m++){
        int u,v;
        scanf("%d%d",&u,&v); adj[u].push_back(v);
    }

    sccId = discovered = vector<int>(N+1,-1);
    nodeCnt = sccCnt = 0;
    for(int n=1;n<=N;n++){
        if(discovered[n]==-1)scc(n);
    }

    for(int n=1;n<=N;n++){
        printf("sccId=[%d],n=%d\n",sccId[n],n);
    }

    // for(int u=1;u<adj.size();u++){
    //     for(int &v : adj[u])printf("[%d]->[%d]\n",u,v);
    // }

    return 0;
}