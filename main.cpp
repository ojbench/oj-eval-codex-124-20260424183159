#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n; // leaves used
    int N; // tree base (power of two)
    vector<int> mn; // segment minimum
    vector<int> lz; // lazy add
    SegTree(int n_, int init_val) {
        n = max(1, n_);
        N = 1; while (N < n) N <<= 1;
        mn.assign(N << 1, INT_MAX / 2);
        lz.assign(N << 1, 0);
        for (int i = 0; i < n_; ++i) mn[N + i] = init_val;
        for (int i = N - 1; i >= 1; --i) mn[i] = std::min(mn[i<<1], mn[i<<1|1]);
    }
    inline void apply(int p, int v) {
        mn[p] += v;
        if (p < N) lz[p] += v;
    }
    inline void push(int p) {
        if (lz[p]) {
            apply(p<<1, lz[p]);
            apply(p<<1|1, lz[p]);
            lz[p] = 0;
        }
    }
    int query_min(int l, int r) { return query_min(1, 1, N, l, r); }
    int query_min(int p, int nl, int nr, int l, int r) {
        if (l > nr || r < nl) return INT_MAX / 2;
        if (l <= nl && nr <= r) return mn[p];
        push(p);
        int mid = (nl + nr) >> 1;
        return min(query_min(p<<1, nl, mid, l, r), query_min(p<<1|1, mid+1, nr, l, r));
    }
    void range_add(int l, int r, int v) { range_add(1, 1, N, l, r, v); }
    void range_add(int p, int nl, int nr, int l, int r, int v) {
        if (l > nr || r < nl) return;
        if (l <= nl && nr <= r) { apply(p, v); return; }
        push(p);
        int mid = (nl + nr) >> 1;
        range_add(p<<1, nl, mid, l, r, v);
        range_add(p<<1|1, mid+1, nr, l, r, v);
        mn[p] = min(mn[p<<1], mn[p<<1|1]);
    }
};

static inline bool read_int(int &out) {
    int c = getchar_unlocked();
    while (c != EOF && (c < '0' || c > '9') && c != '-') c = getchar_unlocked();
    if (c == EOF) return false;
    int sign = 1;
    if (c == '-') { sign = -1; c = getchar_unlocked(); }
    long long val = 0;
    while (c >= '0' && c <= '9') { val = val * 10 + (c - '0'); c = getchar_unlocked(); }
    out = (int)(val * sign);
    return true;
}

int main() {
    int x, k, p;
    if (!read_int(x)) return 0;
    read_int(k);
    read_int(p);

    int segments = max(0, x - 1);
    SegTree st(max(1, segments), k);

    for (int i = 0; i < p; ++i) {
        int u, v, n; read_int(u); read_int(v); read_int(n);
        if (segments == 0 || v <= u) {
            putchar_unlocked('T'); putchar_unlocked('\n');
            continue;
        }
        int l = max(1, u);
        int r = min(segments, v - 1);
        if (l > r) {
            putchar_unlocked('T'); putchar_unlocked('\n');
            continue;
        }
        int m = st.query_min(l, r);
        if (m >= n) {
            st.range_add(l, r, -n);
            putchar_unlocked('T');
        } else {
            putchar_unlocked('N');
        }
        putchar_unlocked('\n');
    }
    return 0;
}
