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
  PBS(Parallel Binary Search) 연습 문제로 공부 하면서 해결한 문제
  왜 병렬 이진 탐색인가 ?  다수의 질의를 해결하기 위해 
  동일한 조건/구간의 이분탐색을 반복적으로 수행하는 경우. 
  현재 수행한 이분탐색의 결과를 모든 질문(쿼리) 해결에 사용한다.
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
		//hi[i] = M으로 설정. 한수 배움
		lo[i] = 0; hi[i] = M;
	}
	sort(EgS.begin(), EgS.end());

	bool flag = true;
	while (flag) {
		flag = false;
		init();
		for (int i = 0; i < Q; i++) {
			if (lo[i] < hi[i]) {
				//아직 QyS[i]는 미해결 상태다
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
					//이때 구하는 답을 업데이트 한다.
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
			//도달 R[l:r]이 연결 불가능인지 확인하고, 
			cout << "-1\n";
		}
		else {
			//답을 출력한다.
			cout << ANSW[i] << " " << ANSZ[i] << "\n";
		}
	}
}