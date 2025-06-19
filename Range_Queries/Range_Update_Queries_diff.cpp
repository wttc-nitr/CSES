/*
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
*/
#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vb vector<bool>
#define vi vector<int>
#define vc vector<char>
#define INF (1LL << 60)
#define inf (1 << 30)

// use diff array for: range-update n point-query

vector<ll> tree;

ll get_sum (int node, int node_left, int node_right, int query_left, int query_right) {
	// disjoint
	if (node_right < query_left || query_right < node_left)
		return 0;

	// interval inside query
	if (query_left <= node_left && node_right <= query_right)
		return tree[node];

	// partially inside
	int mid = node_left + (node_right - node_left) / 2;

	auto left_sum = get_sum (2 * node, node_left, mid, query_left, query_right);
	auto right_sum = get_sum (2 * node + 1, mid + 1, node_right, query_left, query_right);

	return left_sum + right_sum;
}

void update (int node) {
    for (int i = node/2; i >= 1; i /= 2)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}

void solve(void) {
    int N, Q; cin >> N >> Q;
    vector<ll> arr(N); for (auto &x : arr) cin >> x;

    while (__builtin_popcount(N) != 1)
    	N++;

    tree.resize(2 * N);

    // create diff
    vector<ll> diff(arr.size()); diff[0] = arr[0];

    for (int i = 1; i < (int)arr.size(); i++)
    	diff[i] = arr[i] - arr[i-1];

    for (int i = 0; i < (int)diff.size(); i++)
    	tree[N + i] = diff[i];

    // generate sum
    for (int i = N-1; i >= 1; i--)
    	tree[i] = tree[2 * i] + tree[2 * i + 1];

    while (Q-- > 0) {
    	int type; cin >> type;

    	if (type == 1) {
    		// update
    		int a, b, u; cin >> a >> b >> u;
    		a--; b--;

    		if (N + a < (int)tree.size()) {
    			tree[N + a] += u;
    			update (N + a);
    		}

    		if (N + b + 1 < (int)tree.size()) {
    			tree[N + b + 1] -= u;
    			update (N + b + 1);
    		}
    	}
    	else {
    		// print
    		int k; cin >> k;
    		k--;

    		cout << get_sum (1, N, 2 * N -1, N, N + k) << '\n';
    	}
    }
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int test_cases = 1; 
    while (test_cases-- > 0) {
        solve();
    }

#ifndef ONLINE_JUDGE
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}