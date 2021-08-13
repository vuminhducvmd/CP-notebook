//VNOJ LUBENICA
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

int n, k, p[100005][20], mx[100005][20], mn[100005][20], h[100005], q;
vector<pair<int, int>> g[100005];

void dfs(int u, int par = -1) {
    for(pair<int, int> e : g[u]) {
        if(e.st == par)  continue;
        p[e.st][0] = u;
        h[e.st] = h[u] + 1;
        mx[e.st][0] = mn[e.st][0] = e.nd;
        dfs(e.st, u);
    }
}

void prep() {
    for(int j = 0; j <= 17; ++j) {
        for(int i = 1; i <= n; ++i) {
            p[i][j] = -1;
            mx[i][j] = 0;
            mn[i][j] = 1e9;
        }
    }
    dfs(1);
    for(int j = 1; j <= 17; ++j) {
        for(int i = 1; i <= n; ++i) {
            if(p[i][j - 1] == -1) continue;
            p[i][j] = p[p[i][j - 1]][j - 1];
            mn[i][j] = min(mn[p[i][j - 1]][j - 1], mn[i][j - 1]);
            mx[i][j] = max(mx[p[i][j - 1]][j - 1], mx[i][j - 1]);
        }
    }
}

pair<int, int> lca(int u, int v) {
    pair<int, int> ans = {0, 1e9};
    if(h[u] > h[v]) swap(u, v);
    for(int j = 17; j >= 0; --j) {
        if(p[v][j] == -1) continue;
        if(h[p[v][j]] >= h[u]) {
            ans.st = max(ans.st, mx[v][j]);
            ans.nd = min(ans.nd, mn[v][j]);
            v = p[v][j];
        }
    }
    if(u == v) return ans;
    for(int j = 17; j >= 0; --j) {
        if(p[v][j] == -1 || p[u][j] == -1) continue;
        if(p[v][j] != p[u][j]) {
            ans.st = max(ans.st, max(mx[v][j], mx[u][j]));
            ans.nd = min(ans.nd, min(mn[v][j], mn[u][j]));
            u = p[u][j];
            v = p[v][j];
        } 
    }
    ans.st = max(ans.st, max(mx[u][0], mx[v][0]));
    ans.nd = min(ans.nd, min(mn[u][0], mn[v][0]));
    return ans;
    
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n;
    for(int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        g[u].pb({v, w});
        g[v].pb({u, w});
    }
    prep();
    cin >> q;
    for(int i = 1, u, v; i <= q; ++i) {
        cin >> u >> v;
        cout << lca(u, v).nd << " " << lca(u, v).st << "\n";
    }
    
	return 0;
}
