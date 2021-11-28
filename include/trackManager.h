#pragma once
#include <vector>
#include "track.h"

class TrackManager{
public:
    TrackManager();
    ~TrackManager();
    std::vector<Track*> tracks;
};