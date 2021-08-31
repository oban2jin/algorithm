#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 100000 + 1;
vector<int> adj[MAXN];
int P[MAXN],  SZ[MAXN], D[MAXN];
int CN[MAXN], CIX[MAXN];
vector<int> chain[MAXN];
int dfs(int n, int p) {
	//n를 루트로 하는 서브트리에 속한 노드 숫자
	SZ[n] = 1; P[n] = p;
	for (int i = 0; i < adj[n].size(); i++) {
		int next = adj[n][i];
		if (next != p) {
			SZ[n] += dfs(next, n);
		}
	}
	return SZ[n];
}
void HLD(int n, int cn, int d) {
	//n:현재노드, p:부모노드, 
    //cn:현재노드가 속한 체인번호(체인에서 가장 깊이가 낮은 노드 번호), 현재체인의 깊이
	//하위의 서브트르 사이즈를 기준으로 체인을 연결해 간다.

	CN[n] = cn; D[n] = d;
	chain[cn].push_back(n); CIX[n] = chain[cn].size();
	int heavy = -1; 
	for (int i = 0; i < adj[n].size(); i++) {
		int next = adj[n][i]; 	
		if ((next != P[n])&&(heavy == -1 || SZ[heavy] < SZ[next])) 
			heavy = next;
	}
	if (heavy != -1) {
		for (int i = 0; i < adj[n].size(); i++) {
			int next = adj[n][i];
			if (next != P[n]) {
				if (next == heavy) {
					HLD(next,cn,d);
				}
				else {
					HLD(next,next,d+1);
				}
			}
		}
	}
}
int LCA(int a, int b) {
	while (CN[a] != CN[b]) {
		if (D[a] < D[b]) {
			b = P[CN[b]];
		}
		else {
			a = P[CN[a]];
		}
	}
	//a와b는 같은 체인에 위치, 체인에서의 위치가 낮은 쪽이 LCA다
	return (CIX[a] < CIX[b]) ? a : b;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int N; cin >> N; 
	fill(P, P + MAXN, 0);
	fill(SZ, SZ + MAXN, 0);
	fill(D, D + MAXN, 0);
	for (int i = 0; i < N - 1; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b); adj[b].push_back(a);
	}
	dfs(1, 0); HLD(1, 1, 0);
	int M; cin >> M;
	for (int i = 0; i < M; i++){
		int a, b; cin >> a >> b;
		cout << LCA(a, b) << "\n";
	}
}