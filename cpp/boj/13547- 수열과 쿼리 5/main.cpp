long long sum(std::vector<int> &a){
	long long rst = 0L;
	for(int i=0;i<a.size();i++){
		rst += a[i];
	}
	return rst;
}