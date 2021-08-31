#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
struct Et
{
	int i, v, cv;
};
struct Nd
{
	int l, r, v;
};
const int MAXN = 100000;
const int MAX = 20;
Et W[MAXN + 1], RW[MAXN + 1];
int P[MAXN + 1], S[MAXN + 1][MAX], D[MAXN + 1];
vector<int> G[MAXN + 1];
vector<Nd> tree;
int H[MAXN + 1];
int N, M;
void bfs() {
	queue<int> Q; Q.push(1); D[1] = 1; P[1] = 1;
	while (!Q.empty()) {
		int here = Q.front(); Q.pop();
		vector<int> nxts = G[here];
		for (int i = 0; i < nxts.size(); i++) {
			int nxt = nxts[i]; if (D[nxt] == 0) {
				D[nxt] = D[here] + 1; P[nxt] = here; Q.push(nxt);
			}
		}
	}
}
void SPAS() {
	for (int i = 0; i < MAX; i++) {
		for (int n = 1; n <= N; n++) {
			if (i == 0) { 
				S[n][i] = P[n]; 
			}
			else {
				S[n][i] = S[S[n][i-1]][i-1];
			}
		}
	}
}
void init(int node, int S,int E) {
	if (S == E) {
		return;
	}
	tree.push_back({ 0,0,0 }); int lidx = tree.size() - 1; 
	tree.push_back({ 0,0,0 }); int ridx = tree.size() - 1;
	tree[node].l = lidx; tree[node].r = ridx;
	int MID = (S + E) >> 1;
	init(lidx, S, MID); init(ridx, MID + 1, E);
}
int LCA(int a, int b) {
	if (D[a] != D[b]) {
		if (D[a] < D[b]) {
			int tmp = a; a = b; b = tmp;
		}
		int gap = D[a] - D[b];
		for (int i = 0; i < MAX; i++) {
			//shift 연산자(<<)는 우선순위에 신경써야 함
			if ((gap & (1 << i)) != 0) {
				a = S[a][i];
			}
		}
	}
	if (a == b)return a;
	for (int i = MAX-1; i >= 0; i--) {
		if (S[a][i] != S[b][i]) {
			a = S[a][i]; b = S[b][i];
		}
	}
	return S[a][0];
}
void update(int i, int node, int S, int E) {
	if (S == E) {
		tree[node].v = 1; return;
	}
	int MID = (S + E) >> 1;
	if (i <= MID) {
		Nd lchd = tree[tree[node].l];
		tree.push_back({ lchd.l, lchd.r , lchd.v });
		int lidx = tree.size() - 1;	tree[node].l = lidx;
		update(i, lidx, S, MID);
	}
	else {
		Nd rchd = tree[tree[node].r];
		tree.push_back({ rchd.l, rchd.r , rchd.v });
		int ridx = tree.size() - 1;	tree[node].r = ridx;
		update(i, ridx, MID + 1, E);
	}
	tree[node].v = tree[tree[node].l].v + tree[tree[node].r].v;
}
int query(int l, int r, int node, int S, int E) {
	if (r < S || E < l)return 0;
	if (l <= S && E <= r) {
		return tree[node].v;
	}
	int MID = (S + E) >> 1;
	return query(l, r, tree[node].l, S, MID) + query(l, r, tree[node].r, MID + 1, E);
}
int solve(int x, int y, int k) {
	int lca = LCA(x, y);
	int l = 1, r = N;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		int cnt = query(1, mid, H[x], 1, N) + query(1, mid, H[y], 1, N) - query(1, mid, H[lca], 1, N);
		if (lca != 1) {
			cnt -= query(1, mid, H[P[lca]], 1, N);
		}
		if (cnt<k) {
			l = mid + 1;
		}
		else {
			r = mid;
		}
	}
	return l;
}
bool compare(const Et &a, const Et &b) {
	return a.v < b.v;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> N >> M;
	for (int n = 1; n <= N; n++) { int v; cin >> v; W[n] = { n,v,0 }; RW[n] = { n,v,0 }; }
	for (int n = 1; n < N; n++) { int x, y; cin >> x >> y; G[x].push_back(y); G[y].push_back(x); }
	bfs(); tree.push_back({ 0,0,0 }); H[0] = 0; init(0, 1, N); SPAS();
	sort(RW + 1, RW + 1 + N, compare); for (int n = 1; n <= N; n++) { W[RW[n].i].cv = n; }
	queue<int> Q; Q.push(1);
	while (!Q.empty()) {
		int here = Q.front(); Q.pop();
		tree.push_back({ 0,0,0 }); int node = tree.size() - 1;
		int pn = (here==1)? 0 : H[P[here]];
		tree[node].l = tree[pn].l; tree[node].r = tree[pn].r; H[here] = node;
		update(W[here].cv, H[here], 1, N);
		vector<int> nxts = G[here]; 
		for (int i = 0; i < nxts.size(); i++) {
			int nxt = nxts[i]; if (H[nxt] == 0)Q.push(nxt);
		}
	}
	for (int m = 0; m < M; m++) { 
		int x, y, k; cin >> x >> y >> k;
		cout << RW[solve(x, y, k)].v << "\n";
	}
	return 0;
}