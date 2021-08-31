#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
typedef long long lld;
using namespace std;
int N, M, Q;
const int MAXMQ = 100000;
struct Mn
{
	// 1<=a<=b<=10^9
	// 1<=v<=10^9
	int a, b, v;
	bool operator < (const Mn &c) {
		if (a != c.a) {
			return a < c.a;
		}
		else {
			return b < c.b;
		}
	}
};
bool compMn(const Mn &a, const Mn &b) {
	if (a.v != b.v) {
		return a.v < b.v;
	}
	else {
		if (a.a != b.a) {
			return a.a < b.a;
		}
		else {
			return a.b < b.b;
		}
	}
}
struct  Nd
{
	Nd *l, *r; lld cnt;
	Nd(Nd *l, Nd *r, int cnt) :l(l), r(r), cnt(cnt) {};
	Nd *insert(int S, int E, int i, lld cnt);
} *null, *H[MAXMQ];
Nd* Nd::insert(int S, int E, int i, lld cnt) {
	if (S <= i && i <= E) {
		if (S == E) {
			return new Nd(null, null, this->cnt + cnt);
		}
		int MID = (S + E) >> 1;
		return new Nd(this->l->insert(S, MID, i, cnt), this->r->insert(MID + 1, E, i, cnt), this->cnt + cnt);
	}
	return this;
}
struct Rn
{
	int a, b;
};
bool operator < (const Rn &a, const Rn &b) {
	if (a.b == b.b) {
		return  a.a > b.a;
	}
	else {
		return a.b > b.b;
	}
}
Mn Ms[MAXMQ];
vector<Rn> RS;
void update(int i, lld v, Nd *node, int S, int E) {
	if (S == E) { node->cnt += v; return; }
	int MID = (S + E) >> 1; Nd *lch = node->l; Nd *rch = node->r;
	if (i <= MID) {
		node->l = new Nd(lch->l, lch->r, lch->cnt);
		update(i, v, node->l, S, MID);
	}
	else {
		node->r = new Nd(rch->l, rch->r, rch->cnt);
		update(i, v, node->r, MID + 1, E);
	}
	node->cnt = node->l->cnt + node->r->cnt;
}
lld query(int l, int r, Nd *node, int S, int E) {
	if (r < S || E < l)return 0;
	if (l <= S && E <= r)return node->cnt;

	int MID = (S + E) >> 1;
	return query(l, r, node->l, S, MID) + query(l, r, node->r, MID + 1, E);
}
vector<int> U;
vector<Rn> SZ[MAXMQ+1];
int getRnNumber(int i, int s) {
	int l = 0; int r = RS.size() - 1;
	if (s == 0) {
		while (l < r) {
			int m = (l + r) >> 1;
			if (i <= RS[m].a) {
				r = m;
			}
			else {
				l = m + 1;
			}
		}
	}
	else {
		while (l < r) {
			int m = (l + r) >> 1;
			if (i <= RS[m].b) {
				r = m;
			}
			else {
				l = m + 1;
			}
		}
	}

	return l;
}

void PST() {
	sort(Ms, Ms + M, compMn);
	U.push_back(0);
	int cV = Ms[0].v; U.push_back(cV);
	for (int m = 0; m < M; m++) {
		Mn here = Ms[m];
		if (here.v != cV) {
			cV = here.v; U.push_back(cV);
		}
		SZ[U.size() - 1].push_back({ getRnNumber(Ms[m].a,0),getRnNumber(Ms[m].b,1) });
		//cout <<cV<<","<< Ms[m].a << "=>" << getRnNumber(Ms[m].a,0) <<"|"<< Ms[m].b << "=>" << getRnNumber(Ms[m].b,1) << "\n";
	}
	null = new Nd(NULL, NULL, 0); null->l = null->r = null;
	H[0] = new Nd(null, null, 0); 
	for (int i = 1; i < U.size(); i++) {
		int cV = i; vector<Rn> cM = SZ[cV]; Nd *pH = H[cV - 1]; H[cV] = new Nd(pH->l, pH->r, pH->cnt);
		vector<int> T(RS.size(), 0);
		//vector<int> T(RS.size()+1, 0); 
		for (int i = 0; i < cM.size(); i++) {
			int a = cM[i].a; int b = cM[i].b;
			for (int k = a; k <= b; k++) {
				T[k] += RS[k].b - RS[k].a + 1;
			}
		}
		for (int i = 0; i < T.size(); i++) {
			if (T[i] != 0) {
				update(i, T[i], H[cV], 0, RS.size() - 1);
			}
		}
		//for (int j = 0; j < cM.size(); j++) {
		//	int a = cM[j].a; int b = cM[j].b; 
		//	for (int k = a; k <= b; k++) {
		//		update(k, RS[k].b-RS[k].a+1, H[cV], 0, RS.size()-1);
		//	}
		//}
	}
}
void divRange() {
	//Persitence Segment Tree구성
	priority_queue<Rn> Q;
	for (int i = 0; i < M; i++) {
		Q.push({ 0,Ms[i].a });	Q.push({ 1,Ms[i].b });
	}
	int S = 1; int E = 1;
	while (!Q.empty()) {
		Rn cR = Q.top(); Q.pop();
		if (cR.a == 0 && S < cR.b) {
			//시작구간 , R[S:cR.b-1] 구간 도출/ S->cR.b,E->cR.b;
			RS.push_back({ S,cR.b - 1 });
			//cout << RS.size()-1 << "=>[" << S << ":" << cR.b - 1 << "]\n";
			S = cR.b; E = cR.b;
		}
		else if (cR.a == 1 && S <= cR.b) {
			//종료구간 , R[S:cR.b] 구간 도출/ S-> cR.b+1, E -> cR.b+1;
			RS.push_back({ S,cR.b });
			//cout << RS.size() - 1 << "=>[" << S << ":" << cR.b << "]\n";
			S = cR.b + 1, E = cR.b + 1;
		}
	}
	if (S <= N) {
		RS.push_back({ S,N });
		//cout << RS.size() - 1 << "=>[" << S << ":" << N << "]\n";
	}
}
int solve(int x, int y, lld j) {
	int l = 0; int r = U.size() - 1;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (query(x, y, H[mid], 0, RS.size() - 1) < j) {
			l = mid + 1;
		}
		else {
			r = mid;
		}
	}
	return l;
}
int main() {
	freopen("D:/workspacecpp/boj/10641 - The J-th Number/sample.txt", "r", stdin);
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> N >> M >> Q;
	for (int m = 0; m < M; m++) {
		int a, b, v; cin >> a >> b >> v; Ms[m] = { a,b,v };
	}
	divRange();
	PST();
	for (int q = 0; q < Q; q++) {
		int x, y; lld j; cin >> x >> y >> j;
		cout << U[solve(getRnNumber(x, 0), getRnNumber(y, 1), j)] << "\n";
	}
	return 0;
}