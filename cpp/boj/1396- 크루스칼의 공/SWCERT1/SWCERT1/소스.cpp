#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 100000;
int N, M, Q;
struct Qy {
	int l, r;
}; vector<Qy> QyS;
struct Eg
{
	int a, b, c;
	bool operator < (const Eg &o) {
		return c < o.c;
	}
}; vector<Eg> EgS;
vector<int>G[MAXN + 1]; vector<int> VT[MAXN + 1];
int P[MAXN + 1], SZ[MAXN + 1], lo[MAXN + 1], hi[MAXN + 1], ANSZ[MAXN + 1], ANSW[MAXN + 1];
void init() {
	for (int i = 1; i <= N; i++) {
		P[i] = i; SZ[i] = 1;
	}
	for (int i = 0; i < M; i++) { VT[i].clear(); }
}
int find(int a) {
	if (a == P[a])return a;
	return P[a] = find(P[a]);
}
void merge(int a, int b) {
	a = find(a); b = find(b);
	if (a==b)return;
	P[b] = a; SZ[a] += SZ[b];
}
/*
  PBS(Parallel Binary Search) ���� ������ ���� �ϸ鼭 �ذ��� ����
  �� ���� ���� Ž���ΰ� ?  �ټ��� ���Ǹ� �ذ��ϱ� ���� 
  ������ ����/������ �̺�Ž���� �ݺ������� �����ϴ� ���. 
  ���� ������ �̺�Ž���� ����� ��� ����(����) �ذῡ ����Ѵ�.
*/
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b, c; cin >> a >> b >> c;
		EgS.push_back({ a,b,c });
		G[a].push_back(b); G[b].push_back(a);
	}
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		int a, b; cin >> a >> b;
		QyS.push_back({ a,b });
		//hi[i] = M���� ����. �Ѽ� ���
		lo[i] = 0; hi[i] = M;
	}
	sort(EgS.begin(), EgS.end());

	bool flag = true;
	while (flag) {
		flag = false;
		init();
		for (int i = 0; i < Q; i++) {
			if (lo[i] < hi[i]) {
				//���� QyS[i]�� ���ذ� ���´�
				VT[(lo[i] + hi[i]) >> 1].push_back(i);
			}
		}
		for (int i = 0; i < EgS.size(); i++) {
			int a = EgS[i].a; int b = EgS[i].b; int c = EgS[i].c;
			merge(a, b);
			while (VT[i].size()) {
				flag = true;
				int idx = VT[i].back(); VT[i].pop_back();
				Qy qy = QyS[idx]; int l = qy.l; int r = qy.r;
				if (find(l) == find(r)) {
					hi[idx] = i;
					//�̶� ���ϴ� ���� ������Ʈ �Ѵ�.
					ANSZ[idx] = SZ[find(l)]; ANSW[idx] = EgS[i].c;
				}
				else {
					lo[idx] = i + 1;
				}
			}
		}
	};

	for (int i = 0; i < Q; i++) {
		Qy qy = QyS[i]; int l = qy.l; int r = qy.r;
		if (find(l) != find(r)) {
			//���� R[l:r]�� ���� �Ұ������� Ȯ���ϰ�, 
			cout << "-1\n";
		}
		else {
			//���� ����Ѵ�.
			cout << ANSW[i] << " " << ANSZ[i] << "\n";
		}
	}
}