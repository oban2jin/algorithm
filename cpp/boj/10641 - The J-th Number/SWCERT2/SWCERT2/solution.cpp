#include <iostream>
#include <algorithm>
#include <vector>
typedef long long lld;
using namespace std;
const int MAX = 1 << 19;
lld tree[MAX * 2];
int lazy[MAX * 2];
int ln[MAX * 2];
int N, M, Q;
int MAXN, MAXV;
int lo[100000]; int hi[100000];
struct P {
	int i, m;
	bool operator < (const P &o) {
		return m < o.m;
	}
};
struct Qy {
	int a, b;
	lld v;
	bool operator < (const Qy &o) {
		return v < o.v;
	}
}; vector<Qy>Qs; vector<Qy> Ps;
vector<int> R; vector<int>V;
void init(int node, int S, int E) {
	if (S == E) {
		//현재  node가 대표하는 실제 구간의 사이즈가 얼마인지
		ln[node] = R[S + 1] - R[S];
		return;
	}
	int MID = (S + E) >> 1;
	init(node * 2, S, MID); init(node * 2 + 1, MID + 1, E);
	ln[node] = ln[node * 2] + ln[node * 2 + 1];
}
void propagation(int node, int S, int E) {
	int MID = (S + E) >> 1;
	//왼쪽 자식 노드 lazy 값 반영
	tree[node * 2] += ln[node * 2] * lazy[node];
	lazy[node * 2] += lazy[node];
	//오늘쪽 자식 노드 lazy 값 반영
	tree[node * 2 + 1] += ln[node * 2 + 1] * lazy[node];
	lazy[node * 2 + 1] += lazy[node];
	lazy[node] = 0;
}
void update(int l, int r, int v, int node, int S, int E) {
	if (r < S || E < l)return;
	if (l <= S && E <= r) {
		tree[node] += ln[node]*v; lazy[node] += v;
		return;
	}
	propagation(node, S, E);
	int MID = (S + E) >> 1;
	update(l, r, v, node * 2, S, MID); update(l, r, v, node * 2 + 1, MID + 1, E);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}
lld query(int l, int r, int node, int S, int E) {
	if (r < S || E < l)return 0;
	if (l <= S && E <= r)return tree[node];
	propagation(node, S, E);
	int MID = (S + E) >> 1;
	return query(l, r, node * 2, S, MID) + query(l, r, node * 2 + 1, MID + 1, E);
}
/*
 1.Lazy Propagation : 역쉬나 생각했던 것 처럼/완전히 이해하고 있었던 것은 아니였다. 
    : 멈출수 있을때 멈추고(현재 나 자신은 수정하고) , 필요할때 내려 보내주세요.
	: 내려보내는것은 무조건으로 내려보내세요. 계산상 내려 보낸 값이 0이믄 아무 상관 없어요
 2.PST와 Lazy Propagation으로 구현 가능할라나?
   => 일본 도전자의 코드를 이제보면 이해가 갈라나?
      PST + Lazy Propagation +  BS 코드 =>  나도 이렇게 해결하고 싶었는디 ㅡ.ㅡ
 3.Lazy Propagation  + PBS으로 해결을 했으나. 숨어 있는 조건이 역쉬나 많았음. 
    : 구간 압축 => 결국 대표하는 구간의 크기가 달라져서, 전파되는 값도 영향을 받는다.
*/
int main() {
	cin >> N >> M >> Q;
	for (int i = 0; i < M; i++) {
		int a, b, v;  cin >> a >> b >> v;
		Qs.push_back({ a,++b,v });
		//구간 압축을 위해서, R[S:E] =   S<= R < E 
		R.push_back(a); R.push_back(b);
		V.push_back(v);
	}
	for (int i = 0; i < Q; i++) {
		int x, y; lld j; cin >> x >> y >> j;
		Ps.push_back({ x,++y,j });
		//구간 압축을 위해서, R[S:E] =   S<= R < E 
		R.push_back(x); R.push_back(y);
	}
	sort(R.begin(), R.end()); sort(V.begin(), V.end());
	//중복 제거
	R.erase(unique(R.begin(), R.end()), R.end());
	V.erase(unique(V.begin(), V.end()), V.end());
	MAXN = R.size() - 2; MAXV = V.size() - 1;

	for (int i = 0; i < M; i++) {
		Qs[i].a = lower_bound(R.begin(), R.end(), Qs[i].a) - R.begin();
		Qs[i].b = lower_bound(R.begin(), R.end(), Qs[i].b) - R.begin();
		Qs[i].v = lower_bound(V.begin(), V.end(), Qs[i].v) - V.begin();
	}
	for (int i = 0; i < Q; i++) {
		Ps[i].a = lower_bound(R.begin(), R.end(), Ps[i].a) - R.begin();
		Ps[i].b = lower_bound(R.begin(), R.end(), Ps[i].b) - R.begin();
		hi[i] = MAXV; lo[i] = 0;
	}

	init(1, 0, MAXN);
	sort(Qs.begin(), Qs.end());
	vector<P> VT;  bool flag = true;

	while (flag) {
		//각종초기화
		flag = false; VT.clear();
		fill(tree, tree + (MAX * 2), 0);
		fill(lazy, lazy + (MAX * 2), 0);
		//대상이 되는 Ps들 mid 값 설정하고
		for (int i = 0; i < Q; i++) {
			if (lo[i] < hi[i]) {
				VT.push_back({ i,(lo[i] + hi[i]) >> 1 });
				flag = true;
			}
		}
		sort(VT.begin(), VT.end());
		int cur = 0;
		for (P &idxPs : VT) {
			for (; cur < M && Qs[cur].v <= idxPs.m; cur++) {
				Qy hereQ = Qs[cur]; update(hereQ.a, hereQ.b - 1, 1, 1, 0, MAXN);
			}
			Qy herePs = Ps[idxPs.i];
			if (herePs.v <= query(herePs.a, herePs.b - 1, 1, 0, MAXN)) {
				hi[idxPs.i] = idxPs.m;
			}
			else {
				lo[idxPs.i] = idxPs.m + 1;
			}
		}
	}
	for (int i = 0; i < Q; i++) {
		cout << V[lo[i]] << endl;
	}
	return 0;
}