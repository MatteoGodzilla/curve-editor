#pragma once
#include <vector>
#include <cmath>

#define INVALID_HEIGHT (-1.0f)

enum pType{
    ptCONTROL,
    ptNONE,
    ptLINEAR,
    ptBEZIER,
    ptSINE
};

class Point{
public:
    Point(float xx, float yy, pType con);
    float x;
    float y;
    pType type = ptCONTROL;
};

class Track{
public:
    Track();
    Track(int ID);
    float Evaluate(float sampleX) const;
    float GetLastPointX() const;
    ~Track();
    int id = 0;
    std::vector<Point> points;
};