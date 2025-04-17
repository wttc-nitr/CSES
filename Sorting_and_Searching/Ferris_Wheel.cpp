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

// pair the lightest child with the heaviest without exceeding the weight limit
// else include a single child
// TWO POINTER PROBLEM

void solve(void) {
    int N, X; cin >> N >> X;
    vector<ll> arr(N); for (auto &x : arr) cin >> x;

    sort (arr.begin(), arr.end());

    int cnt = 0;

    for (int low = 0, high = N-1; low <= high; ) {
    	if (arr[high] + arr[low] <= X) {
    		cnt++;
    		high--;
    		low++;
    	}
    	else {
    		cnt++;
    		high--;
    	}
    }

    cout << cnt;
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