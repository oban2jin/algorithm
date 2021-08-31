#include <iostream>
#include <algorithm>
using namespace std;
char S[2001];
int D[10][6];
char *cD[10];
int *R1, *R2, *R3;
int *K;

void init() {
	cD[0] = "ZERO"; cD[1] = "ONE"; cD[2] = "TWO"; cD[3] = "THREE"; cD[4] = "FOUR";
	cD[5] = "FIVE"; cD[6] = "SIX"; cD[7] = "SEVEN"; cD[8] = "EIGHT"; cD[9] = "NINE";
	for (int i = 0; i < 10; i++) {
		int j = 0;
		while (cD[i][j] != '\0') {
			D[i][j + 1] = cD[i][j] - 'A'; ++j;
		}
		D[i][0] = j;
	}
	R1 = new int[5] { 0, 2, 4, 6, 8 }; R2 = new int[4] {1, 3, 5, 7}; R3 = new int[1] {9};
	K = new int[10] {'Z'-'A','O'-'A','W'-'A','H'-'A','U'-'A','F'-'A','X'-'A','S'-'A','G'-'A','I'-'A'};
}
int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	init();
	int T; cin >> T;
	for (int t = 1; t <= T; t++) {
		int ANS[10]; int iD[26]; 
		fill(ANS, ANS + 10, 0); fill(iD, iD + 26, 0);
		cin >> S; int i = 0;
		while (S[i] != '\0') {
			char c = S[i] - 'A'; ++iD[c]; ++i;
		}
		for (int idx = 0; idx < 5; idx++) {
			char c = R1[idx]; int cnt = iD[K[c]];
			if (cnt != 0) {
				ANS[c] += cnt; 
				for (int i = 1; i <= D[c][0]; i++) {
					char cur_char = D[c][i]; iD[cur_char] -= cnt;
				}
			}
		}
		for (int idx = 0; idx < 4; idx++) {
			char c = R2[idx]; int cnt = iD[K[c]];
			if (cnt != 0) {
				ANS[c] += cnt;
				for (int i = 1; i <= D[c][0]; i++) {
					char cur_char = D[c][i]; iD[cur_char] -= cnt;
				}
			}
		}
		for (int idx = 0; idx < 1; idx++) {
			char c = R3[idx]; int cnt = iD[K[c]];
			if (cnt != 0) {
				ANS[c] += cnt;
				for (int i = 1; i <= D[c][0]; i++) {
					char cur_char = D[c][i]; iD[cur_char] -= cnt;
				}
			}
		}
		cout << "Case #" << t << ": ";
		for (int d = 0; d < 10; d++) {
			if (ANS[d] != 0) {
				for (int cc = 0; cc < ANS[d]; cc++) {
					cout << d;
				}
			}
		}
		cout << "\n";
	}
	return 0;
}