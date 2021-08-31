#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lld;
const  lld INF = 2e18;
struct Line {
	lld a, b;
	lld get(lld x) {
		return a*x + b;
	}
};
struct Node {
	lld s, e;
	int l, r;
	Line ln;
};
vector<Node> tree;
int init(lld mn,lld mx) {
	tree.push_back({ mn,mx,-1,-1,{ 0,-INF } });
	return tree.size() - 1;
}
void update(int node, Line ln) {
	Line hi = tree[node].ln; Line low = ln;
	Node here = tree[node];
	if (hi.get(here.s) < low.get(here.s))swap(hi, low);
	lld m = (here.s + here.e) >> 1;
	if (low.get(here.e) <= hi.get(here.e)) {
		tree[node].ln = hi; return;
	}

	if (low.get(m) < hi.get(m)) {
		tree[node].ln = hi;
		if (tree[node].r == -1) {
			tree[node].r = tree.size();
			tree.push_back({ m + 1,here.e,-1,-1,{ 0,-INF } });
			//tree[node].r = init(m + 1,here.e); 이 메모리 초과를 발생시켰음.
			//아마도 Recursion에 따른 Stack Memory가 터진것으로 생각됨
		}
		update(tree[node].r, low);
	}
	else {
		tree[node].ln = low;
		if (tree[node].l == -1) {
			tree[node].l = tree.size();
			tree.push_back({ here.s,m,-1,-1, { 0,-INF } });
		}
		update(tree[node].l, hi);
	}
}
lld query(int node, lld xq) {
	if (node == -1) return -INF;
	//기저 사례를 확인한다.
	Node here = tree[node];  lld m = (here.s + here.e) >> 1;
	lld rst = here.ln.get(xq);
	if (xq <= m) {
		rst = max(query(here.l, xq), rst);
	}
	else {
		rst = max(query(here.r, xq), rst);
	}
	return rst;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int Q; cin >> Q; init(-2e12,2e12);
	for (int i = 0; i < Q; i++) {
		int q; lld a, b;
		cin >> q;
		if (q == 1) {
			cin >> a >> b;
			Line ln = { a,b };
			update(0, ln);
		}
		else {
			cin >> a;
			cout << query(0, a) << "\n";
		}
	}
	return 0;
}