//CF 20C

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
 
const ld EPS=0.00000001;
const ll INF=1e18;
const ll mod=1e9+7;

ll n,m,d[100005],p[100005];
bool vis[100005];
vector<pair<ll,ll>> g[100005];
priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;
stack<int> trace;

void dijkstra(int s) {
    memset(d,0x3f3f3f,sizeof d);
    memset(vis,0,sizeof vis);
    d[s]=0; 
    pq.push({0,s});
    while(!pq.empty()) {
        ll u=pq.top().nd;
        pq.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(pair<ll,ll> e:g[u]) {
            ll v=e.st,w=e.nd;
            if(d[u]+w<d[v]) {
                d[v]=d[u]+w;
                pq.push({d[v],v});
                p[v]=u;
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin>>n>>m;
    for(int i=1,u,v,w;i<=m;++i) {
        cin>>u>>v>>w;
        g[u].pb({v,w});
        g[v].pb({u,w});
    }
    
    dijkstra(1);
    
    if(p[n]==0) {
        cout<<-1;
        return 0;
    }
    ll t=n;
    trace.push(n);
    while(p[t]!=0) {
        trace.push(p[t]);
        t=p[t];
    }
    while(!trace.empty()) {
        cout<<trace.top()<<" ";
        trace.pop();
    }

	return 0;
}
