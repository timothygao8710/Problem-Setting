#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define pb push_back

#define f first
#define s second

template <typename T>
struct segtree
{
    T none, val, lazy;
    int gL, gR, mid;
    segtree<T>* left, * right;

    T comb(T& l, T& r)
    {
        return min(l, r);
    }

    //In this code, lazy represents the value only to be propagated(this->value already updated)
    void compose(segtree<T>* tree, T v)
    {
        tree->lazy = max(v, tree->lazy);
        tree->val = max(tree->val, tree->lazy);
    }

    void push()
    {
        if (gL != gR)
        {
            compose(left, lazy);
            compose(right, lazy);
        }
    }

    segtree(int l, int r)
    { //modify arr type
        none = INT_MAX;
        lazy = -1;
        gL = l, gR = r, mid = (gL + gR) / 2;
        if (l == r)
        {
            val = -1;
        }
        else
        {
            left = new segtree<T>(l, mid);
            right = new segtree<T>(mid + 1, r);
            val = comb(
                left->val, right->val);
        }
    }

    T query(int l, int r)
    {
        if (gL > r || gR < l)
        {
            return none;
        }

        if (gL == l && gR == r)
        {
            return val;
        }
        push();
        if (val == -1)
        {
            val = -1;
        }
        T a = left->query(l, min(r, mid));
        T b = right->query(max(l, mid + 1), r);
        return comb(a, b);
    }

    void update(int l, int r, T updlazy)
    {
        if (gL > r || gR < l) {
            return;
        }

        if (gL == l && gR == r) {
            compose(this, updlazy);
        }
        else {
            push();
            left->update(l, min(r, mid), updlazy);
            right->update(max(l, mid + 1), r, updlazy);
            val = comb(left->val, right->val);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int N, M, K, Q; cin >> N >> M >> K >> Q;
    vector<pii> roads(K);
    vector<array<int, 3>> bps;
    for (int i = 0; i < K; i++) {
        int lane, l, r; cin >> l >> r >> lane;
        bps.pb({ lane, 0, i });
        roads[i] = pii(l, r);
    }
    vector<array<int, 4>> queries(Q);
    vector<int> res(Q);
    for (int i = 0; i < Q; i++) {
        int A, B, C, D; cin >> A >> B >> C >> D;
        if (D < B) {
            swap(A, C); swap(B, D);
        }
        bps.pb({ D, 1, i });
        queries[i] = { A, B, C, D };
    }
    sort(bps.begin(), bps.end());
    segtree<int> sgt(0, 2*M + 2);

    for (auto i : bps) {
        if (i[1]) {
            array<int, 4> cur = queries[i[2]];

            //collapse roads
            int mn = sgt.query(min(2*cur[0], 2*cur[2]), max(2*cur[0], 2*cur[2]));
            if (mn >= cur[1] || cur[0] == cur[2]) {
                res[i[2]] = 1;
            }
        }
        else {
            sgt.update(2*roads[i[2]].f, 2*roads[i[2]].s, i[0]);
        }
    }
    for (int i : res) {
        cout << (i ? "YES" : "NO") << '\n';
    }
    return 0;
}