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
    ~Track();
    int id;
    std::vector<Point*> points;
};