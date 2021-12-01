#pragma once
#include <cmath>
#include "wx/wx.h"
#include "wx/vscroll.h"
#include "wx/dcbuffer.h"
#include "trackManager.h"

class TrackRenderer : public wxHVScrolledWindow{
public:
    TrackRenderer(wxWindow* parent, const TrackManager& trackman);
    
    wxCoord OnGetRowHeight( size_t row ) const override;
    wxCoord OnGetColumnWidth ( size_t col ) const override;

    void onPaintEvt(wxPaintEvent& e);
    void onDraw(wxDC& dc);
    
    void drawTrack(wxDC& dc, const Track& track, wxPosition begin, wxPosition end);
    
private:
    wxWindow* win;
    const TrackManager& tm;
    int trackHeight = 300;
    int unitWidth = 300;
    int unitSubdivisions = 4;
    
    wxDECLARE_EVENT_TABLE();
};