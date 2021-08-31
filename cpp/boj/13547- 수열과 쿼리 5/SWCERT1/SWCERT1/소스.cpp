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
vector<qry> Qs;
int N, M;
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> N; for (int n = 1; n <= N; n++) { cin >> As[n]; sq = sqrt(N); }
	cin >> M; for (int m = 0; m < M; m++) { int l, r; cin >> l >> r; Qs.push_back({ l,r,m }); }
	sort(Qs.begin(), Qs.end());
	for (int i = Qs[0].l; i <= Qs[0].r; i++) {
		if (U[As[i]] == 0) { ++U[0]; } 
		++U[As[i]];
	}
	ANS[Qs[0].i] = U[0]; int &rst = U[0]; int l = Qs[0].l; int r = Qs[0].r;
	for (int m = 1; m < M; m++) {
		qry s = Qs[m];
		while (s.l < l) {
			if (U[As[--l]] == 0) { ++rst; } ++U[As[l]];
		}
		while (s.l > l) {
			if (U[As[l]] == 1) { --rst; } --U[As[l++]];
		}
		while (s.r < r) {
			if (U[As[r]] == 1) { --rst; } --U[As[r--]];
		}
		while (s.r > r) {
			if (U[As[++r]] == 0) { ++rst; } ++U[As[r]];
		}
		ANS[s.i] = rst;
	}
	for (int m = 0; m < M; m++) { cout << ANS[m] << "\n"; }
}