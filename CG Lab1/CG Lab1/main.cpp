//
//  main.cpp
//  CG Lab1
//
//  Created by Влад Мазур on 3/24/14.
//  Copyright (c) 2014 Vlad Mazur. All rights reserved.
//

struct Point {
    double x;
    double y;
    
    Point() {x = 0; y=0;}
    
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
};

#include <cmath>

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

#include <iostream>

int main(int argc, const char * argv[])
{
    Point out;
    std::cout << intersection(Point(2,2), Point(5,5), Point(0,0), Point(7,7), &out) << "\n";
    std::cout << intersection(Point(2,2), Point(5,5), Point(2,5), Point(5,2), &out) << "\n";
}

