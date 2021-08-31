#include <iostream>
using namespace std;
typedef long long lld;
int N, M;
const int MAXN = 1 << 20;
const int MAX = 1000000;
lld tree[MAXN * 2];
int I[MAX + 1];
void init(int node,int S,int E) {
	//Segment Tree 초기화
	if (S == E) {
		tree[node] = I[S]; return;
	}
	int MID = (S + E) >> 1;
	init(node * 2, S, MID); init(node * 2 + 1, MID + 1, E);
}
void update(int l, int r,int v, int node, int S, int E) {
	//구간(l,r)에 대한 update
	if (r < S || E < l)return;
	if (l <= S && E <= r) {
		tree[node] += v; return;
	}
	int MID = (S + E) >> 1;
	update(l, r, v, node * 2, S, MID); update(l, r, v, node * 2 + 1, MID + 1, E);
}
lld query(int i, lld v,int node, int S, int E) {
	//1포인트에 대한 query
	if (S == E) { return (v + tree[node]); }
	int MID = (S + E) >> 1;
	lld rst = 0L;
	if (i <= MID) {
		rst = query(i, v+tree[node],node * 2, S, MID);
	}
	else {
		rst = query(i, v+tree[node],node * 2 + 1, MID + 1, E);
	}
	return rst;
}
int main() {
	freopen("D:/workspacecpp/boj/16975 - 수열과쿼리1/sample.txt", "r", stdin);
	cin >> N; for (int n = 1; n < N + 1; n++)scanf("%d", &I[n]);
	init(1,1,MAXN);
	cin >> M; for (int m = 1; m < M + 1; m++) {
		int q, i, j, k, x; scanf("%d", &q);
		if (q == 1) {
			scanf("%d %d %d", &i, &j, &k); 
			update(i, j, k, 1, 1, MAXN);
		}
		else {
			scanf("%d", &x);
			lld ANS = query(x, 0, 1, 1, MAXN);
			printf("%lld\n", ANS);
		}
	}
	return 0;
}