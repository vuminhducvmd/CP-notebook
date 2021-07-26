#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;

const ll mod=1e9+7;
const ll base=37;
 
string s;
ll n, p[1000005], prefix[1000005];
 
ll get(int i,int j) {
    return (prefix[j] - prefix[i - 1]*p[j - i + 1] + mod * mod) % mod;
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> s;
    n = s.length();
    s = " " + s;
    prefix[0] = 0; p[0] = 1;
    for(int i = 1; i <= n; ++i) {
        p[i] = p[i - 1] * base % mod;
        prefix[i] = (prefix[i - 1] * base + s[i] - 'a' + 1) % mod;
    }
 
	return 0;
}
