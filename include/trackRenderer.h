#pragma once

#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "trackManager.h"

class TrackRenderer{
public:
    TrackRenderer() = default;
    TrackRenderer(const TrackManager* trackman);
    void onDraw(wxDC& dc);
    ~TrackRenderer() = default;
    void drawTrack(wxDC& dc, Track* track, size_t index);
private:
    wxWindow* win;
    const TrackManager* tm;
    int height = 40;
};