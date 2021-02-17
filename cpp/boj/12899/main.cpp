#include<iostream>
using namespace std;
const int MAXN =  1 << 21;
int tree[MAXN*2];
int N;
int query(int k,int node,int S,int E){
    if(S==E){ return S;}
    int rst = 0; int Mid = (S+E)>>1;
    if(tree[node*2] < k){
        rst = query(k-tree[node*2],node*2+1,Mid+1,E);
    }else{
        rst = query(k,node*2,S,Mid);
    }
    return rst;
}
void update(int i,int v,int node,int S,int E){
    if(S==E){tree[node]=tree[node]+v; return;}
    int Mid  = (S+E)>>1;
    if(i<=Mid){
        update(i,v,node*2,S,Mid);
    }else{
        update(i,v,node*2+1,Mid+1,E);
    }
    tree[node] = tree[node*2] + tree[node*2+1];
}
int main(){
    cin >> N;for(int n=0;n<N;n++){
        int T,X; scanf("%d %d",&T,&X);
        if(T==1){
            update(X,1,1,1,MAXN);
        }else{
            int ANS = query(X,1,1,MAXN);
            update(ANS,-1,1,1,MAXN);
            printf("%d\n",ANS);
        }
    }
    return 0;
}