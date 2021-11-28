#include "trackRenderer.h"

TrackRenderer::TrackRenderer(const TrackManager* trackman){
    tm = trackman;
}

void TrackRenderer::onDraw(wxDC& dc){
    dc.Clear();

    for(size_t i = 0; i < tm->tracks.size(); i++){
        drawTrack(dc,tm->tracks[i],i);
    }
}

void TrackRenderer::drawTrack(wxDC& dc, Track* track, size_t index){
    wxPen pen = dc.GetPen();
    wxBrush brush = dc.GetBrush();

    wxSize dims = dc.GetSize();

    pen.SetColour(31,31,31);
    pen.SetWidth(3);

    dc.SetPen(pen);

    dc.DrawRectangle(0,40*index,dims.x,40*(index+1));
}