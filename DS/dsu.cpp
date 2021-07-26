#include <bits/stdc++.h>
using namespace std;

int n, dsu[100005];
 
int root(int u) {
	return dsu[u]<0?u:(dsu[u]=root(dsu[u]));
}

void merge(int u,int v) {
	if((u=dsu[u]))==(v=dsu[v])) return;
	if(dsu[u]>dsu[v]) swap(u,v);
    dsu[u]+=dsu[v];
    dsu[v]=u;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin>>n;
    memset(dsu, -1, sizeof dsu);

	return 0;
}
