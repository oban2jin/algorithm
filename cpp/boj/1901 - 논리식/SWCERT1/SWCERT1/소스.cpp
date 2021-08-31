#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
char EX[501];
char SO[100][20]; bool ST[100][2];
char DO[100][20]; bool DT[100][2][2];
char V[100][100]; bool VT[100];
int S, D, Vcnt;
struct TK {
	int t; // 0:variable, 1:Singled OP, 2:Double OP, 3:계산결과, 4:'('
	int ith; //몇번째인지
	int sz; //토큰문자의 길이 사이즈
	int v; //계산 결과
};
TK getToken(int p) {
	char T[100];
	int t=-1, ith=-1, sz=0, v=-1;
	if ('a' <= EX[p] && EX[p] <= 'z') {
		//변수 처리
		t = 0;
		while (EX[p+sz] != ' ' && 'a' <= EX[p+sz] && EX[p+sz] <= 'z') {
			T[sz] = EX[p+sz]; ++sz;
		}
		T[sz] = '\0';
		for (int i = 0; i < Vcnt; i++) {
			if (strcmp(T, V[i]) == 0) { v = VT[i]; ith = i; break; }
		}
	}
	else if ('A' <= EX[p] && EX[p] <= 'Z') {
		//연산자처리
		for (int i = 0; i < S; i++) {
			if (strncmp(SO[i], &EX[p], strlen(SO[i]))==0) {
				t = 1; ith = i; sz = strlen(SO[i]);  break;
			}
		}
		for (int i = 0; i < D; i++) {
			if (strncmp(DO[i], &EX[p], strlen(DO[i]))==0) {
				t = 2; ith = i; sz = strlen(DO[i]);  break;
			}
		}
	}
	else if ('(' <= EX[p]) {
		t = 4; ++sz;
	}
	return { t,ith,sz,v };
}
int cal() {
	int p = 0; int rst = -1;
	vector<TK> Q;
	while (EX[p] != '\0') {
		char here = EX[p]; 
		 if (here == ')') {
			int cnt = 0; TK cur_TK;
			int op = -1; int or1 = -1; int or2 = -1; int op_type = -1;
			while (1) {
				cur_TK = Q.back(); Q.pop_back(); ++cnt;
				if (cur_TK.t == 0 || cur_TK.t == 3) {
					if (cnt == 1)or1 = cur_TK.v;
					else or2 = cur_TK.v;
				}
				else if (cur_TK.t == 1||cur_TK.t==2) {
					op_type = (cur_TK.t == 1) ? 1 : 2;
					op = cur_TK.ith;
				}
				else if (cur_TK.t == 4){
					if (op_type == 1) {
						//싱글 오퍼레이션
						if (or1 == -1) Q.push_back({ 3,-1,-1, -1 });
						else Q.push_back({ 3,-1,-1, ST[op][or1] });
					}
					else {
						//듀얼 오퍼레이션 , 왼쪽 오퍼런드:or2, 오른쪽 오프런드 : or1
						if (or1 != -1 && or2 != -1) {
							Q.push_back({ 3,-1,-1, DT[op][or2][or1] });
						}
						else {
							if (or1 == -1 && or2 !=- 1) {
								//오른쪽 모르고, 왼쪽을 안다.
								if (DT[op][or2][0] == DT[op][or2][1]) {
									Q.push_back({ 3,-1,-1, DT[op][or2][0] });
								}
								else {
									Q.push_back({ 3,-1,-1, -1 });
								}
							}
							else if(or1 !=-1 && or2 == -1){
								//왼쪽을 모르고 , 오른쪽을 안다.
								if (DT[op][0][or1] == DT[op][1][or1]) {
									Q.push_back({ 3,-1,-1, DT[op][0][or1] });
								}
								else {
									Q.push_back({ 3,-1,-1, -1 });
								}
							}
							else {
								Q.push_back({ 3,-1,-1, -1 });
							}
						}
					}
					break;
				}
			}
			++p;
		}
		else if(here != ' '){
			TK rst = getToken(p);
			Q.push_back(rst); p += rst.sz;
		}
		else {
			++p;
		}
	}
	return Q.front().v;
}
int main() {
	int T = 1;
	char tmp[500]; S = 0; D = 0;
	while (1) {
		cin >> S >> D; cin.getline(tmp, 500); Vcnt = 0;
		if (S == -1 && D == -1) break;
		for (int s = 0; s < S; s++) {
			cin.getline(SO[s],100);
			for (int i = 0; i < 2; i++) { 
				cin >> tmp; ST[s][i] = strcmp(tmp, "false") == 0 ? 0 : 1;
			}
			cin.getline(tmp, 500);
		}
		for (int d = 0; d < D; d++) {
			cin.getline(DO[d], 100);
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					cin >> tmp; DT[d][i][j] = strcmp(tmp, "false") == 0 ? 0 : 1;
				}
			}
			cin.getline(tmp, 500);
		}
		cin.getline(EX, 500);
		while (1) {
			cin >> tmp; 
			if (tmp[0] == '*') break;
			strcpy(V[Vcnt], tmp); cin >> tmp; VT[Vcnt] = strcmp(tmp, "false") == 0 ? 0 : 1;
			++Vcnt;
		}
		int ANS = cal(); char *RST; 
		if (ANS == -1) { 
			RST = "unknown"; 
		}
		else if (ANS == 0) {
			RST = "false";
		}
		else {
			RST = "true";
		}
		cout << "Case "<< T++ <<": " << RST << "\n";
	}
	return 0;
}