#include <iostream>
#include "Shape.hpp"

using namespace std;

int main() {
    Point p1(3, 2), p2(4, 4), p3(5, 2), p4(6, 4), p5(8, 2), p6(7, 6), p7(4, 8), p8(2, 4);
    Shape shape({p1, p2, p3, p4, p5, p6, p7, p8});
    cout << shape.isPointInside(Point(3, 2)) << endl;
}