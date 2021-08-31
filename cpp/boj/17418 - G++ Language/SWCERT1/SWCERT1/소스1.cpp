#include <cassert>
#include <iostream>
using namespace std;
int N0 = 21;
int NA1 = 99;
void Zero(int a);					// a = 0
void Mov(int from, int to);			// to = from
void And(int a, int b, int c);		// c = a and b
void Or(int a, int b, int c);		// c = a or b
void Xor(int a, int b, int c);		// c = a xor b
void LShift(int a, int b, int c);	// c = a << b
void RShift(int a, int b, int c);	// c = a >> b
void Add(int a, int b, int c);		// c = a + b
void Sub(int a, int b, int c);		// c - a - b
void Not(int a, int b);				// b = ~a
void LNot(int a, int b);			// b = !a

int main() {
	int h, w;
	cin >> h >> w;

	cout << "INPUT 0\nINPUT 0\n";
	Zero(0);

	// M[0] = 결과
	// M[1~4] = a~d
	// M[5~20] = A0~A15
	for (int n = 0; n < h * w; ++n) {
		cout << "INPUT " << n + 5 << '\n';
	}
	cout << "INPUT 2\nINPUT 1\nINPUT 4\nINPUT 3\n";

	//상수 만들기. N0:0 ~ N16:16 , NA1 : 0xFFFFFFFF;

	// M[21~37] = 0~16
	LNot(N0, N0+1);
	Not(NA1, NA1);
	for (int i = 2; i <= 16; ++i) {
		Add(N0 + i - 1, N0+1, N0 + i);
	}

	// M[38~53] = 덧셈 여부(0x00000000 또는 0x11111111)
	// M[54] = 임시 메모리
	// M[55] = x좌표
	// M[56] = y좌표
	// M[57] = 임시 메모리
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			Mov(N0, 54);

			// a <= x
			Mov(N0 + x, 55);
			Sub(55, 1, 55);
			RShift(55, N0+11, 55);
			And(55, N0+1, 55); // MSB
			Or(54, 55, 54);

			// x <= c
			Mov(N0 + x, 55);
			Sub(3, 55, 55);
			RShift(55, N0+11, 55);
			And(55, N0+1, 55); // MSB
			Or(54, 55, 54);

			// b <= y
			Mov(N0 + y, 56);
			Sub(56, 2, 56);
			RShift(56, N0+11, 56);
			And(56, N0+1, 56); // MSB
			Or(54, 56, 54);

			// y <= d
			Mov(N0 + y, 56);
			Sub(4, 56, 56);
			RShift(56, N0+11, 56);
			And(56, N0+1, 56); // MSB
			Or(54, 56, 54);

			Zero(57);
			Not(57, 57);
			Add(57, 54, 57);
			Mov(57, 38 + y * w + x);
		}
	}

	for (int i = 0; i < h * w; ++i) {
		And(5 + i, 38 + i, 54);
		Add(0, 54, 0);
	}

	for (int i = 1; i <= 99; ++i) {
		if (i == 21) continue;
		Zero(i);
	}
}

void Zero(int a) {
	And(a, N0, a);
}
void Mov(int from, int to) {
	cout << "AND 2 " << NA1 << " " << from << " " << to << "\n";
}
void And(int a, int b, int c) {
	assert(a != b);
	cout << "AND 2 " << a << ' ' << b << ' ' << c << '\n';
}
void Or(int a, int b, int c) {
	assert(a != b);
	cout << "OR 2 " << a << ' ' << b << ' ' << c << '\n';
}
void Xor(int a, int b, int c) {
	assert(a != b);
	cout << "XOR 2 " << a << ' ' << b << ' ' << c << '\n';
}
void LShift(int a, int b, int c) {
	cout << "LSHIFT " << a << ' ' << b << ' ' << c << '\n';
}
void RShift(int a, int b, int c) {
	cout << "RSHIFT " << a << ' ' << b << ' ' << c << '\n';
}
void Add(int a, int b, int c) {
	int r1 = 61; int r2 = 62; int x1 = 63; int a1 = 64;
	Mov(a, r1);
	Mov(b, r2);
	for (int i = 0; i < 12; i++) {
		//X1 = R[103], A1 = [104]
		Xor(r1, r2, x1);
		And(r1, r2, a1);
		Mov(x1, r1);
		LShift(a1, N0 + 1, a1);
		Mov(a1, r2);
	}
	Mov(r1, c);
}
void Sub(int a, int b, int c) {
	Mov(b, 60);
	Not(60, 60);
	Add(60, N0 + 1, 60);
	Add(a, 60, c);
}
void Not(int a, int b) {
	cout << "BNOT " << a << ' ' << b << '\n';
}
void LNot(int a, int b) {
	cout << "NOT " << a << ' ' << b << '\n';
}