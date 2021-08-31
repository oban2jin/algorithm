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
			//������ �� ��ġ�Ǿ�� �� => ������ ���̿��Ѵ�.
			h = m - 1;
		}
		else {
			//������ ��ġ ���� �ٿ��� �� => ������ �ÿ��� �Ѵ�.
			if(ans < m)ans = m;
			l = m + 1;
		}
	}
/*
	int left = 1; // ������ �ּ� �Ÿ�
	int right = L[N - 1] - L[0]; // ������ �ִ� �Ÿ�
	int d = 0;
	int ans = 0;

	while (left <= right) {
		int mid = (left + right) / 2; // ����
		int start = L[0];
		int cnt = 1;

		// ����(d) �� �������� ������ ��ġ
		for (int i = 1; i < N; i++) {
			d = L[i] - start;
			if (mid <= d) {
				++cnt;
				start = L[i];
			}
		}

		if (cnt >= C) {
			// �������� ���� ������ => ���� ������
			ans = mid;
			left = mid + 1;
		}
		else {
			// �����Ⱑ �� ��ġ�Ǿ���Ѵ�. => ���� ������
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