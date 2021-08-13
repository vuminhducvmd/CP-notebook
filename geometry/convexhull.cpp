#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define x real()
#define y imag()
 
typedef long long ll;
typedef long double ld;
typedef complex<ll> pt;
 
const ld EPS = 0.00000001;
const ll INF = 1e18;
const ll mod = 1e9+7;

bool cmp(pt p1, pt p2) {
    return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);
}

bool cw(pt a, pt b, pt c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
}

bool ccw(pt a, pt b, pt c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
}

vector<pt> convexhull(vector<pt>& poly) {
    if(poly.size() == 1) return poly;
    sort(poly.begin(), poly.end(), cmp);
    pt p1 = poly[0], p2 = poly.back();
    vector<pt> up, down;
    up.pb(p1); 
    down.pb(p1);
    
    for(int i = 1; i <poly.size(); ++i) {
        if(i == poly.size() - 1 || cw(p1, poly[i], p2)) {
            while(up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], poly[i])) {
                up.pop_back();
            }
            up.pb(poly[i]);
        }
        if(i == poly.size() - 1 || ccw(p1, poly[i], p2)) {
            while(down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], poly[i])) {
                down.pop_back();
            }
            down.pb(poly[i]);
        }
    }
    poly.clear();
    for(int i = 0; i < up.size(); ++i) poly.pb(up[i]);
    for(int i = down.size() - 2; i > 0; --i) poly.pb(down[i]);
    return poly;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int n;
    vector<pt> poly;
    
    cin>>n;
    for(int i = 1, _x, _y; i <= n; ++i) {
        cin >> _x >> _y;
        poly.pb({_x, _y});
    }
    poly = convexhull(poly);
    for(pt i : poly) cout << i.x << " " << i.y << endl;
    
	return 0;
}
