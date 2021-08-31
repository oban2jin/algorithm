#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
int sq;
struct  qry
{
	int l, r, i;
	bool operator < (const qry &o) {
		int s1 = l / sq; int s2 = o.l / sq;
		if (s1 == s2)return r < o.r;
		return s1 < s2;
	}
};
int U[1000000 + 1];
int As[1000000 + 1];
int ANS[100000 + 1];
int CNT[1000000 + 1][1];
vector<qry> Qs;
int N, M;
int MAX;
void add(int v) {
	//v의 현재 갯수 = U[v], cnt = v의 갯수와 동일한 갯수의 다른 수가  몇개 있는지
	if (CNT[U[v]][0] != 0) {
		--CNT[U[v]][0];
		////줄이전 갯수에서 v를 빼주고
		//for (int i = 1; i <= CNT[U[v]][0]; i++) {
		//	if (CNT[U[v]][i] == v) { CNT[U[v]][i] = 0; --CNT[U[v]][0]; break; }
		//}
	}
	++U[v]; ++CNT[U[v]][0];
	////늘인 갯수에 v를 넣어주고
	//for (int i = 1; i <= CNT[U[v]][0]; i++) {
	//	if (CNT[U[v]][i] == 0) { CNT[U[v]][i] = v; break; }
	//}
	if (MAX < U[v])MAX = U[v];
}
void remove(int v) {
	if (CNT[U[v]][0] != 0) {
		--CNT[U[v]][0];
		////줄이전 갯수에서 v를 빼주고
		//for (int i = 1; i <= CNT[U[v]][0]; i++) {
		//	if (CNT[U[v]][i] == v) { CNT[U[v]][i] = 0; --CNT[U[v]][0]; break; }
		//}
	}
	--U[v]; ++CNT[U[v]][0];
	////줄인 갯수에 v를 넣어주고
	//for (int i = 1; i <= CNT[U[v]][0]; i++) {
	//	if (CNT[U[v]][i] == 0) { CNT[U[v]][i] = v; break; }
	//}
	if (CNT[MAX][0] == 0) {
		--MAX;
	}
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> N; for (int n = 1; n <= N; n++) { cin >> As[n]; }
	sq = sqrt(N);
	cin >> M; for (int m = 0; m < M; m++) { int l, r; cin >> l >> r; Qs.push_back({ l,r,m }); }
	sort(Qs.begin(), Qs.end()); MAX = 0;
	for (int i = Qs[0].l; i <= Qs[0].r; i++) {
		add(As[i]);
	}
	int l = Qs[0].l; int r = Qs[0].r;	ANS[Qs[0].i] = MAX;
	for (int m = 1; m < M; m++) {
		qry s = Qs[m]; int cnt, idx;
		while (s.l < l) {
			--l; add(As[l]);
		}
		while (s.l > l) {
			remove(As[l]); ++l;
		}
		while (s.r < r) {
			remove(As[r]); r--;
		}
		while (s.r > r) {
			++r; add(As[r]);
		}
		ANS[s.i] = MAX;
	}
	for (int m = 0; m < M; m++) { cout << ANS[m] << "\n"; }
}