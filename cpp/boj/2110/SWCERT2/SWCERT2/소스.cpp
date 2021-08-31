#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N, C;
vector<int> L;
int solve() {
	int ans = 0;
	int l = 1, h = L[N - 1] - L[0], m = 0;
	while (l <= h) {
		m = (l + h) / 2; int c = 0; int cn = 1;
		for (int n = 1; n < N; n++) {
			if ((L[n] - L[c]) >= m) { c = n; ++cn; }
		}
		if (cn < C) {
			//공유기 더 설치되어야 함 => 간격을 줄이여한다.
			h = m - 1;
		}
		else {
			//공유기 설치 숫자 줄여야 함 => 간격을 늘여야 한다.
			if(ans < m)ans = m;
			l = m + 1;
		}
	}
/*
	int left = 1; // 가능한 최소 거리
	int right = L[N - 1] - L[0]; // 가능한 최대 거리
	int d = 0;
	int ans = 0;

	while (left <= right) {
		int mid = (left + right) / 2; // 기준
		int start = L[0];
		int cnt = 1;

		// 간격(d) 를 기준으로 공유기 설치
		for (int i = 1; i < N; i++) {
			d = L[i] - start;
			if (mid <= d) {
				++cnt;
				start = L[i];
			}
		}

		if (cnt >= C) {
			// 공유기의 수를 줄이자 => 간격 넓히기
			ans = mid;
			left = mid + 1;
		}
		else {
			// 공유기가 더 설치되어야한다. => 간격 좁히기
			right = mid - 1;
		}
	}
*/	
	return ans;
}
int main() 
{
	cin >> N >> C;
	int e;
	for (int n = 0; n < N; n++) {
		scanf("%d", &e); L.push_back(e);
	}
	sort(L.begin(), L.end());
	cout << solve();
	return 0;
}