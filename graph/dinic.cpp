// VNOJ NKFLOW

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

struct Edge {
    int u, v, cap, flow;
};

struct Maxflow {
    int n, s, t;
    vector<int> d, ptr, q; //depth, pointer, queue
    vector<Edge> e;
    vector<vector<int>> g;
    
    Maxflow(int n) : n(n), d(n), ptr(n), q(n), g(n) {
        e.clear();
        for(int i = 0; i < n; ++i) {
            g[i].clear();
            ptr[i] = 0;
        }
    }
    
    void addEdge(int u, int v, int cap) {
        Edge e1 = {u, v, cap, 0};
        Edge e2 = {v, u, 0, 0};
        
        g[u].pb((int) e.size());
        e.pb(e1);
        g[v].pb((int) e.size());
        e.pb(e2);
    }
    
    int getMF(int _s, int _t) {
        s = _s; t = _t;
        int flow = 0;
        for(;;) {
            if(!bfs()) break;
            for(int i = 0; i < n; ++i) ptr[i] = 0;
            while(int pushed = dfs(s, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
    
private:
    bool bfs() {
        int qh = 0, qt = 0; //queue_head, queue_tail
        q[qt++] = s;
        for(int i = 0; i < n; ++i) d[i] = -1;
        d[s] = 0;
        
        while(qh < qt && d[t] == -1) {
            int u = q[qh++];
            for(int id : g[u]) {
                int to = e[id].v;
                if(d[to] == -1 && e[id].flow < e[id].cap) {
                    q[qt++] = to;
                    d[to] = d[u] + 1;
                }
            }
        }
        return d[t] != -1;
    }
    
    int dfs(int u, int flow) {
        if(!flow) return 0;
        if(u == t) return flow;
        for(; ptr[u] < (int) g[u].size(); ++ptr[u]) {
            int id = g[u][ptr[u]], to = e[id].v;
            if(d[to] != d[u] + 1) continue;
            int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
            if(pushed) {
                e[id].flow += pushed;
                e[id ^ 1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
};

int n, m, s, t;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n >> m >> s >> t;
    Maxflow mf(n);
    for(int i = 1, u, v, c; i <= m; ++i) {  
        cin >> u >> v >> c;
        mf.addEdge(u - 1, v - 1, c);
    }
    cout << mf.getMF(s - 1, t - 1);
    
	return 0;
}
