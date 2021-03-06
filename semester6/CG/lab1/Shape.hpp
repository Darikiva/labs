#pragma once

#include <algorithm>
#include <vector>

struct Point
{
    Point() {}
    double x, y;
    explicit Point(int x, int y) : x(x), y(y) {}
    bool operator==(const Point& other) const {
        return this->x == other.x && this->y == other.y;
    }
};

struct Edge
{
    Point p1;
    Point p2;
    void organizeY()
    {
        if (p1.y > p2.y)
        {
            std::swap(p1, p2);
        }
    }
    explicit Edge(Point p1, Point p2) : p1(p1), p2(p2) {}
};

struct Shape
{
    Shape() {}
    std::vector<Edge> edges;
    std::vector<Point> points;
    explicit Shape(std::vector<Point> points): points(points)
    {
        edges.emplace_back(Edge(points[0], points.back()));
        for (int i = 1; i < points.size(); ++i)
        {
            edges.emplace_back(Edge(points[i], points[i - 1]));
        }
    }

    bool isPointInside(const Point& point) {
        int res = 0;
        for (auto& edge: edges) 
        {
            edge.organizeY();
            const Point& p1 = edge.p1;
            const Point& p2 = edge.p2;
            if (p1 == point || p2 == point) return true;
            if (p1.y > point.y || p2.y < point.y) continue;
            double num = (p1.y - p2.y) * point.x + (p2.x - p1.x) * point.y + (p1.x * p2.y - p2.x * p1.y);
            if (num <= 0) ++res;
        }
        return (res % 2 != 0);
    }
};