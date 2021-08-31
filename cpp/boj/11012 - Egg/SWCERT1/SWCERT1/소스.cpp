#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
struct Nd {
	int l, r;
	int v;
};
const int MAX = 100002;
int T, N, M;
long long ANS;
int head[MAX];
vector<Nd> node;
vector<int> GX[MAX];
void init(int nidx, int left, int right) {
	if (left == right)return;
	int mid = (left + right) / 2;
	node.push_back({ 0,0,0 }); node[nidx].l = node.size() - 1; init(node[nidx].l, left, mid);
	node.push_back({ 0,0,0 }); node[nidx].r = node.size() - 1; init(node[nidx].r, left, mid);
}
int query(int l, int r, int nidx, int left, int right) {
	if (r < left || l > right)return 0;
	else if (l <= left && right <= r)return node[nidx].v;
	int mid = (left + right) / 2;
	return query(l, r, node[nidx].l, left, mid) + query(l, r, node[nidx].r, mid + 1, right);
}
// array[i]=v로 변경했을때, node[nidx]를 root로 구간트리를 변경해간다.
void update(int i, int v, int nidx, int left, int right) {
	if (left > i || i > right)return;
	if (left == right) {
		//루트 노드의 값을 변경하고 넘어오는 구조라..
		return;
	}
	int mid = (left + right) / 2;
	if (i <= mid) {
		int lidx = node[nidx].l; node.push_back({ node[lidx].l,node[lidx].r,node[lidx].v + v });
		node[nidx].l = node.size() - 1; update(i, v, node[nidx].l, left, mid);
	}
	else {
		int ridx = node[nidx].r; node.push_back({ node[ridx].l,node[ridx].r,node[ridx].v + v });
		node[nidx].r = node.size() - 1; update(i, v, node[nidx].r, mid + 1, right);
	}
}
int main() {
	scanf("%d", &T); for (int t = 0; t < T; t++) {
		fill(head, head + MAX, 0);  for (int i = 0; i < MAX; i++) { GX[i].clear(); }
		ANS = 0;
		scanf("%d %d", &N, &M);
		for (int n = 0; n < N; n++) {
			int x, y; scanf("%d %d", &x, &y); ++x; ++y; GX[y].push_back(x);
		}
		node.resize(2); node.push_back({ 0,0,0 }); head[0] = 0;	init(0, 1, MAX - 1);
		for (int y = 1; y < MAX; y++) {
			if (y != 1 && head[y] == 0) {
				node.push_back({ node[head[y - 1]].l,node[head[y - 1]].r,node[head[y - 1]].v });
				head[y] = node.size() - 1;
			}
			for (int i = 0; i < GX[y].size(); i++) {
				int nxtx = GX[y][i]; node[head[y]].v = node[head[y]].v + 1;
				update(nxtx, 1, head[y], 1, MAX - 1);
			}
		}
		for (int m = 0; m < M; m++) {
			int l, r, b, t; scanf("%d %d %d %d", &l, &r, &b, &t); ++b; ++t; ++l; ++r;
			ANS = ANS + query(l, r, head[t], 1, MAX - 1) - query(l, r, head[b - 1], 1, MAX - 1);
		}
		printf("%lld\n", ANS);
	}
	return 0;
}
