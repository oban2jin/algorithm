#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
struct Nd
{
	int l, r, v;
	Nd() {}
	Nd(int l, int r, int v) :l(l), r(r), v(v) {}
};
struct  L
{
	int i, v;
	L() {}
	L(int i, int v) :i(i), v(v) {}
};
struct Q
{
	int l, r, k;
	Q() {}
	Q(int l, int r, int k) :l(l), r(r), k(k) {}
};
const int MAXK = 100000 + 1;
int N, M;
vector<L> Ls;
vector<Q> Qs;
int head[MAXK];
vector<Nd> node;
bool comp(const L &a, const L &b) {
	return a.v < b.v;
}
void init(int nidx, int l, int r) {
	if (l == r)return;
	int mid = (l + r) / 2;
	node.push_back({ 0,0,0 }); node[nidx].l = node.size() - 1; init(node[nidx].l, l, mid);
	node.push_back({ 0,0,0 }); node[nidx].r = node.size() - 1; init(node[nidx].r, mid + 1, r);
}
void update(int i, int v, int nidx, int left, int right) {
	if (i < left || right < i)return;
	if (left == right)return;
	int mid = (left + right) / 2;
	if (i <= mid) {
		int lidx = node[nidx].l; node.push_back({ node[lidx].l,node[lidx].r,node[lidx].v + 1 });
		node[nidx].l = node.size() - 1; update(i, v, node[nidx].l, left, mid);
	}
	else {
		int ridx = node[nidx].r; node.push_back({ node[ridx].l,node[ridx].r,node[ridx].v + 1 });
		node[nidx].r = node.size() - 1; update(i, v, node[nidx].r, mid + 1, right);
	}
}
int query(int l, int r, int nidx, int left, int right) {
	if (right < l || r < left) {
		return 0;
	}
	else if (l <= left && right <= r) {
		return node[nidx].v;
	}
	int mid = (left + right) / 2;
	return query(l, r, node[nidx].l, left, mid) + query(l, r, node[nidx].r, mid + 1, right);
}
int solve(int l, int r, int k) {
	int mid = 0; int low = 1; int high = N;
	int rst = 0;
	while (low <= high) {
		mid = (low + high) / 2;
		rst = query(l, r, head[mid], 1, 100000);
		if (rst < k) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	return Ls[low - 1].v;
}
void printChild(int nidx) {
	vector<int> D(MAXK, 0);
	queue<int> Q; Q.push(nidx); int cr = 0;
	while (!Q.empty()) {
		int here = Q.front(); Q.pop();
		if (D[here] != cr) { printf("\n"); cr = D[here]; }
		printf("  [node=%d/l=%d/r=%d/v=%d]", here, node[here].l, node[here].r, node[here].v);
		if (node[here].l != 0 && node[here].r != 0 && node[here].v != 0) {
			D[node[here].l] = D[here] + 1; D[node[here].r] = D[here] + 1;
			Q.push(node[here].l);  Q.push(node[here].r);
		}
	}
}
int main() {
	scanf("%d %d", &N, &M);
	for (int n = 0; n < N; n++) { int l; scanf("%d", &l); Ls.push_back(L(n + 1, l)); }
	for (int m = 0; m < M; m++) { int l, r, k; scanf("%d %d %d", &l, &r, &k); Qs.push_back(Q(l, r, k)); }
	sort(Ls.begin(), Ls.end(), comp);

	fill(head, head + MAXK, 0);
	node.push_back({ 0,0,0 }); head[0] = 0; init(0, 1, 100000);
	for (int k = 1; k < N + 1; k++) {
		node.push_back({ node[head[k - 1]].l,node[head[k - 1]].r,node[head[k - 1]].v + 1 }); head[k] = node.size() - 1;
		update(Ls[k - 1].i, 1, head[k], 1, 100000);
	}
	for (int m = 0; m < M; m++) {
		printf("%d\n", solve(Qs[m].l, Qs[m].r, Qs[m].k));
	}
	/*
		while(1){
			int l,r,k; scanf("%d %d %d",&l,&r,&k);
			int ans = query(l,r,head[k],1,100000);
			printf("l=[%d],r=[%d],k=[%d],ans=[%d],head=[%d|%d]\n",l,r,k,ans,node[head[k]].v,head[k]);
		}
	*/
	return 0;
} // namespace std;