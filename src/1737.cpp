#include <bits/stdc++.h>

using namespace std;

#define print_op(...) ostream& operator<<(ostream& out, const __VA_ARGS__& u)
template<typename A, typename B> print_op(pair<A, B>) { return out << "(" << u.first << ", " << u.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> print_op(T_container) { out << "{"; string sep; for (const T &x : u) out << sep << x, sep = ", "; return out << "}"; }
template<typename T> void dbg_out(string s, T x) {cerr << "\033[1;35m" << s << "\033[0;32m = \033[33m" << x << "\033[0m\n";}
template<typename T, typename... Args> void dbg_out(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++; else
if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << "\033[1;35m" << s.substr(0, i) << "\033[0;32m = \033[33m" << x << "\033[31m | "; dbg_out(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}
#ifdef LOCAL
#define dbg(...) dbg_out(#__VA_ARGS__, __VA_ARGS__)
#else
#define dbg(...)
#endif

#define ar array
#define ll long long
#define ld long double
#define sz(x) ((int)x.size())
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++) 
#define all(a) (a).begin(), (a).end()

const int MAX_N = 1e5 + 5;
const int MAX_L = 20;
const int MAX_C = 26;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;

struct Node {
    Node *ln = NULL, *rn = NULL;
    ll sum;
    Node(): sum() {}
    Node(ll x): sum(x) {}
    Node(Node *ln, Node *rn, ll x): ln(ln), rn(rn), sum(x) {}
    Node(Node l, Node r): sum(l.sum + r.sum) {}
    void init() {
        if (ln == NULL || rn == NULL) {
            ln = new Node(), rn = new Node();
        }
    }
};
 
struct SegmentTree { 
    int n, ver; vector<Node*> st;
 
    void init(int _n, int q) { n = _n; ver = 0; st.resize(q); st[0] = new Node(); }
    void init(vector<int> &a, int q) { init(sz(a), q); build(a, st[0], 0, n - 1); }
 
    void apply(Node *node, ll x) {
        node->sum = x;
    }
 
    void pull_up(Node *node) {
        node->sum = node->ln->sum + node->rn->sum;
    }
 
    void build(vector<int> &a, Node *node, int start, int end) {
        if (start == end) {
            *node = Node(a[start]);
            return;
        }
        node->init();
        int mid = (start + end) / 2;
        build(a, node->ln, start, mid);
        build(a, node->rn, mid + 1, end);
        pull_up(node);
    }
 
    void update(Node *node, int start, int end, int i, ll x) {
        if (start == end) {
            apply(node, x);
            return;
        }
        int mid = (start + end) / 2;
        if (i <= mid) {
            node->ln = new Node(node->ln->ln, node->ln->rn, node->ln->sum);
            update(node->ln, start, mid, i, x);
        }
        else {
            node->rn = new Node(node->rn->ln, node->rn->rn, node->rn->sum);
            update(node->rn, mid + 1, end, i, x);
        }
        pull_up(node);
    }
 
    Node query(Node *node, int start, int end, int l, int r) {
        if (r < start || end < l) return Node();
        if (l <= start && end <= r) return *node;
        int mid = (start + end) / 2;
        return Node(query(node->ln, start, mid, l, r), query(node->rn, mid + 1, end, l, r));
    }
    
    void update(int k, int i, ll x) { update(st[k], 0, n - 1, i, x); }
    Node query(int k, int l, int r) { return query(st[k], 0, n - 1, l, r); }
    void copy(int k) { st[++ver] = new Node(st[k]->ln, st[k]->rn, st[k]->sum); }
};
 
void solve(int tc = 0) {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    SegmentTree st; st.init(a, q);
    while (q--) {
        int t, k; cin >> t >> k; k--;
        if (t == 1) {
            int i, x; cin >> i >> x; i--;
            st.update(k, i, x);
        } else if (t == 2) {
            int l, r; cin >> l >> r; l--; r--;
            cout << st.query(k, l, r).sum << "\n";
        } else {
            st.copy(k);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve(t);
    }
}