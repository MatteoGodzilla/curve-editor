#pragma once
#include "wx/wx.h"
#include "wx/vscroll.h"
#include "wx/dcbuffer.h"
#include "trackManager.h"

class TrackRenderer : public wxHVScrolledWindow{
public:
    TrackRenderer() = default;
    ~TrackRenderer() = default;
    TrackRenderer(wxWindow* parent ,const TrackManager* trackman);
    
    wxCoord OnGetRowHeight( size_t row ) const override;
    wxCoord OnGetColumnWidth ( size_t col ) const override;

    void onPaintEvt(wxPaintEvent& e);
    void onDraw(wxDC& dc);
    
    void drawTrack(wxDC& dc, Track* track, wxPosition begin, wxPosition end);
    
private:
    wxWindow* win;
    const TrackManager* tm;
    int trackHeight = 200;
    int width = 100;
    
    wxDECLARE_EVENT_TABLE();
};