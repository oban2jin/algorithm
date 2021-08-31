#include <iostream>
#include<cmath>
typedef long long ll;
using namespace std;
ll Ns[1000000 + 1];
ll Bs[1000 + 1];
int N, M, K;
int sq;
void init() {
	sq = sqrt(N);
	for (int i = 1; i <= N; i++) {
		//sqrt(N) ���� ��ŭ�� ���� �����, �ʱ� ���� �� ó��
		cin >> Ns[i];  Bs[i / sq] += Ns[i];
	}
}
void update(int i, ll v) {
	int bidx = i / sq; Bs[bidx] = 0;
	int s = bidx * sq; int e = s + sq;
	Ns[i] = v; for (int i = s; i < e; i++) {
		Bs[bidx] += Ns[i];
	}
}
ll query(int l, int r) {
	ll rst = 0L;
	//���������� �����̸鼭
	while (l%sq != 0 && l <= r) {
		rst += Ns[l++];
	}
	//�������� �����̸鼭
	while (r%sq != sq - 1 && l <= r) {
		rst += Ns[r--];
	}
	//����� ����
	while (l <= r) {
		rst += Bs[l / sq]; l += sq;
	}
	return rst;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> N >> M >> K; 
	init(); int a, b; ll c;
	for (int i = 0; i < M+K; i++) {
		cin >> a >> b >> c;
		if (a == 1) {
			update(b, c);
		}
		else {
			cout << query(b, c) << "\n";
		}
	}
}