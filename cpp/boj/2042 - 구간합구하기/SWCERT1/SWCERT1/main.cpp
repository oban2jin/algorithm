#include <iostream>
using namespace std;
typedef long long lld;
const int MAXN = 1000000;
lld C[MAXN + 1];
lld tree[MAXN + 1];
int N, M, K;
void update(int i, lld v) {
	lld diff = v - C[i]; C[i] = v;
	while (i <= N) {
		tree[i] += diff;
		i += (i&-i);
	}
}
lld search(int i) {
	lld sum = 0;
	while (i) {
		sum += tree[i];
		i -= (i&-i);
	}
	return sum;
}
/*
 Segment Tree : 1180ms 소요
 Penwick Tree(BIT) : 152 ms 소요  
 152/1180 = 0.12xxx 
 구간의 합은 Penwick Tree(BIT)로 
*/
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> N >> M >> K; 
	fill(C, C + MAXN, 0);
	for (int i = 1; i <= N; i++) {
		lld n; cin >> n; update(i, n);
	}
	for (int i = 0; i < M + K; i++) {
		int a, b, c; cin >> a >> b >> c;
		if (a == 1) {
			update(b, c);
		}
		else {
			cout << search(c) - search(b - 1) << "\n";
		}
	}
	return 0;
}