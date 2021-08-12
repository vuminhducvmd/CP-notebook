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

int n, q, tin[200005], tout[200005], timer = 0, a[200005], x;
string s;
pair<int, int> st[800005];
vector<int> g[200005];

void dfs(int u, int p = -1) {
    tin[u] = ++timer;
    for(int v : g[u]) {
        if(v == p) continue;
        dfs(v, u);
    }
    tout[u] = timer;
}

void down(int id, int l, int r) {
    if(st[id].nd == 0) return;
    int mid = (l + r) >> 1;
    st[id << 1].st = mid - l + 1 - st[id << 1].st;
    st[id << 1].nd ^= 1;
    st[id << 1 | 1].st = r - mid - st[id << 1 | 1].st;
    st[id << 1 | 1].nd ^= 1;
    st[id].nd = 0;
}

void build(int id, int l, int r) {
    if(l == r) {
        st[id].st = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    st[id].st = st[id << 1].st + st[id << 1 | 1].st;
}

void upd(int id, int l, int r, int x, int y) {
    if(y < l || r < x) return;
    if(x <= l && r <= y) {
        st[id].st = r - l + 1 - st[id].st;
        st[id].nd ^= 1;
        return;
    }
    int mid = (l + r) >> 1;
    down(id, l, r);
    upd(id << 1, l, mid, x, y);
    upd(id << 1 | 1, mid + 1, r, x, y);
    st[id].st = st[id << 1].st + st[id << 1 | 1].st;
}

int get(int id, int l, int r, int x, int y) {
    if(y < l || r < x) return 0;
    if(x <= l && r <= y) return st[id].st;
    int mid = (l + r) >> 1;
    down(id, l, r);
    return get(id << 1, l, mid, x, y) + get(id << 1 | 1, mid + 1, r, x, y);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n;
    for(int i = 2, u; i <= n; ++i) {
        cin >> u;
        g[u].pb(i);
    }
    dfs(1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[tin[i]];
    }
    build(1, 1, n);
    cin >> q;
    while(q--) {
        cin >> s >> x;
        if(s == "pow") upd(1, 1, n, tin[x], tout[x]);
        else cout << get(1, 1, n, tin[x], tout[x]) << "\n";
    }
    
	return 0;
}
