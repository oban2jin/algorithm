#include <iostream>
using namespace std;
typedef long long lld;
int N,M;
const int MAXN = 1<<20;
const int MAX  = 1000000;
lld tree[MAXN*2];
int I[MAX+1];
void update(int i,int v,int node, int S,int E){
    if(S==E){tree[node]=tree[node]+v;return;}
    int Mid = (S+E)>>1;
    if(i<=Mid){
        update(i,v,2*node,S,Mid);
    }else{
        update(i,v,2*node+1,Mid+1,E);
    }
    tree[node] = tree[node*2] + tree[node*2+1];
}
lld query(int l,int r,int node, int S,int E){
    if(r<S||E<l)return 0;
    if(l<=S&&E<=r)return tree[node];
    int Mid = (S+E)>>1;
    return query(l,r,2*node,S,Mid)+query(l,r,2*node+1,Mid+1,E);
}
int main(){
    cin >> N; for(int n=1;n<N+1;n++)scanf("%d",&I[n]);
    cin >> M; for(int m=1;m<M+1;m++){
        int q,i,j,k,x; scanf("%d",&q);
        if(q==1){
            scanf("%d %d %d",&i,&j,&k); 
            update(i,k,1,1,MAXN); update(j+1,-k,1,1,MAXN);
        }else{
            scanf("%d",&x);
            lld ANS = query(1,x,1,1,MAXN) + I[x];
            printf("%lld\n",ANS);
        }
    }
    return 0;
}