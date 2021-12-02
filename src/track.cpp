#include "track.h"

Point::Point(float xx, float yy, pType t = ptCONTROL){
    x = xx;
    y = yy;
    type = t;
}

Track::Track(int ID){
    id = ID;
    points = std::vector<Point>();
}

Track::Track(){
    points = std::vector<Point>();
}

float evaluateLinear(float sampleX, const Point& start, const Point& end){
    return start.y + (end.y - start.y) * (sampleX - start.x) / (end.x - start.x);
}

float evaluateBezier(float sampleX, const Point& s, const Point& c1, const Point& c2, const Point& e){
    float t = (sampleX - s.x) / (e.x - s.x);

    return INVALID_HEIGHT;
}

float evaluateSine(float sampleX, const Point& start, const Point& c){
    float amplitude = c.y - start.y;
    float period = (c.x - start.x) * 4;
    return start.y + amplitude * sin((sampleX - start.x) / period * 2 * M_PI);
}

float Track::Evaluate(float sampleX) const{
    //these indices ignore control points by design    
    int pointIndexBeforeSample = -1;

    for(size_t i = 0; i < points.size(); i++){
        if(points[i].type != ptCONTROL){
            if(points[i].x <= sampleX) pointIndexBeforeSample = i;
            else if(points[i].x > sampleX) break; 
        }
    }

    int start = pointIndexBeforeSample;
    switch(points[start].type){
        case ptNONE: return INVALID_HEIGHT;
        case ptLINEAR: return evaluateLinear(sampleX, points[start], points[start+1]);
        case ptBEZIER: return INVALID_HEIGHT;
        case ptSINE: return evaluateSine(sampleX, points[start], points[start+1]);
    }
    return INVALID_HEIGHT;
}

float Track::GetLastPointX() const{
    return points.back().x;
}

Track::~Track(){
    points.clear();
}