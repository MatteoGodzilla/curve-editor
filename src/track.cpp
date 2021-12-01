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
    for(size_t i = 0; i < points.size(); i++){
        if(points[i].x <= sampleX && points[i].type != ptCONTROL){
            //first one that is behind the sampleX
            switch(points[i].type){
                case ptLINEAR: 
                    if(i + 1 < points.size()){
                        //linear requires the end point to exist
                        return evaluateLinear(sampleX, points[i], points[i+1]);
                    }
                case ptBEZIER:
                    if(i + 3 < points.size() && points[i+1].type == ptCONTROL && points[i+2] .type == ptCONTROL){
                        //bezier requires 3 points and first two must be control
                    }
                case ptSINE:
                    if(i + 2 < points.size() && points[i+1].type == ptCONTROL){
                        //sine requires 2 points and first must be control
                        return evaluateSine(sampleX, points[i], points[i+1]);
                    }
                default: return INVALID_HEIGHT;
            }
        }
    }
    return INVALID_HEIGHT;
}

float Track::GetLastPointX() const{
    return points.back().x;
}

Track::~Track(){
    points.clear();
}