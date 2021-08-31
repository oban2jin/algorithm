#include <iostream>
#include <algorithm>
#include <vector>
typedef long long lld;
using namespace std;
const int MXQ = 1000;
const int INF = 1000000007;
int N, X0, A, B, Q;
lld ANS;
int Qs[MXQ];
int C[MXQ + 1], lo[MXQ], hi[MXQ], mid[MXQ];
struct Qry
{
	int l, r, m, q;
	bool operator <(const Qry &o) {
		return m < o.m;
	}
}; vector<int> VT;
int BS(int v) {
	int l = 0; int r = Q;
	while (l < r) {
		int m = (l + r) >> 1;
		if (v <= mid[m]) {
			r = m;
		}
		else {
			l = m + 1;
		}
	}
	return l;
}
/*
 1.여러가지 회고의 거리를 던져준다. 
 2.역시 문제를 끝까지 읽어야 문제해결의 결정적 단서를 확인한다.
    (매번 Qry집합을 m기준으로 소팅하려는 접근이 사실은 대단한 뻘짓)
 3.lower_bound / 이분탐색의 하한도 의미를 정확하게 이해했다. 
 4.프로그램 순서 제어는 최대한 심플하고 명확하게 / 이거 때문에 진짜 밤샜음
*/
int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> N >> X0 >> A >> B;
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		int t;
		cin >> t; Qs[i] = t + 1;
		lo[i] = 0; hi[i] = INF - 1;
	}
	sort(Qs, Qs + Q);
	bool flag = true;
	while (flag) {
		flag = false;
		fill(C, C + Q + 1, 0); 
		for (int i = 0; i < Q; i++) {
			if (lo[i] < hi[i]) {
				flag = true; break;
			}
		}
		if (!flag)break;
		lld X = X0;
		for (int n = 0; n < N; n++) {
			C[BS(X)]++;
			X = (X * A + B) % INF;
		}
		for (int i = 1; i < Q; i++) {
			C[i] += C[i - 1];
		}
		for (int i = 0; i < Q; i++) {
			//if (lo[i] == hi[i])continue;
			if (Qs[i] <= C[i]) {
				hi[i] = mid[i];
			}
			else {
				lo[i] = mid[i] + 1;
			}
			mid[i] = (lo[i] + hi[i]) >> 1;
		}
	}
	for (int i = 0; i < Q; i++) {
		ANS += lo[i];
	}
	cout << ANS << "\n";
	return 0;
}