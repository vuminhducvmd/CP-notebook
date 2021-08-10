//SPOJ NAJPF
#include <bits/stdc++.h>
using namespace std;

int T, pf[2000005];
vector<int> ans;
string s, t;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> T;
    while(T--) {
        cin >> t >> s;
        t = s + '#' + t;
        ans.clear();
        for(int i = 1; i <= t.length(); ++i) {
            int j = pf[i - 1];
            while(j > 0 && t[j] != t[i]) j = pf[j - 1];
            if(t[i] == t[j]) ++j;
            pf[i] = j;
            if(pf[i] == s.length()) ans.pb(i - 2*s.length() + 1);
        }
        if(ans.size()) {
            cout << ans.size() << "\n";
            for(int i : ans) cout << i << " ";
            cout << "\n\n";
        }
        else cout << "Not found\n\n";
    }
    
	return 0;
}
