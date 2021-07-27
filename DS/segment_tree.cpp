//VNOJ QMAX

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

int n,m,q;
pair<int,int> st[200005];

void down(int id) {
    int val=st[id].nd;
    st[id<<1].st+=val;
    st[id<<1|1].st+=val;
    st[id<<1].nd+=val;
    st[id<<1|1].nd+=val;
    st[id].nd=0;
}

void upd(int id,int l,int r,int x,int y,int val) {
    if(y<l||r<x) return;
    if(x<=l&&r<=y) {
        st[id].st+=val;
        st[id].nd+=val;
        return;
    }
    down(id);
    int mid=(l+r)>>1;
    upd(id<<1,l,mid,x,y,val);
    upd(id<<1|1,mid+1,r,x,y,val);
    st[id].st=max(st[id<<1].st,st[id<<1|1].st);
}

int get(int id,int l,int r,int x,int y) {
    if(y<l||r<x) return 0;
    if(x<=l&&r<=y) return st[id].st;
    down(id);
    int mid=(l+r)>>1;
    return max(get(id<<1,l,mid,x,y),get(id<<1|1,mid+1,r,x,y));
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin>>n>>m;
    for(int i=1,u,v,k;i<=m;++i) {
        cin>>u>>v>>k;
        upd(1,1,n,u,v,k);
    }
    cin>>q;
    for(int i=1,u,v;i<=q;++i) {
        cin>>u>>v;
        cout<<get(1,1,n,u,v)<<"\n";
    }

	return 0;
}
