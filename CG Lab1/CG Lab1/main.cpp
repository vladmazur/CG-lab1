//
//  main.cpp
//  CG Lab1
//
//  Created by Влад Мазур on 3/24/14.
//  Copyright (c) 2014 Vlad Mazur. All rights reserved.
//

#include <cmath>
#include <iostream>
using namespace::std;

struct Point {
    double x;
    double y;
    
    Point() {x=0; y=0;}
    
    Point(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    
    Point operator -(const Point & p)
    {
        Point result;
        result.x = x-p.x;
        result.y = y-p.y;
        return result;
    }
    
    Point operator +(const Point & p)
    {
        Point result;
        result.x = x+p.x;
        result.y = y+p.y;
        return result;
    }
    
    Point operator *(const float k)
    {
        Point result;
        result.x = k*x;
        result.y = k*y;
        return result;
    }
    
    friend std::ostream& operator<<(std::ostream &os, const Point &p)
    {
        os << "Point(" << p.x << "," << p.y << ")";
        return os;
    }
};

struct Interval {
    Point start;
    Point end;
    
    friend std::ostream& operator<<(std::ostream &os, const Interval &l)
    {
        os << "Interval(" << l.start << "," << l.end << ")";
        return os;
    }
    
    Interval(Point start, Point end)
    {
        this->start = start;
        this->end = end;
    }
};

bool intersection(Point start1, Point end1, Point start2, Point end2, Point * out_intersection)
{
    Point dir1 = end1 - start1;
    Point dir2 = end2 - start2;
    
    //считаем уравнения прямых проходящих через отрезки
    float a1 = -dir1.y;
    float b1 = +dir1.x;
    float d1 = -(a1*start1.x + b1*start1.y);
    
    float a2 = -dir2.y;
    float b2 = +dir2.x;
    float d2 = -(a2*start2.x + b2*start2.y);
    
    //подставляем концы отрезков, для выяснения в каких полуплоскотях они
    float seg1_line2_start = a2*start1.x + b2*start1.y + d2;
    float seg1_line2_end = a2*end1.x + b2*end1.y + d2;
    
    float seg2_line1_start = a1*start2.x + b1*start2.y + d1;
    float seg2_line1_end = a1*end2.x + b1*end2.y + d1;
    
    //если концы одного отрезка имеют один знак, значит он в одной полуплоскости и пересечения нет.
    if (seg1_line2_start * seg1_line2_end >= 0 || seg2_line1_start * seg2_line1_end >= 0)
        return false;
    
    float u = seg1_line2_start / (seg1_line2_start - seg1_line2_end);
    *out_intersection =  start1 + dir1 * u;
    
    return true;
}

bool intersection(Interval one, Interval two, Point * out_intersection)
{
    return intersection(one.start, one.end, two.start, two.end, out_intersection);
}

#warning add angle calculation



void testForIntersection(Interval one, Interval two, bool expectedResult)
{
    Point out;
    cout << one << " and " << two << "\n";
    bool res = intersection(one, two, &out);
    if ( res == expectedResult)
        cout << "Test OK\n\n";
    else
        cout << "Test FAIL\n\n";
    if(res)
        cout << "Intersection point:" << out <<"\n\n";
}

void test()
{
    testForIntersection(Interval(Point(2,2), Point(5,5)),
                        Interval(Point(0,0), Point(7,7)),
                        false);
    testForIntersection(Interval(Point(2,2), Point(5,5)),
                        Interval(Point(2,5), Point(5,2)),
                        true);
    
    // точка:
    testForIntersection(Interval(Point(2,2), Point(2,2)),
                        Interval(Point(0,0), Point(7,7)),
                        false);
    
    // паралельные прямые:
    testForIntersection(Interval(Point(2,2), Point(2,5)),
                        Interval(Point(3,3), Point(3,6)),
                        false);
    
    // один входит в другой:
    testForIntersection(Interval(Point(2,2), Point(5,5)),
                        Interval(Point(3,3), Point(4,4)),
                        false);
}

int main(int argc, const char * argv[])
{
    test();
}

