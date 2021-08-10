//CF 86D
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
 
const double EPS=0.000001;
const ll INF=1e9;
const ll mod=1e9+7;

ll n, t, a[200005], ans[200005], blk, res, cnt[1000005];
 
struct query {
    int l, r, idx;
    bool operator < (query x) {
        if(r / blk != x.r / blk) return r / blk < x.r / blk;
        return l < x.l;
    }
};
 
query q[200005];
 
void add(int x) {
    res += (cnt[x] * 2 + 1) * x;
    ++cnt[x];
}
 
void del(int x) {
    --cnt[x];
    res -= (cnt[x] * 2 + 1) * x;
}
 
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
 
    cin >> n >> t;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    for(int i = 1, l, r; i<=t; ++i) {
        cin >> l >> r;
        q[i] = {l, r, i};
    }
    blk = sqrt(n);
    sort(q + 1, q + t + 1);
    int l = 1, r = 0;
    for(int i = 1; i <= t; ++i) {
        while(l > q[i].l) add(a[--l]);
        while(l < q[i].l) del(a[l++]);
        while(r > q[i].r) del(a[r--]);
        while(r < q[i].r) add(a[++r]);
        ans[q[i].idx]=res;
    }
    for(int i = 1; i <= t; ++i) cout << ans[i] << "\n";
    
    return 0;
}
 
