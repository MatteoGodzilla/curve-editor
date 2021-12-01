#include "trackManager.h"

TrackManager::TrackManager(){
    tracks = std::vector<Track>();
    Track t = Track(0);
    t.points.emplace_back(0,0.5,ptSINE);
    t.points.emplace_back(0.5,0.75,ptCONTROL);
    t.points.emplace_back(2,0.5,ptNONE);
    tracks.push_back(t);
}

int TrackManager::getMaximumWidth() const{
    int m = 1;
    for(auto& t : tracks){
        m = std::max(m, (int)std::ceil(t.GetLastPointX()));
    }
    return m;
}