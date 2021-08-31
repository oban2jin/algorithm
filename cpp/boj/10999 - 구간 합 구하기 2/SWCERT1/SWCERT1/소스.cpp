#include <iostream>
using namespace std;
typedef long long lld;
int N, M, K;
const int MAXN = 1 << 20;
lld tree[MAXN * 2]; lld lazy[MAXN * 2];
void propagation(int node,int S, int E) {
	int MID = (S + E) >> 1;
	tree[node * 2] += lazy[node] * (MID-S+1);
	lazy[node * 2] += lazy[node];
	tree[node * 2 + 1] += lazy[node]*(E-MID);
	lazy[node * 2 + 1] += lazy[node];
	lazy[node] = 0;
}
void updateR(int l, int r,lld v, int node, int S, int E) {
	if (r < S || E < l)return;
	if (l <= S && E <= r) {
		tree[node] += (E - S + 1)*v; lazy[node] += v;
		return;
	}
	propagation(node, S, E);
	int MID = (S + E) >> 1;
	updateR(l, r, v, node * 2, S, MID);  updateR(l, r, v, node * 2 + 1, MID + 1, E);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}
lld query(int l,int r, int node, int S,int E) {
	if (r < S || E < l)return 0L; 
	if (l <= S && E <= r) {
		return tree[node];
	}
	propagation(node, S, E);
	int MID = (S + E) >> 1;
	return query(l,r,2*node,S,MID)+query(l,r,2*node+1,MID+1,E);
}
void update(int i, lld v, int node, int S, int E) {
	if (S == E) { tree[node] = v; return; }
	int MID = (S + E) >> 1;
	if (i <= MID) {
		update(i, v, node * 2, S, MID);
	}
	else {
		update(i, v, node * 2 + 1, MID + 1, E);
	}
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}
int main() {
	freopen("D:/workspacecpp/boj/10999 - 구간 합 구하기 2/sample.txt", "r", stdin);
	cin >> N >> M >> K;
	for (int n = 1; n < N + 1; n++) { lld Ni;  scanf("%lld", &Ni); update(n,Ni,1,1,MAXN); }
	for (int i = 0; i < M + K; i++) {
		int a, b, c; lld d;  scanf("%d", &a);
		if (a == 1) {
			scanf("%d %d %lld", &b, &c, &d); updateR(b, c, d, 1, 1, MAXN);
		}
		else {
			scanf("%d %d", &b, &c);
			lld ANS = query(b,c,1,1,MAXN); printf("%lld\n", ANS);
		}
	}
	return 0;
}