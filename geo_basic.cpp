const double eps = 1e-7;
int cmp(double x, double y)
{
    if(fabs(x - y) < eps) return 0;
    return (x < y) ? -1 : 1;
}

struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    friend istream& operator>>(istream& is, Point& p)
    {
        is >> p.x >> p.y;
        return is;
    }
};

struct Vector {
    double x, y;
    Vector(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    Vector(Point s, Point t) : x(t.x - s.x), y(t.y - s.y) {}

    Vector operator+(Vector other)
    {
        return Vector(x + other.x, y + other.y);
    }

    Vector operator-(Vector other)
    {
        return Vector(x - other.x, y - other.y);
    }

    Vector operator*(double k)
    {
        return Vector(x * k, y * k);
    }

    friend Vector operator*(double k, Vector other)
    {
        return other * k;
    }

    friend double dot(Vector lhs, Vector rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    friend double cross(Vector lhs, Vector rhs)
    {
        return lhs.x * rhs.y - rhs.x * lhs.y;
    }

    friend istream& operator>>(istream& is, Vector& v)
    {
        cin >> v.x >> v.y;
        return is;
    }
};

struct Line {
    Point o;
    Vector dir;

    Line(Point x, Point y) : o(x), dir(x, y) {}
    Line(Point _o, Vector _d) : o(_o), dir(_d) {}

    friend Point getCrossPoint(Line lhs, Line rhs)
    {
        assert(cmp(cross(lhs.dir, rhs.dir), 0.0) != 0);
        Vector u(rhs.o, lhs.o);
        double t = cross(rhs.dir, u) / cross(lhs.dir, rhs.dir);
        Vector dt = lhs.dir * t;
        return Point(lhs.o.x + dt.x, lhs.o.y + dt.y);
    }
};

bool sameDir(Vector a, Vector b)
{
    return cmp(dot(a, b), 0) > 0 && cmp(cross(a, b), 0) == 0;
}

bool onSeg(Point a, Point b, Point c)
{
    return c.x >= min(a.x, b.x) && c.y >= min(a.y, b.y) && c.x <= max(a.x, b.x) && c.y <= max(a.y, b.y) &&
    cmp(cross(Vector(c, a), Vector(c, b)), 0) == 0;
}