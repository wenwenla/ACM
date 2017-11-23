struct Circle {
    const double PI = 3.141592653589793;
    Point c;
    double r;

    Circle(Point _c, double _r) : c(_c), r(_r) {}
    Circle(Point x, Point y, Point z) {
        Point cxy(0.5 * (x.x + y.x), 0.5 * (x.y + y.y));
        Point cyz(0.5 * (y.x + z.x), 0.5 * (y.y + z.y));
        Vector xy(x, y), yz(y, z);
        Vector nxy(-xy.y, xy.x), nyz(-yz.y, yz.x);
        c = getCrossPoint(Line(cxy, nxy), Line(cyz, nyz));
        r = Vector(c, x).length();
    }

    double area() const {
        return PI * sqr(r);
    }

    friend void getCrossPoint(Circle a, Circle b, Point* ps, int& cnt) {
        if(a.c == b.c) return;
        int cdis2 = Vector(a.c, b.c).len2();
        int tp1 = cmp(cdis2, sqr(a.r + b.r));
        int tp2 = cmp(cdis2, sqr(a.r - b.r));
        cnt = 0;
        if(tp1 == 1 || tp2 == -1) return;
        Vector ab(a.c, b.c);
        double cost = 0.5 * (sqr(a.r) + ab.len2() - sqr(b.r)) / (ab.length() * sqr(a.r));
        double sint = sqrt(1 - sqr(cost));
        Vector v1 = rotate(ab, cost, sint).norm();
        ps[cnt++] = Point(v1.x * a.r, v1.y * a.r);
        if(tp1 == 0 || tp2 == 0) return;
        Vector v2 = rotate(ab, cost, -sint).norm();
        ps[cnt++] = Point(v2.x * a.r, v2.y * a.r);
    }
};