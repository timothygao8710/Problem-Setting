#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define pb push_back

#define f first
#define s second

const int mod = 1e9 + 7;

int binpow(ll base, ll pow)
{
    ll ret = 1;
    while(pow > 0){
        if(pow & 1) ret = (ret * base)%mod;
        base = (base * base)%mod;
        pow >>= 1;
    }
    return ret;
}

ll get(ll a, ll b)
{
    return max(binpow(a, b), binpow(b, a));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N; cin >> N;
    vector<ll> nums(N);
    for (int i = 0; i < N; i++) cin >> nums[i];

    ll ret = 0;
    vector<ll> inTree(N), Dist(N);
    //InTree is a 0/1 vector representing wether the ith node is in the spanning tree
    //Dist is bestDist as described in the editorial
    
    inTree[0] = 1;
    for(int i = 1; i<N; i++){
        ll best = max(get(nums[i], nums[0]), get(nums[0], nums[i]));
        Dist[i] = best;
    }
    for (int i = 1; i < N; i++)
    {
        int j = -1;
        for (int k = 0; k < N; k++)
        {
            if (inTree[k])
                continue;
            if (j == -1 || Dist[k] > Dist[j])
            {
                j = k;
            }
        }
        //calculate new approximate distances
        ret += Dist[j];
        ret %= mod;
        inTree[j] = 1;
        for (int k = 0; k < N; k++)
        {
            if(inTree[k]) continue;
            ll best = max(get(nums[j], nums[k]), get(nums[k], nums[j]));
            Dist[k] = max(Dist[k], best);
        }
    }
    cout << ret << '\n;
    return 0;
}