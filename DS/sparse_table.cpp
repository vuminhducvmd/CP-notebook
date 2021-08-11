#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define st first
#define nd second
#define lb lower_bound
#define ub upper_bound
#define bit(x, i) ((x>>i)&1)
 
typedef long long ll;
typedef long double ld;
typedef complex<ll> pt;
 
const ld EPS = 0.00000001;
const ll INF = 1e18;
const ll mod = 1e9+7;

int n, s, l, a[100005], lg[100005], st[100005][23];

int calc(int x, int y) {
    int loga = lg[y - x + 1];
    return max(st[x][loga], st[y - (1 << loga) + 1][loga]);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n >> s >> l;
    lg[1] = 0;
    for(int i = 1; i <= n; ++i) {
        if(i > 1) lg[i] = lg[i/2] + 1;
        cin >> a[i];
        st[i][0] = a[i];
    }
    for(int j = 1; j <= 20; ++j) {
        for(int i = 1; i + (1 << j) <= n + 1; ++i) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
    
	return 0;
}
