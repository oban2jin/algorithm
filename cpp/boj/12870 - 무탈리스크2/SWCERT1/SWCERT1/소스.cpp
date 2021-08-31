#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
vector<int> Ts;
int S;
int ad[] = {9,3,1};
int D[1201][21][100][7];
int N;
int dp(int c,int k,int n) {
	//c:남은 무탈의 공격횟수, k-th SCV부터 공격 가능, 
	//가능한 공격력 사용했는지 이진수 : 111(9,3,1)로 표시 
	//cout << "S=" << S << ",k=" << k << ",n=" << n << ",c="<< c << ",D[]=" << D[S][k][c][n] << endl;
	if (S == 0) return 1;
	if (c==0 && n==0) return 0;

	int &rst = D[S][k][c][n];
	if (rst != -1)return rst;

	int i = 0; rst = 0;
	if (n==0) {
		i = 0; n = 7;  --c;
	}else{
		i = k;
	}
	for (; i < Ts.size(); i++) {
		for (int j = 0; j < 3; j++){
			if (0<Ts[i] && rst==0 && (n&(1<<j))!=0) {
				int here = 0;
				if (Ts[i] < ad[j]) {
					here = Ts[i];
				}
				else {
					here = ad[j];
				}
				S -= here; Ts[i] -= here;
				rst = dp(c,(i+1)%N,n-(1<<j));
				S += here; Ts[i] += here;
			}
		}
	}
	return rst;
}
int solve() {
	int l = 1; int r = 100;
	while (l < r) {
		int m = (l + r) >> 1;
		if (dp(m,0,0)==1) {
			r = m;
		}
		else {
			l = m + 1;
		}
	}
	return l;
}
int main() {
	//freopen("D:/workspacecpp/boj/12870 - 무탈리스크2/log.txt", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(NULL);
	memset(D, -1, sizeof(D));
	cin >> N; for (int i = 0; i < N; i++) { int t; cin >> t; Ts.push_back(t);  S += t; }
	//cout << solve();
	cout << dp(7, 0, 0);
	return 0;
}