#include <iostream>
#include <algorithm>
using namespace std;
int T,N,K;
const int MAXN = 1 << 17;
const int MAXV = 987654321;
struct Nd{
	int mn,mx;
	Nd(){};
	Nd(int mn,int mx):mn(mn),mx(mx){};
}tree[MAXN*2];
Nd query(int l,int r){
	Nd rst = Nd(MAXV,0);
	int S = MAXN + l; int E = MAXN + r;
	while(S<=E){
		if(S%2==1){ 
			rst.mn = min(tree[S].mn,rst.mn);
			rst.mx = max(tree[S].mx,rst.mx);
			++S;
		}
		if(E%2==0){
			rst.mn = min(tree[E].mn,rst.mn);
			rst.mx = max(tree[E].mx,rst.mx);			
			--E;
		}
		S = S >> 1; E = E >> 1;
	}
	return rst;
}
void update(int i,int v){
	int a = MAXN + i; tree[a] = Nd(v,v);
	a = a >> 1;
	while(a){
		tree[a].mx = max(tree[2*a].mx,tree[2*a+1].mx);
		tree[a].mn = min(tree[2*a].mn,tree[2*a+1].mn);
		a = a >> 1;
	}
}
void init(){
	for(int i=0;i<2*MAXN;i++){tree[i]=Nd(MAXV,0);}
	for(int n=0;n<N;n++)update(n,n);
}
int main(){
	cin >> T;for(int t=0;t<T;t++){
		cin >> N >> K; init();
		for(int k=0;k<K;k++){
			int q,a,b; scanf("%d %d %d",&q,&a,&b);
			if(q==0){
				Nd av = query(a,a); Nd bv = query(b,b);
				update(a,bv.mn); update(b,av.mn);
			}else{
				Nd rst = query(a,b);
				if(rst.mn==a&&rst.mx==b){
					printf("YES\n");
				}else{
					printf("NO\n");
				}
			}
		}
	}
	return 0;
}