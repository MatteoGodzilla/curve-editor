#pragma once
#include <vector>
#include <algorithm>
#include <cmath>
#include "track.h"


class TrackManager{
public:
    TrackManager();
    int getMaximumWidth() const;
    std::vector<Track> tracks;
};