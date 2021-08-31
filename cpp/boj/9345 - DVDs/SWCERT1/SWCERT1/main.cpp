#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100001;

struct node {
	int Max, Min;
};

int n, k;
node tree[MAXN * 4];
int arr[MAXN];

node init(int index, int start, int end) {
	if (start == end) {
		tree[index].Max = tree[index].Min = arr[start] = start;
		return tree[index];
	}
	else {
		int mid = (start + end) / 2;
		node y = init(index * 2 + 1, start, mid);
		node x = init(index * 2 + 2, mid + 1, end);
		tree[index].Max = max(y.Max, x.Max);
		tree[index].Min = min(y.Min, x.Min);
		return tree[index];
	}
}

bool query(int index, int left, int right, int start, int end) {
	if (left > end || right < start)
		return true;
	if (left <= start && end <= right)
		return left <= tree[index].Min && tree[index].Max <= right;
	else {
		int mid = (start + end) / 2;
		return query(index * 2 + 1, left, right, start, mid) && query(index * 2 + 2, left, right, mid + 1, end);
	}
}

node update(int index, int target, int value, int start, int end) {
	if (target < start || target > end)
		return tree[index];
	tree[index].Max = max(tree[index].Max, value);
	tree[index].Min = min(tree[index].Min, value);
	if (start == end) {
		arr[target] = tree[index].Max = tree[index].Min = value;
		return tree[index];
	}
	else {
		int mid = (start + end) / 2;
		node y = update(index * 2 + 1, target, value, start, mid);
		node x = update(index * 2 + 2, target, value, mid + 1, end);
		tree[index].Max = max(y.Max, x.Max);
		tree[index].Min = min(y.Min, x.Min);
		return tree[index];
	}
}


int main() {
	freopen("D:/workspacecpp/boj/9345 - DVDs/sample.txt", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	while (t--) {
		cin >> n >> k;
		init(0, 0, n - 1);
		int q, a, b;
		while (k--) {
			cin >> q >> a >> b;
			if (q == 0) { // ¹Ù²ãÄ¡±â
				int p = arr[a];
				update(0, a, arr[b], 0, n - 1);
				update(0, b, p, 0, n - 1);
			}
			else {
				cout << (query(0, a, b, 0, n - 1) ? "YES\n" : "NO\n");
			}
		}
	}
	return 0;
}