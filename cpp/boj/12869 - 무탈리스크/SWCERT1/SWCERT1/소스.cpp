#include <iostream>
#include <algorithm>
using namespace std;
int D[61][61][61];
int dp(int a, int b, int c) {
	if (a <= 0 && b <= 0 && c <= 0)return 0;

	a = a <= 0 ? 0 : a; b = b <= 0 ? 0 : b; c = c <= 0 ? 0 : c;
	if (D[a][b][c] != -1) return D[a][b][c];

	int &rst = D[a][b][c];	rst = 987654321;

	rst = min(rst,min(dp(a - 9, b - 3, c - 1), dp(a - 9, b - 1, c - 3))+1);
	rst = min(rst,min(dp(a - 3, b - 9, c - 1), dp(a - 3, b - 1, c - 9))+1);
	rst = min(rst,min(dp(a - 1, b - 9, c - 3), dp(a - 1, b - 3, c - 9))+1);
	
	return rst;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	for (int i = 0; i < 61; i++) for (int j = 0; j < 61; j++) for (int k = 0; k < 61; k++)D[i][j][k] = -1;
	int N; cin >> N;
	int Ns[] = { 0,0,0 }; 
	for (int i = 0; i < N; i++) {
		cin >> Ns[i];
	}
	cout << dp(Ns[0], Ns[1], Ns[2]);
	return 0;
}