#include<iostream>
#include<vector>
using namespace std;
typedef long long lld;
const int MAXN = 300000;
int N, M, Q;
lld tree[MAXN + 1];
int P[MAXN + 1], lo[MAXN + 1], hi[MAXN + 1];
vector<int> Z[MAXN + 1], VT[MAXN + 1];
struct Qy
{
	int l, r, a;
}; Qy QyS[MAXN + 1];
void init() {
	for (int i = 1; i <= Q; i++)VT[i].clear();
	fill(tree, tree + MAXN + 1, 0);
}
void update(int i, int v) {
	while (i <= M) {
		tree[i] += v;
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
 1.PBS를 알고 있어도 문제 해결이 가능했을까 ?
 2.BIT Rage Update, Spot Query하는 방식을 알고있어야 하며
 3.계산의 중간에 long long계산이 터지는 부문이 존재한다.
*/
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> N >> M;
	for (int i = 1; i <= M; i++) {
		int z;
		cin >> z; Z[z].push_back(i);
	}
	for (int i = 1; i <= N; i++) {
		cin >> P[i];
	}
	cin >> Q;
	for (int i = 1; i <= Q; i++) {
		int l, r, a; cin >> l >> r >> a;
		QyS[i] = { l,r,a };
	}
	for (int i = 1; i <= N; i++) {
		lo[i] = 1; hi[i] = Q + 1;
	}
	bool flag = true;
	while (flag) {
		flag = false;
		init();
		for (int i = 1; i <= N; i++) {
			if (lo[i] < hi[i]) {
				flag = true;
				VT[(lo[i] + hi[i]) >> 1].push_back(i);
			}
		}
		for (int i = 1; i <= Q; i++) {
			Qy here = QyS[i];
			if (here.l <= here.r) {
				//R[l:r]에 +a, R[r+1,M] -a;
				update(here.l, here.a); update(here.r + 1, -here.a);
			}
			else {
				//R[1:r]애 +a, R[l:M] -a
				update(1, here.a);	update(here.r + 1, -here.a);	update(here.l, here.a);
			}
			while (VT[i].size()) {
				//idx는 이번에 비교처리할 나라(N) 번호
				int idx = VT[i].back(); VT[i].pop_back();
				lld sum = 0;
				for (int z = 0; z < Z[idx].size(); z++) {
					sum += search(Z[idx][z]);
					if (P[idx] <= sum)break;
				}
				if (P[idx] <= sum) {
					hi[idx] = i;
				}
				else {
					lo[idx] = i + 1;
				}
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		if (lo[i] == Q + 1) {
			cout << "NIE\n";
		}
		else {
			cout << lo[i] << "\n";
		}
	}
	return 0;
}