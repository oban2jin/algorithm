#include<cstdio>
#include<algorithm>
#include<cstdlib>
#define fi first
#define se second
#define rep(i,n) for(int i = 0; i < n; i++)
#define maxs(x,y) x = max(x,y);
#define mins(x,y) x = min(x,y);
#define pb push_back
using namespace std;
typedef long long int ll;
typedef pair<int,int> P;
typedef pair<int,P> Q;

const int MX = 100005, MN = MX*200, x2 = 30, n2 = 1<<x2, INF = 1000000000;

int sn;
struct node{ int l, r; ll x, y;};
node t[MN]; int ti;

int add(int a, int b, int i, int l = 0, int r = n2){
	if(i == -1){
		i = ti; t[ti++] = (node){-1,-1,0,0};
	} else if(i < sn){
		t[ti] = t[i]; i = ti++;
	}
	if(a <= l && r <= b){ t[i].x++; return i;}
	
	int c = l+r>>1; t[i].y = 0;
	if(a < c) t[i].l = add(a,b,t[i].l,l,c);
	if(c < b) t[i].r = add(a,b,t[i].r,c,r);
	if(t[i].l != -1) t[i].y += t[t[i].l].y+t[t[i].l].x*(c-l);
	if(t[i].r != -1) t[i].y += t[t[i].r].y+t[t[i].r].x*(r-c);
	return i;
}

ll sum(int a, int b, int i, int l = 0, int r = n2, ll v = 0){
	if(i == -1) return v*(min(b,r)-max(a,l));
	v += t[i].x;
	if(a <= l && r <= b){ return t[i].y+v*(r-l);}
	ll res = 0; int c = l+r>>1;
	if(a < c) res += sum(a,b,t[i].l,l,c,v);
	if(c < b) res += sum(a,b,t[i].r,c,r,v);
	return res;
}

Q z[MX]; int x[MX], xn[MX], xi;

int main(){
	int n, m, q, a, b, c, pre, l, r; ll th;
	scanf("%d%d%d",&n,&m,&q);
	
	rep(i,m){
		scanf("%d%d%d",&a,&b,&c);
		z[i] = Q(c,P(a,b));
	}
	sort(z,z+m);
	
	ti = 1;
	t[0] = (node){-1,-1,0,0};
	
	pre = -1; sn = 0;
	rep(i,m){
		c = z[i].fi; a = z[i].se.fi; b = z[i].se.se;
		if(pre != c){
			pre = x[xi] = c;
			t[ti] = t[sn];
			xn[xi++] = ti++;
		}
		sn = xn[xi-1];
		add(a,b+1,sn);
	}
	
	rep(qi,q){
		scanf("%d%d%lld",&a,&b,&th);
		l = -1; r = xi-1;
		while(l+1<r){
			c = (l+r+1)/2;
			if(sum(a,b+1,xn[c]) < th) l = c; else r = c;
		}
		printf("%d\n",x[r]);
	}
	
	return 0;
}