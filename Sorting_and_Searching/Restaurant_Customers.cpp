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

// if we arrange the intervals on a number line & start from the left-most & keep travelling to right,
// if we meet an starting interval, we can increase the count (persons) & in case of ending interval, decrease it

void solve(void) {
    int N; cin >> N;
    vector<int> arrival(N), departure(N);
    for (int i = 0; i < N; i++) 
    	cin >> arrival[i] >> departure[i];
    
    sort (arrival.begin(), arrival.end());
    sort (departure.begin(), departure.end());

    int best = 0;

    for (int i = 0, j = 0, cnt = 0; i < N && j < N; ) {
    	if (arrival[i] < departure[j]) {
    		cnt++;
    		i++;
    	}
    	else {
    		cnt--;
    		j++;
    	}

    	best = max (best, cnt);
    }

    cout << best;
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