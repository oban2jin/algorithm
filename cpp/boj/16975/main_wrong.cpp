#include <iostream>
using namespace std;
int N,M;
const int MAXN = 1 << 17;
int tree[2*MAXN];
void update(int i,int v,int node, int S,int E){
    if(S==E){tree[node]=v;return;}
    int  Mid = (S+E)>>1;
    if(i<=Mid){
        update(i,v,2*node,S,Mid);
    }else{
        update(i,v,2*node+1,Mid+1,E);
    }
    tree[node] = tree[node*2] + tree[node*2+1];
}
void updateR(int l,int r,int v, int node, int S,int E){
    if(S==E){tree[node]=tree[node]+v; return;}
    int Mid = (S+E)>>1;
    if(r<=Mid){
        updateR(l,r,v,2*node,S,Mid);
    }else if(l<=Mid&&(Mid+1)<=r){
        updateR(l,Mid,v,2*node,S,Mid); updateR(Mid+1,r,v,2*node+1,Mid+1,E);
    }else{
        updateR(l,r,v,2*node+1,Mid+1,E);
    }
    tree[node] = tree[node*2] + tree[node*2+1];
}
int query(int l,int r,int node,int S,int E){
    int rst=0;
    if(r<S||E<l)return 0;
    if(l<=S&&E<=r)return tree[node];
    int Mid = (S+E)>>1;
    return query(l,r,node*2,S,Mid)+query(l,r,node*2+1,Mid+1,E);
}
int main(){
    freopen("./sample.txt","r",stdin);
    cin >> N;  for(int n=1;n<N+1;n++){
        int v; scanf("%d",&v); update(n,v,1,1,MAXN);
    }
    cin >> M; for(int m=1;m<M+1;m++){
        int q,i,j,k,x; scanf("%d", &q);
        if(q==1){
            scanf("%d %d %d",&i,&j,&k); updateR(i,j,k,1,1,MAXN);
        }else{
            scanf("%d",&x); int ANS=query(x,x,1,1,MAXN);
            printf("%d\n",ANS);
        }
    }
    return 0;
}