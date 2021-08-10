#pragma GCC optimize("Ofast")
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

struct Node {
    int child[2], cnt[2];
    Node() {
        child[0]  = child[1] = -1;
        cnt[0] = cnt[1] = 0;
    }
};

Node node[6500000];
int N = 0;

void add(int x) {
    int cur = 0;
    for(int i = 30; i >= 0; --i) {
        int nxt = bit(x, i);
        if(node[cur].child[nxt] == -1) node[cur].child[nxt] = ++N;
        ++node[cur].cnt[nxt];
        cur = node[cur].child[nxt];
    }
}


void del(int x) {
    int cur = 0;
    for(int i = 30; i >= 0; --i) {
        --node[cur].cnt[bit(x, i)];
        cur = node[cur].child[bit(x, i)];
    }
}

int get(int x) {
    int cur = 0, res = 0;
    for(int i = 30; i >= 0; --i) {
        int nxt = !bit(x, i);
        if(node[cur].cnt[nxt] > 0) {
            res = res * 2 + 1;
            cur = node[cur].child[nxt];
        }
        else {
            res = res * 2;
            cur = node[cur].child[!nxt];
        }
    }
    return max(res, x);
}

int t, x;
char ch;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> t;
    while(t--) {
        cin >> ch >> x;
        if(ch == '+') add(x);
        else if(ch == '-') del(x);
        else cout << get(x) << "\n";
    }
    
	return 0;
}
