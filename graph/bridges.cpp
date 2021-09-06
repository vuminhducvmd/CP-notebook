//UVA 796

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
const int INF = 1e9;
const ll mod = 1e9+7;

int n, visited[10005], low[10005], tin[10005], timer;
vector<int> g[10005];
set<pair<int, int>> s;

void dfs(int u, int p = -1) {
    visited[u] = 1;
    low[u] = tin[u] = ++timer;
    for(int v : g[u]) {
        if(v == p) continue;
        if(visited[v]) low[u] = min(low[u], tin[v]);
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > tin[u]) {
                if(u < v) s.insert({u, v});
                else s.insert({v, u});
            }
        }
    }
}

void solve() {
    if(n == 0) {
        cout << "0 critical links\n\n";
        return;
    }
    for(int i = 0, u, m; i < n; ++i) {
        scanf("%d (%d)", &u, &m);
        g[u].clear();
        for(int j = 0, v; j < m; ++j) {
            cin >> v;
            g[u].pb(v);
        }
    }
    s.clear();
    timer = 0;
    for(int i = 0; i < n; ++i) {
        visited[i] = 0;
        low[i] = -1;
        tin[i] = -1;
    }
    for(int i = 0; i < n; ++i) {
        if(!visited[i]) dfs(i);
    }
    cout << s.size() << " critical links\n";
    for(pair<int, int> p : s) cout << p.st << " - " << p.nd << "\n";
    cout << "\n";
}

signed main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    
    while(cin >> n) {
        solve();
    }
    
	return 0;
}
