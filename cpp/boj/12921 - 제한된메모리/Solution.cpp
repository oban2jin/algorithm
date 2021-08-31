#include <iostream>
#include <algorithm>
using namespace std;
int main(){
	int INF = 1000000007; 
	int X0 = 1000000000, A=1000,B=55;
	int XN[100];
	long long X=X0; 
	for(int i=0;i<100;i++){
		XN[i] = X;
		X = (X*A + B)%INF;
	}
	sort(XN,XN+100);
	for(int i=0;i<100;i++){
		cout << XN[i] << endl;
	}
	return 0;
}