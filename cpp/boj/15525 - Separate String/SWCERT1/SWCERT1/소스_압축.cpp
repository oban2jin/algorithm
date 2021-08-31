#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <cstring>
using namespace std;
typedef long long lld;
const int MOD  = 1000000021;
const int MOD1 = 1000000007;
const int MAXN = 1000001;
char S[MAXN];
int d[MAXN];
lld H[MAXN], P[MAXN];
int SZ;
struct Node
{
	bool leaf;
	int next[26];
	//cnt:자식노드 갯수, H:압축된 문자 Hashing 값, sz: 압축된 문자 길이
	//압축된 문자를 소비하고, 점프해야 하는 다음 노드를 어찌 표현하지?
	int cnt, h, sz;
	Node() {
		leaf = false;
		fill(next, next + 26, -1);
		cnt = 0, h = 0, sz = 0;
	}
};
vector<Node> trie;
void insert(int node, char* c) {
	if (*c == '\0') {
		trie[node].leaf = true; return;
	}
	int ch = *c - 'a';
	if (trie[node].next[ch] == -1) {
		trie.push_back(Node());
		trie[node].next[ch] = trie.size() - 1;
		++trie[node].cnt;
	}
	insert(trie[node].next[ch], c + 1);
}
int getH(int l, int r) {
	l++; r++;
	int t = r - l + 1;
	int rst = (H[r] - H[l - 1] * P[t]) % MOD;
	if (rst < 0)rst += MOD;
	return rst;
}
int go(int n) {
	if (n==SZ)return 1;
	int& rst = d[n]; if (rst != -1)return rst; 
	rst = 0; int node = 0;
	while (1) {
		if (n == SZ)break;
		int ch = S[n] - 'a';
		int nnode = trie[node].next[ch];
		if (nnode == -1)break;
		int L = trie[nnode].sz;
		if (SZ < n + L)break;
		if (trie[nnode].h == getH(n, n+L-1)) {
			if(trie[nnode].leaf)rst = (rst + go(n + L)) % MOD1;
			node = nnode; n += L;
		}
		else break;
	}
	return rst;
}
tuple<int,int,int> compress(int node,int sz,int h) {
	if (trie[node].cnt > 1 || trie[node].leaf) { return {node,sz,h}; }
	for (int i = 0; i < 26; i++) {
		if (trie[node].next[i] != -1) {
			return compress(trie[node].next[i], sz + 1, (1LL*h * 37 + i  + 1) % MOD);
		}
	}
	return {};
}
void dfs(int node) {
	for (int i = 0; i < 26; i++) {
		if (trie[node].next[i] != -1) {
			tuple<int,int,int> nnode = compress(trie[node].next[i], 1, i+1);
			int nn = get<0>(nnode); int nsz = get<1>(nnode); int nh = get<2>(nnode);
			trie[node].next[i] = nn; trie[nn].sz = nsz; trie[nn].h = nh;
			dfs(nn);
		}
	}
}
/*
 - Trie 압축도 쉽지 않다.  -> Hashing 함수 만들어 내는 부문이, 생소하다
*/
int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int N; cin >> N; trie.push_back(Node());
	for (int i = 0; i < N; i++) {
		cin >> S; insert(0, S);
	}
	dfs(0);
	cin >> S; SZ = strlen(S);
	// - Hashing Value 0은 제외하고 시작해야지
	H[0] = 0; P[0] = 1;
	for(int i=0;i<SZ;i++){
		//H[]계산 편의를 위해 H[1~]
		H[i+1] = (H[i] * 37 + S[i]-'a'+1) % MOD;
		P[i+1] = (P[i] * 37) % MOD;
	}
	fill(d, d + MAXN, -1);
	cout << go(0);
	return 0;
}