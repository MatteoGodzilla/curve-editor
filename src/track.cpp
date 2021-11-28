#include "track.h"

Point::Point(float xx, float yy, pType t = CONTROL){
    x = xx;
    y = yy;
    type = t;
}

Track::Track(){
    points = std::vector<Point*>();
}

Track::~Track(){
    for(auto p : points){
        delete p;
    }
}