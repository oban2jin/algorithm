#include <iostream>
#include <vector>
using namespace std;
typedef long long lld;
const int MAXN = 1 << 19;
lld sal[MAXN];
lld tree[MAXN * 2];
vector<int> child[MAXN];
int L[MAXN], R[MAXN], Nd[MAXN];
int N, M;
void update(int l, int r,lld v, int node, int S, int E) {
	if (r < S || E < l) return;
	if (l <= S && E <= r) {
		tree[node] += v; return;
	}
	int MID = (S + E) >> 1;
	update(l, r, v, node * 2, S, MID); update(l, r, v, node * 2 + 1, MID + 1, E);
}
lld query(int i,lld v,int node,int S,int E) {
	if (S == E) { return v+tree[node]; }
	int MID = (S + E) >> 1;
	lld rst = 0L;
	if (i <= MID) {
		rst = query(i, v+tree[node],node * 2, S, MID);
	}
	else {
		rst = query(i, v + tree[node], node * 2 + 1, MID + 1, E);
	}
	return rst;
}
void init(int node,int S,int E) {
	if (S == E) {
		tree[node] = sal[Nd[S]];
		return;
	}
	int MID = (S + E) >> 1;
	init(node * 2, S, MID); init(node * 2 + 1, MID + 1, E);
}
void pre_order(int n, int &cnt) {
	L[n] = ++cnt;
	for (int i = 0; i < child[n].size(); i++) {
		pre_order(child[n][i], cnt);
	}
	R[n] = cnt;
}
int main() {
	freopen("D:/workspacecpp/boj/2820 - 자동차공장/sample.txt", "r", stdin);
	cin >> N >> M;
	int s, p; scanf("%d",&s); sal[1] = s;
	for (int n = 2; n < N+1; n++) {
		scanf("%d %d", &s, &p);
		child[p].push_back(n); sal[n] = s;
	}
	int cnt = 0;
	pre_order(1, cnt); for (int n = 1; n < N + 1; n++) { Nd[L[n]] = n; }
	init(1, 1, N);
	char q; int a, x;
	for (int m = 1; m < M + 1; m++) {
		scanf(" %c", &q);
		if (q == 'p') {
			//a 아래 노드들의 월급을 x만큼 올리세요.
			scanf("%d %d", &a, &x);
			update(L[a]+1, R[a], x, 1, 1, N); 
		}
		else {
			scanf("%d", &a);
			lld ANS = query(L[a],0L, 1, 1, N);
			printf("%lld\n", ANS);
		}
	}
	return 0;
}