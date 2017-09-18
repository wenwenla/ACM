struct ST {
    //1 base, query O(1)
    int dp[50005][20];
    int n;
    int arr[50005];

    void make(int _n) {
		assert(n < 50005);
        n = _n;
        for(int i = 1; i <= n; ++i) {
            dp[i][0] = arr[i];
        }
        for(int j = 1; (1 << j) <= n; ++j) {
            for(int i = 1; (i + (1 << (j - 1))) <= n; ++i) {
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return min(dp[l][k], dp[r - (1 << k) + 1][k]);
    }
} st;