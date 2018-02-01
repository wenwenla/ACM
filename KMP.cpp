int Pi[N];//next

void make_prefix(const char* p) {
    //1 base
    Pi[1] = 0;
    int k = 0;
    for(int i = 2; p[i]; ++i) {
        while(k > 0 && p[k + 1] != p[i]) {
            k = Pi[k];
        }
        if(p[k + 1] == p[i]) {
            ++k;
        }
        Pi[i] = k;
    }
}

int kmp_match(const char* p, const char* s) {
    //1 base
    make_prefix(p);
    int len = strlen(p + 1);
    int cnt = 0;
    int ans = 0;
    for(int i = 1; s[i]; ++i) {
        while(cnt > 0 && p[cnt + 1] != s[i]) {
            cnt = Pi[cnt];
        }
        if(p[cnt + 1] == s[i]) {
            ++cnt;
        }
        if(cnt == len) {
            ++ans;
            cnt = Pi[cnt];
        }
    }
    return ans;
}