#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int MAX_N = 2e5 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;
const long long INF = 1e9 + 7;
const double EPS = 1e-9;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, Q;
int arr[MAX_N], st[4 * MAX_N];

void build(int node, int start, int end) {
    if (start == end) {
        st[node] = arr[start];
    }
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        st[node] = min(st[2 * node], st[2 * node + 1]);
    }
}

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        arr[idx] = val;
        st[node] = val;
    }
    else {
        int mid = (start + end) / 2;
        if (idx <= mid) update(2 * node, start, mid, idx, val);
        else update(2 * node + 1, mid + 1, end, idx, val);
        st[node] = min(st[2 * node], st[2 * node + 1]);
    }
}

int query(int node, int start, int end, int l, int r) {
    if (l > r) return INF;
    if (start == l && end == r) return st[node];
    int mid = (start + end) / 2;
    return min(query(2 * node, start, mid, l, min(r, mid)),
               query(2 * node + 1, mid + 1, end, max(l, mid + 1), r));
}

void solve() {
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    build(1, 1, N);
    while (Q--) {
        char c; cin >> c;
        if (c == '1') {
            int k, u; cin >> k >> u;
            update(1, 1, N, k, u);
        }
        else {
            int a, b; cin >> a >> b;
            cout << query(1, 1, N, a, b) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    for (int t = 1; t <= tc; t++) {
        //cout << "Case #" << t  << ": ";
        solve();
    }
}
