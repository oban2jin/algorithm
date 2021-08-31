#include <iostream>
#include <algorithm>
using namespace std;
typedef long long lld;
struct Nd
{
	//i -> 입력 순서, j -> v 기준 내림차순 순서
	int i, j, v;
};
const int MAXN = 1 << 19;
int tree[MAXN * 2];
int N;
const int MAX = 500000;
Nd I[MAX];
bool cmp(const Nd &a, const Nd &b) {
	return a.v < b.v;
}
bool cmp2(const Nd &a,const Nd &b) {
	return a.i < b.i;
}
void update(int i, int v,int node, int S,int E) {
	if (S == E) { tree[node] = tree[node] + v; return; }
	int Mid = (S + E) >> 1;
	if (i <= Mid) update(i,v,node*2,S,Mid);
	else update(i,v,node*2+1,Mid+1,E);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}
int query(int l, int r, int node, int S,int E) {
	if (r < S || E < l)return 0;
	if (l <= S && E <= r)return tree[node];
	int Mid = (S + E) >> 1;
	return query(l, r, node * 2, S, Mid) + query(l, r, node * 2 + 1, Mid + 1, E);
}
int main() {
	cin >> N; for (int n = 0; n < N; n++) { 
		int v; scanf("%d", &v); I[n] = { n,0,v };
 	}
	sort(I, I + N, cmp);
	int j = 1;
	for (int n = 0; n < N; n++) {
		if (n == 0) { I[n].j = j; continue; }
		if (I[n - 1].v == I[n].v)I[n].j = j;
		else I[n].j = ++j;
	}
	sort(I, I + N, cmp2);
	lld ANS = 0;
	for (int n = 0; n < N; n++) {
		Nd here = I[n]; update(here.j, 1, 1, 1, MAXN);
		ANS = ANS + query(here.j + 1, N, 1, 1, MAXN);
	}
	cout << ANS;
}