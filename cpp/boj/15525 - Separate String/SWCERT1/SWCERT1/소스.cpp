#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
const int MOD = 1000000007;
const int MAXN = 1000001;
int d[MAXN];
char S[MAXN]; int SZ;
struct  Node
{
	bool leaf;
	int next[26];
	Node() {
		leaf = false;
		fill(next, next + 26, -1);
	}
};
vector<Node> Trie;
void insert(char *c,int node) {
	if (*c == '\0') { Trie[node].leaf = true; return; }
	int ch = *c - 'a'; 
	if (Trie[node].next[ch] == -1) {
		Trie.push_back(Node()); Trie[node].next[ch] = Trie.size() - 1;
	}
	insert(c + 1, Trie[node].next[ch]);
}
int go(int n) {
	//기저사례를 정의
	if (n == SZ)return 1;
	int &rst = d[n]; if (rst != -1)return rst; 
	rst = 0; int node = 0;
	while (1) {
		if (n == SZ)break; //S의 끝까지 찾아 갔는디. 분리를 완성하지 못했다.
		int ch = S[n] - 'a';
		if (Trie[node].next[ch] == -1)break;
		node = Trie[node].next[ch]; 
		if (Trie[node].leaf) {
			rst = (rst + go(n + 1))%MOD;
		}
		++n;
	}
	return rst;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int N; cin >> N; 
	Trie.push_back(Node());
	fill(d, d + MAXN, -1);
	for (int i = 0; i < N; i++) {
		cin >> S; insert(S, 0);
	}
	cin >> S; SZ = strlen(S);
	cout << go(0);
	return 0;
}