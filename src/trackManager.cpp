#include "trackManager.h"

TrackManager::TrackManager(){
    tracks = std::vector<Track*>();
    tracks.push_back(new Track(0));
    tracks.push_back(new Track(1));
    tracks.push_back(new Track(2));
}

TrackManager::~TrackManager(){
    for(auto t : tracks){
        t->~Track();
        delete t;
    }
}