#include <iostream>
#include <vector>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
struct Ed
{
	int s, e, l;
};
bool operator < (Ed const &a,Ed const &b) {
	return a.l > b.l;
}
vector<int> Es;
vector<Ed> Q;
int N, M, L;
bool dec(int mid) {
	int CNT = 0; bool rst = true;
	for (int i = 0; i < Q.size(); i++) {
		Ed here = Q[i]; CNT += (int)(ceil(here.l / (double)mid)-1);
		if (M < CNT) { rst = false; break; }
	}
	return rst;
}
int solve() {
	int l = 1; int r = Q[0].l; int m;
	while (l < r) {
		m = (l + r) >> 1;
		if (dec(m)) {
			r = m;
		}
		else {
			l = m + 1;
		}
	}
	return l;
}
/*
 Parametic Search : 정답의 구간, 도출 방식을 알고 있을 때, 조건에 맞는 최적/최선의 답을 탐색(이분탐색)을 통해서 결정한다.
 1.처음에는 길이가 제일 긴 구간은 선택해서, 절반으로 쪼개는 탐욕 알고리즘으로 해결하려 했으나, 
   새로 추가될 휴계소의 갯수(긴 구간 절단점)의 갯수에 따라 달라짐
 2.bool decision(구간의길이) : '구간의길이'를 최대크기로 전체 길이,절단이 가능하냐의 판단 문제로 변경하여, 
   구간의 길이를 이분탐색해 가면서 해결
 3.C++ priority_queue<struct>는 구조체 선언 외부에  bool operator <(struct const &a, struct const &b){} 형태로, 
   비교 연산자 overridding을 해줘야 한다.  
 */
int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> N >> M >> L;
	for (int i = 0; i < N; i++) {
		int a; cin >> a; Es.push_back(a);
	}
	sort(Es.begin(), Es.end());
	for (int i = 0; i < Es.size(); i++) {
		Ed here = { 0,0,0 };
		if (i == 0) { here.s = 0; }
		else { here.s = Es[i - 1]; }
		here.e = Es[i]; here.l = here.e - here.s;
		Q.push_back(here);
	}
	Q.push_back({Es[N-1],L,L-Es[N-1]});
	sort(Q.begin(), Q.end());
	cout << solve();
	return 0;
}