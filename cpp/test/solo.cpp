#include <iostream>
#include <cstdio>

using namespace std;

int main(){
	int sum = 0;
	for(int n=0;n<10;n++){
		//sum = sum + n;
		sum += n;
		printf("sum=[%d]\n",sum);
	}	
	return 0;
}
