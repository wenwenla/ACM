struct LIS {
    // O(nlgn), strictly increase monotonically
    const static int N = 100005;
    int a[N], b[N];

    void input(int n) {
        for(int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
    }

    int solve(int n) {
        int len = 0;
        for(int i = 1; i <= n; ++i) {
            int* p = lower_bound(b + 1, b + len + 1, a[i]);
            *p = a[i];
            len = max(len, a[i] = p - b);
        }
        return len;
    }
} lis;