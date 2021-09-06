//UVA 10199

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

int n, t, visited[105], tin[105], low[105], m, timer;
vector<int> g[105];
map<string, int> mp;
string s[105];
set<string> ans;

void dfs(int u, int p = -1) {
    visited[u] = 1;
    tin[u] = low[u] = ++ timer;
    int child = 0;
    for(int v : g[u]) {
        if(p == v) continue;
        if(visited[v]) low[u] = min(low[u], tin[v]);
        else { 
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= tin[u] && p != -1) ans.insert(s[u]);
            ++child;
        }
    }
    if(p == -1 && child > 1) ans.insert(s[u]);
}

void solve() {
    ++t;
    for(int i = 1; i <= n; ++i) {
        cin >> s[i];
        mp[s[i]] = i;
        visited[i] = 0;
        tin[i] = low[i] = -1;
        g[i].clear();
    }
    timer = 0;
    ans.clear();
    cin >> m;
    for(int i = 1; i <= m; ++i) {
        string u, v;
        cin >> u >> v;
        g[mp[u]].pb(mp[v]);
        g[mp[v]].pb(mp[u]);
    }
    for(int i = 1; i <= n; ++i) {
        if(!visited[i]) dfs(i);
    }
    cout << "City map #" << t << ": " << ans.size() << " camera(s) found\n";
    for(string i : ans) cout << i << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin>>n;
    solve();
    while( cin >> n) {
        if(n == 0) return 0;
        cout << "\n";
        solve();
    }
    
	return 0;
}
