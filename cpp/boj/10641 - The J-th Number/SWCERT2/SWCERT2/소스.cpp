#include <iostream>
#include <algorithm>
#include <vector>
#define va first
#define vb second
#define pp push_back
#define ep emplace_back
#define lb lower_bound
#define all(v) (v).begin(),(v).end()
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int mx = 1 << 19;
int n, m, q;
vector<int> cmp;
int N;
vector<int> cmpv;

struct upds {
	int s, e, v;
	bool operator< (upds &u) {
		return v < u.v;
	}
} U[mx];

int qa[mx], qb[mx], qs[mx], qe[mx];
ll qj[mx];

ll seg[mx * 2];
int laz[mx * 2];
int len[mx * 2];

int nnode = 0;
void build(int now, int s, int e) {
	if (s == e) {
		nnode = max(nnode, now);
		len[now] = cmp[s + 1] - cmp[s];
		return;
	}
	int m = s + e >> 1;
	build(now << 1, s, m);
	build(now << 1 | 1, m + 1, e);
	len[now] = len[now << 1] + len[now << 1 | 1];
}

void flush(int now, int s, int e) {
	if (!laz[now]) return;
	seg[now] += ll(laz[now]) * len[now];
	if (s == e) {
		laz[now] = 0;
		return;
	}
	laz[now << 1] += laz[now];
	laz[now << 1 | 1] += laz[now];
	laz[now] = 0;
}

void upd(int now, int s, int e, int l, int r) {
	flush(now, s, e);
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		++laz[now];
		flush(now, s, e);
		return;
	}
	int m = s + e >> 1;
	upd(now << 1, s, m, l, r);
	upd(now << 1 | 1, m + 1, e, l, r);
	seg[now] = seg[now << 1] + seg[now << 1 | 1];
}

ll sum(int now, int s, int e, int l, int r) {
	flush(now, s, e);
	if (e < l || r < s) return 0;
	if (l <= s && e <= r) {
		return seg[now];
	}
	int m = s + e >> 1;
	return sum(now << 1, s, m, l, r)
		+ sum(now << 1 | 1, m + 1, e, l, r);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> q;
	for (int i = 0; i < m; i++) {
		cin >> U[i].s >> U[i].e >> U[i].v;
		++U[i].e;
		cmp.pp(U[i].s);
		cmp.pp(U[i].e);
		cmpv.pp(U[i].v);
	}
	sort(U, U + m);
	for (int i = 0; i < q; i++) {
		cin >> qa[i] >> qb[i] >> qj[i];
		++qb[i];
		cmp.pp(qa[i]);
		cmp.pp(qb[i]);
	}
	sort(all(cmp));
	sort(all(cmpv));
	cmp.erase(unique(all(cmp)), cmp.end());
	cmpv.erase(unique(all(cmpv)), cmpv.end());

	for (int i = 0; i < m; i++) {
		U[i].s = lb(all(cmp), U[i].s) - cmp.begin();
		U[i].e = lb(all(cmp), U[i].e) - cmp.begin();
		U[i].v = lb(all(cmpv), U[i].v) - cmpv.begin();
	}
	for (int i = 0; i < q; i++) {
		qa[i] = lb(all(cmp), qa[i]) - cmp.begin();
		qb[i] = lb(all(cmp), qb[i]) - cmp.begin();
	}
	N = cmp.size() - 1;
	build(1, 0, N - 1);
	for (int i = 0; i < q; i++) {
		qs[i] = 0;
		qe[i] = (int)cmpv.size() - 1;
	}
	bool pbs = true;
	vector<pii> tsk;
	while (pbs) {
		pbs = false;
		tsk.clear();
		fill(seg, seg + nnode + 1, 0);
		fill(laz, laz + nnode + 1, 0);
		for (int i = 0; i < q; i++)
			if (qs[i] < qe[i]) tsk.ep(qs[i] + qe[i] >> 1, i);
		sort(all(tsk));
		int cur = 0;
		for (pii &p : tsk) {
			for (; cur < m && U[cur].v <= p.va; cur++)
				upd(1, 0, N - 1, U[cur].s, U[cur].e - 1);
			if (sum(1, 0, N - 1, qa[p.vb], qb[p.vb] - 1) >= qj[p.vb]) {
				qe[p.vb] = p.va;
			}
			else {
				qs[p.vb] = p.va + 1;
			}
			if (qs[p.vb] < qe[p.vb]) pbs = true;
		}
	}
	for (int i = 0; i < q; i++) cout << cmpv[qs[i]] << '\n';
}