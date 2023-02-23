#include <iostream>
#include <cmath>

/*
    0----------------------------> x
    | R|  |  |  |  |  |  |  |
    --------------------------
    |  |  |  |  |  |  |  |  |
    --------------------------
    |  |  |  |  |  |  |  |  |
    --------------------------
    |  |  |  |  |  |  |  |  |
    --------------------------
    |  |  |  |  |  |  |  |  |
    --------------------------
    |
    \/ 
    y

    The board is represented in decart coordinates.
    Each square is 1x1. Square (x,y) has 4 points (x,y), (x+1,y), (x,y-1), (x+1,y-1) and center (x-0.5,y-0.5).
    The origin position of the robot is in the square (0, 0).
*/

class Point {
private:
    double _x, _y; // immutable
public:
    Point() {
        this->_x = 0;
        this->_y = 0;
    }
    Point(double x, double y) {
        this->_x = x;
        this->_y = y;
    }
    double x() {
        return _x;
    }
    double y() {
        return _y;
    }
};

class LineSegment {
private:
    Point p1, p2;
public:
    LineSegment() {
        this->p1 = Point(0, 0);
        this->p2 = Point(0, 0);
    }
    LineSegment(Point p1, Point p2) {
        this->p1 = p1;
        this->p2 = p2;
    }

    Point get_p1() {
        return p1;
    }

    Point get_p2() {
        return p2;
    }

    // Given three collinear points p, q, r, the function checks if
    // point q lies on line segment 'pr'
    bool on_segment(Point p, Point q, Point r)
    {
        if (q.x() <= std::max(p.x(), r.x()) && q.x() >= std::min(p.x(), r.x()) &&
            q.y() <= std::max(p.y(), r.y()) && q.y() >= std::min(p.y(), r.y()))
        return true;
    
        return false;
    }
    
    // To find orientation of ordered triplet (p, q, r).
    // The function returns following values
    // 0 --> p, q and r are collinear
    // 1 --> Clockwise
    // 2 --> Counterclockwise
    int orientation(Point p, Point q, Point r)
    {
        // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
        // for details of below formula.
        int val = (q.y() - p.y()) * (r.x() - q.x()) -
                (q.x() - p.x()) * (r.y() - q.y());
    
        if (val == 0) return 0;  // collinear
    
        return (val > 0) ? 1: 2; // clock or counterclock wise
    }
    
    // The main function that returns true if line segment 'p1q1'
    // and 'p2q2' intersect.
    bool do_intersect(LineSegment other) {
        Point p1 = this->p1, q1 = this->p2, p2 = other.get_p1(), q2 = other.get_p2();

        // Find the four orientations needed for general and
        // special cases
        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);
    
        // General case
        if (o1 != o2 && o3 != o4)
            return true;
    
        // Special Cases
        // p1, q1 and p2 are collinear and p2 lies on segment p1q1
        if (o1 == 0 && on_segment(p1, p2, q1)) return true;
    
        // p1, q1 and q2 are collinear and q2 lies on segment p1q1
        if (o2 == 0 && on_segment(p1, q2, q1)) return true;
    
        // p2, q2 and p1 are collinear and p1 lies on segment p2q2
        if (o3 == 0 && on_segment(p2, p1, q2)) return true;
    
        // p2, q2 and q1 are collinear and q1 lies on segment p2q2
        if (o4 == 0 && on_segment(p2, q1, q2)) return true;
    
        return false; // Doesn't fall in any of the above cases
    }

    Point get_intersection(LineSegment other) {
        if (!do_intersect(other)) {
            // TODO: throw exception
            return Point(-99999, -99999);
        }

        // first represented as a1x + b1y = c1
        double a1 = this->p2.y() - this->p1.y();
        double b1 = this->p1.x() - this->p2.x();
        double c1 = a1*(this->p1.x()) + b1*(this->p1.y());
    
        // Line CD represented as a2x + b2y = c2
        double a2 = other.get_p2().y() - other.get_p1().y();
        double b2 = other.get_p1().x() - other.get_p2().x();
        double c2 = a2*(other.get_p1().x())+ b2*(other.get_p1().y());
    
        double determinant = a1*b2 - a2*b1;
    
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        return Point(x, y);
    }
};

class Robot {
private:
    Point position;
public:
    Robot() {
        this->position = Point(0, 0);
    }
    Robot(Point position) {
        this->position = position;
    }
    Point getPosition() {
        return position;
    }
    void move(Point newPosition) {
        this->position = newPosition;
    }
};

int main() {
    // determine 2 line segments
    LineSegment ls1 = LineSegment(Point(0, 1), Point(0, -2));
    LineSegment ls2 = LineSegment(Point(-2, 0), Point(1, 0));
    Point intersection = ls1.get_intersection(ls2);
    std::cout << intersection.x() << " " << intersection.y() << std::endl;
}