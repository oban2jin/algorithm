#include <iostream>
using namespace std;
const int MXN = 1 << 19;
int tree[MXN *2], lazy[MXN * 2];
int N, M;
void propagation(int node, int S, int E) {
	if(lazy[node]==0)return;
	int MID = (S + E) >> 1;
	tree[node * 2] = tree[node * 2] ^ (lazy[node]*((MID-S+1)%2));
	lazy[node * 2] = lazy[node * 2] ^ lazy[node];
	tree[node * 2 + 1] = tree[node * 2 + 1] ^ (lazy[node]*((E-MID)%2));
	lazy[node * 2 + 1] = lazy[node * 2 + 1] ^ lazy[node];
	lazy[node] = 0;
}
void update(int l,int r, int v, int node, int S, int E) {
	if (r < S || E < l)return;
	if (l <= S && E <= r) {
		tree[node] = tree[node] ^ (v*((E-S+1)%2));
		lazy[node] = lazy[node] ^ v;
		return;
	}
	propagation(node, S, E);
	int MID = (S + E) >> 1;
	update(l, r, v, node * 2, S, MID); update(l, r, v, node * 2 + 1, MID + 1, E);
	tree[node] = tree[node * 2] ^ tree[node * 2 + 1];
}
int query(int l, int r, int node, int S, int E) {
	if (r < S || E < l)return 0;
	if(l <= S && E <= r)return tree[node];
	propagation(node, S, E);
	int MID = (S + E) >> 1;
	return query(l, r, node * 2, S, MID) ^ query(l, r, node * 2 + 1, MID + 1, E);
}
/*
 1. tree[node] ^= lazy[node]가 기존의 변수에 값을 변경하는 것이 아니라, 계속 새로운 변수를 생성하는 듯 
   - 메모리 부족 오류 발생 
 2. 결국 문제 해결은 논리적으로 모두 정리 되어 있지 않으면, 코드를 만들면서 요행으로 해결되는 문제는 없다. 
   - XOR 항등원 처리, 배분법칙이 적용 되지 않는 부문 처리, Lazy Propagation 흐름처리 부문
 3. BOJ 99th 해결 문제임.
*/
int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> N; 
	for (int i = 0; i < N; i++) {
		int A; cin >> A; update(i, i, A,1,0,N);
	}
	cin >> M;
	for (int i = 0; i < M; i++) {
		int q, a, b, c; cin >> q;
		if (q == 1) {
			cin >> a >> b >> c;
			update(a, b, c,1,0,N);
		}
		else {
			cin >> a >> b;
			cout << query(a, b,1,0,N) << "\n";
		}
	}

	return 0;
}