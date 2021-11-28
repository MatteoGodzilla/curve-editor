#include "trackRenderer.h"

wxBEGIN_EVENT_TABLE(TrackRenderer,wxHVScrolledWindow)
    EVT_PAINT(TrackRenderer::onPaintEvt)
wxEND_EVENT_TABLE()

TrackRenderer::TrackRenderer(wxWindow* parent, const TrackManager* trackman)
    : wxHVScrolledWindow(parent)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    tm = trackman;
}

void TrackRenderer::onPaintEvt(wxPaintEvent& e){
    wxBufferedPaintDC dc(this);
    SetRowCount(tm->tracks.size());
    SetColumnCount(4);
    
    PrepareDC(dc);
    onDraw(dc);
}

void TrackRenderer::onDraw(wxDC& dc){
    dc.Clear();

    wxPosition begin = GetVisibleBegin();
    wxPosition end = GetVisibleEnd();

    for(auto t : tm->tracks){
        drawTrack(dc,t,begin,end);
    }
}

void TrackRenderer::drawTrack(wxDC& dc, Track* track, wxPosition begin, wxPosition end){
    //skip rendering if track is off screen
    if(track->id >= begin.GetRow() && track->id < end.GetRow()){
        int baseY = track->id * trackHeight;
        int baseX = begin.GetCol() * width;
        int w = (end.GetCol() - begin.GetCol()) * width;
        int h = (end.GetRow() - begin.GetRow()) * trackHeight;
        
        wxPen pen = dc.GetPen();
        wxBrush brush = dc.GetBrush();

        pen.SetColour(31,31,31);
        pen.SetStyle(wxPENSTYLE_SHORT_DASH);
        pen.SetWidth(1);
        dc.SetPen(pen);
        
        //base
        //dc.DrawRectangle(begin.GetCol() * width, baseY, width * 3, height);
        for(int sub = 0; sub < 4; sub++){
            int subHeight = trackHeight / 4;
            dc.DrawLine(baseX,baseY + subHeight*sub, baseX + w, baseY + subHeight*sub);
        }

        //draw tick marks
        for(int x = begin.GetCol(); x <= end.GetCol(); x++){
            dc.DrawLine(x*width,baseY,x*width,baseY+trackHeight);
        }

        //separator
        pen.SetWidth(3);
        pen.SetStyle(wxPENSTYLE_SOLID);
        dc.SetPen(pen);

        dc.DrawLine(baseX,baseY, baseX + w, baseY);
        dc.DrawLine(baseX,baseY + trackHeight, baseX + w, baseY + trackHeight);
    }
}

wxCoord TrackRenderer::OnGetRowHeight( size_t row ) const {
    return wxCoord(trackHeight);
}

wxCoord TrackRenderer::OnGetColumnWidth ( size_t col ) const {
    return wxCoord(width);
}
