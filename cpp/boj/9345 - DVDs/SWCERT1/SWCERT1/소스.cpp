#include <iostream>
using namespace std;
typedef long long lld;
const int MAXN = 1 << 17;
lld tree[MAXN * 2];
lld I[100000];
int T, N, K;
lld query(int l, int r) {
	lld rst = 0;
	int S = l + MAXN; int E = r + MAXN;
	while (S <= E) {
		if (S % 2 == 1) { rst = rst + tree[S++]; }
		if (E % 2 == 0) { rst = rst + tree[E--]; }
		S = S >> 1; E = E >> 1;
	}
	return rst;
}
void update(int i, int v) {
	int a = i + MAXN; tree[a] = v;
	while (a = a >> 1) {
		tree[a] = tree[2 * a] + tree[2 * a + 1];
	}
}
void init() {
	for (int n = 0; n < MAXN * 2; n++)tree[n] = 0;
	for (int n = 0; n < N; n++)update(n, n);
}
int main(){
	freopen("D:/workspacecpp/boj/9345 - DVDs/sample.txt", "r", stdin);
	for (int n = 0; n < 100000; n++) {
		if (n == 0)continue;
		I[n] = I[n - 1] + n;
	}
	cin >> T; for (int t = 0; t < T; t++) {
		cin >> N >> K; init();
		for (int k = 0; k < K; k++) {
			int a, b, c; scanf("%d %d %d", &a, &b, &c);
			if(a==0){
				//tree[MAXN+a]에 저장된 값을 구하고,  변경될  숫자와 차이만큼 udpate한다.
				int bv = query(b, b); int cv = query(c, c);
				update(b, cv);  update(c, bv);
			}
			else {
				lld ANS = query(b, c); lld bv, cv;
				b == 0? bv = 0: bv = I[b - 1];
				cv = I[c];
				if (ANS == (cv-bv))printf("YES\n");
				else printf("NO\n");
			}
		}
	}
	return 0;
}