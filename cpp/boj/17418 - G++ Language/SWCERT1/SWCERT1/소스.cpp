#include <iostream>
#include<cassert>
using namespace std;
const int N0 = 21;
const int NA1 = 99;
const int a=1, b=2, c=3, d=4;
int H, W;
void OR(int a, int b, int c);
void AND(int a, int b, int c);
void XOR(int a, int b, int c);
void ADD(int a, int b,int c);
void SUB(int a, int b,int c);
void MOVE(int a, int b);
void LSH(int a, int b, int n);
void RSH(int a, int b, int n);
void NOT(int a, int b);
void BNOT(int a, int b);
void BNOT(int a, int b) {
	//b = !a
	cout << "BNOT " << a << " " << b << "\n";
}
void NOT(int a, int b) {
	//b = ~a
	cout << "NOT " << a << " " << b << "\n";
}
void RSH(int a, int b, int n) {
	//b = a >> n;
	cout << "RSHIFT " << a << " " << n << " " << b << "\n";
}
void LSH(int a, int b, int n) {
	//b = a << n;
	cout << "LSHIFT " << a << " " << n << " " << b << "\n";
}
void OR(int a, int b, int c) {
	//c = a | b 
	assert(a != b);
	cout << "OR 2 " << a << " " << b << " " << c << "\n";
}
void AND(int a, int b, int c) {
	//c = a & b 
	assert(a != b);
	cout << "AND 2 " << a << " " << b << " " << c << "\n";
}
void XOR(int a, int b, int c) {
	//c = a ^ b
	assert(a != b);
	cout << "XOR 2 " << a << " " << b << " " << c << "\n";
}
void MOVE(int a, int b) {
	//b = a
	cout << "AND 2 " << NA1 << " " << a << " " << b << "\n";
}
void SUB(int a, int b,int c) {
	//R[c] = R[a] - R[b] =>  R[c] = R[a] + (-R[b])
	MOVE(b, 60);
	BNOT(60, 60);
	ADD(60, N0 + 1, 60);
	ADD(a, 60, c);
}
void ADD(int a, int b,int c) {
	// R[c] = R[a] + R[b];
	int r1 = 61; int r2 = 62; int x1 = 63; int a1 = 64;
	MOVE(a, r1);
	MOVE(b, r2);
	for (int i = 0; i < 12; i++) {
		XOR(r1, r2, x1);
		AND(r1, r2, a1);
		MOVE(x1, r1);
		LSH(a1, a1, N0 + 1);
		MOVE(a1, r2);
	}
	MOVE(r1, c);
}
void clear() {
	for (int i = 1; i < 100; i++) {
		if (i == N0) continue;
		AND(N0, i, i);
	}
}
void solve() {
	// a<=y<=c, b<=x<=d 
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			MOVE(N0 , 54);
			//0<=y-a
			MOVE(N0 + y, 55);
			SUB(55, a, 55);
			RSH(55, 55, N0 + 11);
			AND(55, N0 + 1, 55);
			OR(54, 55, 54);
			//0<=c-y
			MOVE(N0 + y, 55);
			SUB(c, 55, 55);
			RSH(55, 55, N0 + 11);
			AND(55, N0 + 1, 55);
			OR(54, 55, 54);
			//0<=x-b 
			MOVE(N0 + x, 56);
			SUB(56, b, 56);
			RSH(56, 56, N0 + 11);
			AND(56, N0 + 1, 56);
			OR(54, 56, 54);
			//0<=d-x
			MOVE(N0 + x, 56);
			SUB(d, 56, 56);
			RSH(56, 56, N0 + 11);
			AND(56, N0 + 1, 56);
			OR(54, 56, 54);

			MOVE(N0, 57);
			BNOT(57, 57);
			ADD(57, 54, 57);

			MOVE(57, 38+ W * y + x);
		}
	}

	for (int i = 0; i < H*W; i++) {
		AND(5 + i, 38 + i, 57);
		ADD(0, 57, 0);
	}
}
int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> H >> W;
	cout << "INPUT 0" << "\n"; 
	cout << "INPUT 0" <<  "\n";

	MOVE(N0, 0);
	for (int i = 0; i < H*W; i++) {
		cout << "INPUT " << (5 + i) << "\n";
	}
	cout << "INPUT " << a << "\n";
	cout << "INPUT " << b << "\n";
	cout << "INPUT " << c << "\n";
	cout << "INPUT " << d << "\n";

	//상수 만들기. N0:0 ~ N16:16 , NA1 : 0xFFFFFFFF, NA12 : 0xFFF
	NOT(N0, N0 + 1);
	BNOT(NA1, NA1);
	for (int i = 2; i <= 16; i++) {
		ADD(N0 + i - 1, N0 + 1, N0 + i);
	}
	solve();
	clear();
	return 0;
}