int ConvexHull(Point* in, Point* out, int n) {
    sort(in, in + n);
    n = unique(in, in + n) - in;
    int m = 0;
    for(int i = 0; i < n; ++i) {
        while(m > 1 && cmp(cross(Vector(out[m - 2], out[m - 1]), Vector(out[m - 2], in[i])), 0) <= 0) --m;
        out[m++] = in[i];
    }
    int k = m;
    for(int i = n - 2; i >= 0; --i) {
        while(m > k && cmp(cross(Vector(out[m - 2], out[m - 1]), Vector(out[m - 2], in[i])), 0) <= 0) --m;
        out[m++] = in[i];
    }
    if(n > 1) --m;
    return m;
}

double getArea(Point* p, int n) {
    double area = 0.0;
    for(int i = 2; i < n; ++i) {
        area += cross(Vector(p[0], p[i - 1]), Vector(p[0], p[i]));
    }
    return 0.5 * area;
}

int inPolygon(Point o, Point p[], int n) {
    int w = 0;
    for(int i = 0; i < n; ++i) {
        if(onSeg(p[i], p[(i + 1) % n], o)) return -1;//on
        int k = cmp(cross(Vector(p[i], p[(i + 1) % n]), Vector(p[i], o)), 0);
        int d1 = cmp(p[i].y - o.y, 0);
        int d2 = cmp(p[(i + 1) % n].y - o.y, 0);
        if(k > 0 && d1 <= 0 && d2 > 0) ++w;
        if(k < 0 && d2 <= 0 && d1 > 0) --w;
    }
    if(w != 0) return 1;//in
    return 0;//out
}