//
//  main.cpp
//  CG Lab1
//
//  Created by Влад Мазур on 3/24/14.
//  Copyright (c) 2014 Vlad Mazur. All rights reserved.
//

#include "CG.h"

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
    
    // -45 deg is 315 deg:
    angle(Interval(Point(2,2), Point(5,5)),
          Interval(Point(0,0), Point(3,0)));
    //
    angle(Interval(Point(2,2), Point(5,5)),
          Interval(Point(-2,2), Point(-5,5)));
}

int main(int argc, const char * argv[])
{
    test();
}

