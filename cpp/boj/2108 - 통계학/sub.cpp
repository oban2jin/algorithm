#include <iostream>
using namespace std;
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	int N; cin >> N;  int SM=0;
	int Ns[500001] ={0,}; int Es[8001] = {0,}; int idx; int MXEs = 0;
	for(int n=0;n<N;n++){
		cin >> Ns[n];  SM += Ns[n];  idx = Ns[n]+4000; ++Es[idx]; 
		if(MXEs<Es[idx])Es[idx];
	}
	return 0;
}