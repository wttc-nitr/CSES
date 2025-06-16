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

struct Node {
	ll mx, lazy;

	Node () : mx(0), lazy(0) {}
};

vector<Node> tree;

void lazy_propagate (int node, int node_low, int node_high) {
	if (tree[node].lazy > 0) {
		tree[node].mx += tree[node].lazy;

		if (node_low < node_high) {
			// export lazy to children
			tree[2 * node].lazy += tree[node].lazy;
			tree[2 * node + 1].lazy += tree[node].lazy;
		}

		tree[node].lazy = 0;
	}
}

ll get_max (int node, int node_low, int node_high, int query_low, int query_high) {
	// disjoint
	if (node_high < query_low || query_high < node_low) 
		return 0;
	
	// before doing anything, handle any pending updates	
	lazy_propagate (node, node_low, node_high);

	// interval inside query
	if (query_low <= node_low && node_high <= query_high) 
		return tree[node].mx;

	// partially inside
	int mid = node_low + (node_high - node_low) / 2;

	auto left_max = get_max (2 * node, node_low, mid, query_low, query_high);
	auto right_max = get_max (2 * node + 1, mid + 1, node_high, query_low, query_high);

	return max (left_max, right_max);
}

void update (int node, int node_low, int node_high, int query_low, int query_high, int val) {
	// disjoint
	if (node_high < query_low || query_high < node_low)
		return;

	// before doing anything, handle any pending updates
	lazy_propagate (node, node_low, node_high);

	// interval inside query
	if (query_low <= node_low && node_high <= query_high) {
		tree[node].lazy += val;
		lazy_propagate (node, node_low, node_high); // bcoz we've to calculate max in parent
		return;
	}

	// partially inside
	int mid = node_low + (node_high - node_low) / 2;	

	update (2 * node, node_low, mid, query_low, query_high, val);
	update (2 * node + 1, mid + 1, node_high, query_low, query_high, val);

	tree[node].mx = max (tree[2 * node].mx , tree[2 * node + 1].mx);
}

void solve(void) {
    int N, Q; cin >> N >> Q;

    vector<ll> arr(N); for (auto &x : arr) cin >> x;

    while (__builtin_popcount(N) != 1)
    	N++;

    tree.resize(2 * N);

    for (int i = 0; i < (int)arr.size(); i++)
    	tree[N + i].mx = arr[i];

    // generate max
    for (int i = N-1; i >= 1; i--) 
    	tree[i].mx = max (tree[2 * i].mx, tree[2 * i + 1].mx);

    while (Q-- > 0) {
    	int type; cin >> type;
    	if (type == 1) {
    		int a, b, u; cin >> a >> b >> u;
    		// update
    		a--; b--;
    		update(1, N, 2 * N - 1, N + a, N + b, u);
    	}
    	else {
    		int k; cin >> k;
    		// print
    		k--;
    		cout << get_max (1, N, 2 * N - 1, N + k, N + k) << '\n';
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