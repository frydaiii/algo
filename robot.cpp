#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

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
    double _x, _y; 
public:
    Point() : _x(0), _y(0) {}
    Point(double x, double y) : _x(x), _y(y) {}
    double x() {
        return _x;
    }
    double y() {
        return _y;
    }
    void new_pos(double x, double y) {
        this->_x = x;
        this->_y = y;
    }

    // this function used for sorting points in a vector
    static bool compare(Point p1, Point p2) {
        if (p1.x() < p2.x()) {
            return true;
        } else if (p1.x() == p2.x()) {
            return p1.y() < p2.y();
        } else {
            return false;
        }
    }
};

class LineSegment {
private:
    Point p1, p2;
public:
    LineSegment() : p1(Point(0,0)), p2(Point(0,0)) {}
    LineSegment(Point _p1, Point _p2) : p1(_p1), p2(_p2) {}

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

    /*
        find the unit square that contains the segment. If possible, return top left Point of that square.
        If not return error.
    */
    Point unit_square_contain() {
        return Point(std::min(std::floor(p1.x()), std::floor(p2.x())), std::max(std::ceil(p1.y()), std::ceil(p2.y()))); // return top left point
    }
};

class Board {
private:
    Point robot;
    int dimension;
    std::vector<std::vector<int>> board; // board (x, y) is a square with top left point is (-y, x)
public:
    Board() : robot(Point(0.5, 0.5)), dimension(0), board(dimension, std::vector<int>(dimension, 0)) {}
    Board(int n) : robot(Point(0.5, 0.5)), dimension(n), board(dimension, std::vector<int>(dimension)) {}

    // integer coordinate to index of board
    std::pair<int, int> coordinate_to_index(Point p) {
        // TODO handle exception
        return std::make_pair(-p.y(), p.x());
    }

    // index of board to integer coordinate
    Point index_to_coordinate(std::pair<int, int> index) {
        return Point(index.second, -index.first);
    }

    void move_robot(int i, int j) {
        Point p = index_to_coordinate(std::make_pair(i, j));
        this->robot.new_pos(p.x() + 0.5, p.y() - 0.5);
    }

    void move_robot_and_draw(int _i, int _j) {
        Point p = index_to_coordinate(std::make_pair(_i, _j)), dest_square_center(p.x() + 0.5, p.y() - 0.5);
        LineSegment line(robot, dest_square_center);
        std::vector<LineSegment> unit_lines;
        for (int i = 0; i < this->dimension; i++) {
            LineSegment v(Point(i, 0), Point(i, this->dimension)), h(Point(0, -i), Point(this->dimension, -i));
            unit_lines.push_back(v);
            unit_lines.push_back(h);
        }

        // cut the line into segments
        std::vector<Point> intersections;
        intersections.push_back(this->robot);
        for (LineSegment l : unit_lines) {
            if (line.do_intersect(l)) {
                intersections.push_back(line.get_intersection(l));
            }
        }
        move_robot(_i, _j);
        intersections.push_back(this->robot);

        // sort the intersections
        std::sort(intersections.begin(), intersections.end(), Point::compare);

        // iterate through the intersections and draw
        for (std::vector<Point>::iterator it = intersections.begin() + 1; it != intersections.end(); it++) {
            Point p1 = *(it - 1), p2 = *it;
            LineSegment l(p1, p2);
            Point square = l.unit_square_contain();
            std::pair<int, int> index = coordinate_to_index(square);
            this->board[index.first][index.second] = 1;
        }
    }

    void print_board() {
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                std::cout << this->board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};  

int main() {
    Board board(5);
    board.move_robot(1, 1);
    board.move_robot_and_draw(3, 3);
    board.move_robot_and_draw(2, 3);
    board.print_board();
}