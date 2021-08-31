#include<iostream>
#include<vector>
using namespace std;
int partion(std::vector<int> &a,int S,int E) {
	int R = rand()%(E-S+1) + S; swap(a[S],a[R]);
	int pivotV = a[S]; int i = S; 
	for(int j=S+1,j<=E;j++){
		if(a[j]<=pivotV){
			//i�� pivotV���� ���� ���� ����� ������ index��.
			++i; swap(a[i],a[j]);
		}
	}
	swap(a[S],a[i]);
}
int quickselect(std::vector<int> &a,int S,int E,int k) {
	int nth = partion(a, S, E);
	if (nth == k)return a[nth];
	if (nth < k) {
		return quickselect(a, S, nth-1, k);
	}
	else {
		return quickselect(a, nth+1, E, k);
	}
}
int kth(std::vector<int> &a, int k) {
	int ans = quickselect(a, 0, a.size()-1, --k);
	return ans;
}
/*
  - Radix Sort : �������� �ٿ���  O(2N) + O(65535) ������ Ǯ� Ÿ�� �ƿ��̴�
  1) -10^9<=A[i]<=10^9 ������. 10^9(1G)*4(int)*2(���/����) = 80G �޸� ��밡���̸� , ī���� ���� ���� => O(2*N)
  => ������ ��ü ����Ʈ�� Sorting �� �ʿ䰡 ����, k��°�� ���ڸ� ���ϸ� �Ǵ� ��Ȳ�̴�
   - Quick Selection : ���� ���� �˰���. ������ ���ϴ� ���� ����Ʈ ��ü�� Sorting�ϴ� ���� �ƴ϶�, 
   1) Pivot value�� �������� ���ݾ� ���ؼ�, kth�� ����ʿ� �ִ��� �ٿ� ����.
     => O(n+n/2+n/4................) = 2N
	 => �Ӹ��� �ڵ��, ������ ����� ���°Ŷ� �������� �ٸ���.
	 => ���� ������ �ڵ�( ��� ����Ʈ�� ���ʿ��� �ٿ����� ��� : while 3��)�� Ÿ�Ӿƿ�
	 => Pivot Value������ �������� �ʰ�(Randomize), ��迭ó���� �����ϰ� ó��
*/
int main() {
	std::vector<int> A; 
	A.push_back(1); A.push_back(2); A.push_back(3); A.push_back(4); A.push_back(5);
	A.push_back(6); A.push_back(7); A.push_back(8); A.push_back(9); A.push_back(10);
	A.push_back(20); A.push_back(19); A.push_back(18); A.push_back(17); A.push_back(16);
	A.push_back(15); A.push_back(14); A.push_back(13); A.push_back(12); A.push_back(-11);
	std::cout << kth(A, 11);
	return 0;
}