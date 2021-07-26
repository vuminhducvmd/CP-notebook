//VNOJ LATGACH4
//simple matrix multiplication
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const ll mod=111539786;

struct Matrix {
    vector<vector<ll>> mat;
    
    Matrix(int n=0,int m=0) {
        mat.assign(n,vector<ll>(m,0));
    }
    
    Matrix operator * (const Matrix &x) {
        int n=mat.size(),m=mat[0].size(),p=x.mat[0].size();
        Matrix ans(n,p);
        for(int i=0;i<n;++i) {
            for(int j=0;j<p;++j) {
                for(int k=0;k<m;++k) {
                    ans.mat[i][j]=(ans.mat[i][j]+mat[i][k]*x.mat[k][j]%mod)%mod;
                }
            }
        }
        return ans;
    }
};

Matrix binpow(Matrix x,ll y) {
    int n=x.mat.size();
    Matrix res(n,n);
    for(int i=0;i<n;++i) res.mat[i][i]=1;
    while(y) {
        if(y&1) res=res*x;
        x=x*x; y>>=1;
    }
    return res;
}

ll t,n;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin>>t;
    while(t--) {
        cin>>n;
        Matrix ans(1,2),mul(2,2);
        ans.mat[0][1]=1;
        mul.mat[0][1]=mul.mat[1][0]=mul.mat[1][1]=1;
        ans=ans*binpow(mul,n);
        cout<<ans.mat[0][1]<<"\n";
    }

	return 0;
}
