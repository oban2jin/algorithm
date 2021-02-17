#include <iostream>
using namespace std;
typedef long long lld;
const int MAXN = 1 << 20;
lld arr[MAXN*2];
int N,M,K;
lld qry(int node,int l,int r, int s,int e){
    if(r<s||e<l)return 0;
    if(l<=s&&e<=r)return arr[node];
    int mid =(s+e)>>1;
    return qry(node*2,l,r,s,mid) + qry(node*2+1,l,r,mid+1,e);
}
//update(i,v,1,1,MAXN);
void update(int i,int v,int node, int s,int e){
    if(s==e){arr[node]=v;return;}
    int mid = (s+e)>>1;
    if(i<=mid){
        update(i,v,node*2,s,mid);
    }else{
        update(i,v,node*2+1,mid+1,e);
    }
    arr[node] = arr[node*2] + arr[node*2+1];
}
int main(){
    cin >> N >> M >> K;
    for(int n=1;n<N+1;n++){
        lld v; cin >> v; 
       update(n,v,1,1,MAXN);
    }
    for(int i=0;i<M+K;i++){
        lld a,b,c;
        cin >> a >> b >> c;
        if(a==1){
            update(b,c,1,1,MAXN);
        }else{
            lld ans = qry(1,b,c,1,MAXN);
            cout << ans << endl;
        }
    }
    return 0;
}