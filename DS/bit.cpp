//VNOJ NKINV

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

int n,ans,a[60005],bit[60005];

void upd(int pos,int val) {
    for(;pos<=60000;pos+=pos&-pos) bit[pos]+=val;
}

int get(int pos) {
    int res=0;
    for(;pos;pos-=pos&-pos) res+=bit[pos];
    return res;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];
    for(int i=1;i<=n;++i) {
        ans+=get(60000-a[i]);
        upd(60000-a[i]+1,1);
    }
    cout<<ans;

	return 0;
}
