#include<bits/stdc++.h> 
using namespace std; 
struct Query 
{ 
	int l, r, x, idx; 
}; 
struct ArrayElement 
{ 
	int val, idx; 
}; 
bool cmp1(Query q1, Query q2) 
{ 
	return q1.x < q2.x; 
} 
bool cmp2(ArrayElement x, ArrayElement y) 
{ 
	return x.val < y.val; 
} 
void update(int bit[], int idx, int val, int n) 
{ 
	for (; idx<=n; idx +=idx&-idx) 
		bit[idx] += val; 
} 
int query(int bit[], int idx, int n) 
{ 
	int sum = 0; 
	for (; idx > 0; idx -= idx&-idx) 
		sum += bit[idx]; 
	return sum; 
} 

void answerQueries(int n, Query queries[], int q, 
							ArrayElement arr[]) 
{ 
	int bit[n+1]; 
	memset(bit, 0, sizeof(bit)); 

	sort(arr, arr+n, cmp2); 

	sort(queries, queries+q, cmp1); 

	int curr = 0; 

	int ans[q]; 

	for (int i=0; i<q; i++) 
	{ 
		while (arr[curr].val <= queries[i].x && curr<n) 
		{ 
			update(bit, arr[curr].idx+1, 1, n); 
			curr++; 
		} 

		ans[queries[i].idx] = query(bit, queries[i].r+1, n) - 
							query(bit, queries[i].l, n); 
	} 
	for (int i=0 ; i<q; i++) 
		cout << ans[i] << endl; 
} 

int main() 
{ 
	int n = 4; 

	ArrayElement arr[n]; 
	arr[0].val = 2; 
	arr[0].idx = 0; 
	arr[1].val = 3; 
	arr[1].idx = 1; 
	arr[2].val = 4; 
	arr[2].idx = 2; 
	arr[3].val = 5; 
	arr[3].idx = 3; 

	int q = 2; 
	Query queries[q]; 
	queries[0].l = 0; 
	queries[0].r = 2; 
	queries[0].x = 2; 
	queries[0].idx = 0; 
	queries[1].l = 0; 
	queries[1].r = 3; 
	queries[1].x = 5; 
	queries[1].idx = 1; 

	answerQueries(n, queries, q, arr); 

	return 0; 
} 
