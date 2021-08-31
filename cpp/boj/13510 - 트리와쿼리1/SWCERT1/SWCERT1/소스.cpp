#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Eg
{
	int u, v, w;
};
const int MAXN = 100000 + 1;
//입력받은 노드 번호 기준
vector<Eg> adj[MAXN];
int P[MAXN], SZ[MAXN];
//새로 매핑한 노드 번호 기준
//NN : HLD 수행 시 부여한 새로운 넘버, 같은 체인내에, Depth가 깊어질수록 증가한다.
//EN : 엣지번호로 새로운 노드 넘버를 매핑함, 1번엣지 : u<-v EN[1]=v로 표현
int EN[MAXN];
int CN[MAXN], D[MAXN];
int NN[MAXN], W[MAXN], NP[MAXN];
int tree[MAXN * 4];
vector<int> chain[MAXN];
Eg E[MAXN];
int C;
void update(int i, int v, int node, int S, int E) {
	if (S == E) { tree[node] = v; return; }
	int MID = (S + E) >> 1;
	if (i <= MID) {
		update(i, v, node * 2, S, MID);
	}
	else {
		update(i, v, node * 2 + 1, MID + 1, E);
	}
	tree[node] = (tree[node * 2] < tree[node * 2 + 1]) ? tree[node * 2 + 1] : tree[node * 2];
}
int query(int l, int r, int node, int S, int E) {
	if (E < l || r < S)return 0;
	if (l <= S && E <= r)return tree[node];
	int MID = (S + E) >> 1;
	return max(query(l,r,node*2,S,MID),query(l,r,node*2+1,MID+1,E));
}
int dfs(int n, int p) {
	SZ[n] = 1; P[n] = p;
	for (int i = 0; i < adj[n].size(); i++) {
		int next = adj[n][i].v;
		if (next != p) SZ[n] += dfs(next, n);
	}
	return SZ[n];
}
void HLD(int n, int cn, int d, int w,int p) {
	//n:변환되기 전에 노드 번호, cn:체인번호(변환후) , d : 체인 - depth
	NN[n] = ++C; int nn = NN[n]; D[nn] = d; CN[nn] = cn; chain[cn].push_back(nn);
	//이전 노드 번호 기준 : EN[간선번호]=next.v로 설정
	EN[w] = nn; W[nn] = E[w].w; NP[nn] = p;
	Eg heavy = {-1,-1,-1};
	for (int i = 0; i < adj[n].size(); i++) {
		Eg next = adj[n][i];
		if ((next.v != P[n]) && (heavy.v == -1 || SZ[heavy.v] < SZ[next.v])) { heavy = next; }
	}
	if (heavy.v != -1) {
		HLD(heavy.v, cn, d, heavy.w, nn);
		for (int i = 0; i < adj[n].size(); i++) {
			Eg &next = adj[n][i]; 
			if ((next.v != P[n])&&(next.v != heavy.v)) {
				HLD(next.v, C+1, d + 1, next.w, nn);
			}
		}
	}
}
int solve(int a, int b) {
	int rst = 0;
	while(CN[a]!=CN[b]){
		if (D[a] < D[b]){
			int s = CN[b]; int e = b;
			rst = max(rst, query(s, e, 1, 1, MAXN));
			b = NP[CN[b]];
		}
		else {
			int s = CN[a]; int e = a;
			rst = max(rst, query(s, e, 1, 1, MAXN));
			a = NP[CN[a]];
		}
	}
	if (a > b)swap(a, b);
	if (a != b) {
		rst = max(rst, query(a + 1, b, 1, 1, MAXN));
	}
	return rst;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int N; cin >> N;
	for (int i = 1; i < N ; i++) {
		int u, v, w; cin >> u >> v >> w;
		E[i] = { u,v,w };
		adj[u].push_back({ v,v,i }); adj[v].push_back({ u,u,i });
	}
	fill(P, P + MAXN, 0);	fill(SZ, SZ + MAXN, 0);
	fill(CN, CN + MAXN, 0); fill(D, D + MAXN, 0);
	fill(NN, NN + MAXN, 0); fill(EN, EN + MAXN, 0);
	fill(W, W + MAXN, 0);	fill(NP, NP + MAXN, 0);
	fill(tree, tree + MAXN * 4, 0);
	dfs(1, 0);
	C = 0; HLD(1, 1, 0, 0, 1);
	for (int i = 0; i < MAXN; i++) {
		if (chain[i].size() != 0) {
			for (int j = 0; j < chain[i].size(); j++) {
				update(chain[i][j], W[chain[i][j]], 1, 1, MAXN);
			}
		}
	}
	int M; cin >> M; 
	for (int i = 0; i < M; i++) {
		int a, b, c; cin >> a >> b >> c;
		if (a == 1) {
			//b번간선 w->c로
			update(EN[b], c, 1, 1, MAXN);
		}
		else {
			//b<->c 구간의 최고 무거운 간선의 무게를 출력
			cout << solve(NN[b], NN[c]) << "\n";
		}
	}
}