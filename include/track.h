#pragma once
#include <vector>

enum pType{
    CONTROL,
    LINEAR,
    BEZIER,
    SINE
};

class Point{
public:
    Point(float xx, float yy, pType con);
    float x;
    float y;
    pType type = CONTROL;
};

class Track{
public:
    Track();
    Track(int ID);
    ~Track();
    int id = 0;
    std::vector<Point*> points;
};