#include "trackManager.h"

TrackManager::TrackManager(){
    tracks = std::vector<Track*>();
    tracks.push_back(new Track());
}

TrackManager::~TrackManager(){
    for(auto t : tracks){
        t->~Track();
        delete t;
    }
}