char s[2000];
int dp[2000][2000];
/*最长回文子序列*/
int f(int i, int j) {
    if(i > j) return 0;
    if(dp[i][j] != 0) return dp[i][j];
    if(i == j) return dp[i][j] = 1;
    else {
        if(s[i] == s[j]) {
            return dp[i][j] = f(i + 1, j - 1) + 2;
        } else {
            return dp[i][j] = max(f(i, j - 1), f(i + 1, j));
        }
    }
}