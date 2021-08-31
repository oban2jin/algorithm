#include<iostream>
using namespace std;
typedef unsigned long long lld;
const int MOD = 1234567891;
char T[51];
int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
	int N; cin >> N; cin >> T;
	lld H = 0L;
	for(int i=N-1;0<=i;i--){
		H = (H*31%MOD + (T[i]-'a' + 1)%MOD)%MOD;
	}
	cout << H;
	return 0;
}