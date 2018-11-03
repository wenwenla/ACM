const int N = 100005;
struct KMP {
    int fail[N], plen;
    const char* p;
    void init(const char* pattern) {
        p = pattern;
        plen = strlen(p);
        fail[0] = 0; fail[1] = 0;
        for(int i = 2; i <= plen; ++i) {
            int k = fail[i - 1];
            while(k != 0 && p[i - 1] != p[k]) k = fail[k];
            fail[i] = (p[i - 1] == p[k]) ? k + 1 : 0;
        }
    }
    int match(const char* s) {
        int ans = 0, np = 0;
        for(int i = 0; s[i]; ++i) {
            while(np != 0 && s[i] != p[np]) {
                np = fail[np];
            }
            if(s[i] == p[np]) ++np;
            if(np == plen) {
                ++ans;
                SELECT_ONE
                //np = fail[np];
                //np = 0;
            }
        }
        return ans;
    }
} kmp;