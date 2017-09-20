namespace fastio {
    const int buf_size = 8388608;//about 8Mb
    char buf[buf_size];
    int pos = buf_size;
    int in;
    bool eof = false;

    inline void read_next() {
        in = fread(buf, 1, buf_size, stdin);
        pos = 0;
        eof = !in;
    }

    inline char nc() {
        if(pos == buf_size || pos == in) read_next();
        return buf[pos++];
    }

    template<typename T>
    inline void read_num(T& res) {
        bool neg = false;
        char now = nc();
        while(now == ' ' || now == '\n') now = nc();
        if(now == '-') {
            neg = true;
            now = nc();
        }
        T ret = 0;
        while(now != ' ' && now != '\n') {
            ret = ret * 10 + now - '0';
            now = nc();
        }
        res = (neg ? -ret : ret);
    }

    template<typename T>
    inline void put_num(T x) {
        if(x < 0) {
            putchar('-');
            x = -x;
        }
        if(x == 0) {
            putchar('0');
        }
        char tmp[32];
        int cnt = 0;
        while(x) {
            tmp[cnt++] = x % 10 + '0';
            x /= 10;
        }
        while(cnt > 0) {
            putchar(tmp[cnt - 1]);
            --cnt;
        }
    }
}
