#include<iostream>
#include<vector>
using namespace std;
int partion(std::vector<int> &a,int S,int E) {
	int R = rand()%(E-S+1) + S; swap(a[S],a[R]);
	int pivotV = a[S]; int i = S; 
	for(int j=S+1,j<=E;j++){
		if(a[j]<=pivotV){
			//i는 pivotV보다 작은 것이 보장된 마지막 index다.
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
  - Radix Sort : 극한으로 줄여서  O(2N) + O(65535) 정도로 풀어도 타임 아웃이다
  1) -10^9<=A[i]<=10^9 범위다. 10^9(1G)*4(int)*2(양수/음수) = 80G 메모리 사용가능이면 , 카운터 정렬 가능 => O(2*N)
  => 문제는 전체 리스트를 Sorting 할 필요가 없이, k번째만 숫자만 구하면 되는 상황이니
   - Quick Selection : 빠른 선택 알고리즘. 문제가 원하는 답은 리스트 전체를 Sorting하는 것이 아니라, 
   1) Pivot value를 기준으로 절반씩 비교해서, kth가 어느쪽에 있는지 줄여 간다.
     => O(n+n/2+n/4................) = 2N
	 => 머릿속 코드랑, 손으로 만들어 지는거랑 지랄같이 다르네.
	 => 조금 복잡한 코드( 대상 포인트를 양쪽에서 줄여오는 방식 : while 3중)도 타임아웃
	 => Pivot Value선정을 고정하지 않고(Randomize), 재배열처리도 심플하게 처리
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