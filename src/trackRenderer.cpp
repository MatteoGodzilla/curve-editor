#include "trackRenderer.h"

wxBEGIN_EVENT_TABLE(TrackRenderer,wxHVScrolledWindow)
    EVT_PAINT(TrackRenderer::onPaintEvt)
wxEND_EVENT_TABLE()

TrackRenderer::TrackRenderer(wxWindow* parent, const TrackManager& trackman)
    : wxHVScrolledWindow(parent), tm(trackman)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void TrackRenderer::onPaintEvt(wxPaintEvent& e){
    wxBufferedPaintDC dc(this);
    SetRowCount(tm.tracks.size());
    SetColumnCount((tm.getMaximumWidth() + 1) * unitSubdivisions);
    
    PrepareDC(dc);
    onDraw(dc);
}

void TrackRenderer::onDraw(wxDC& dc){
    dc.Clear();

    wxPosition begin = GetVisibleBegin();
    wxPosition end = GetVisibleEnd();

    for(auto& t : tm.tracks){
        drawTrack(dc,t,begin,end);
    }
}

void TrackRenderer::drawTrack(wxDC& dc, const Track& track, wxPosition begin, wxPosition end){
    //skip rendering if track is off screen
    if(track.id >= begin.GetRow() && track.id < end.GetRow()){
        int columnWidth = (unitWidth / unitSubdivisions);
        int baseY = track.id * trackHeight;
        int baseX = begin.GetCol() * columnWidth;
        int w = (end.GetCol() - begin.GetCol()) * columnWidth;
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
            dc.DrawLine(x*columnWidth, baseY, x*columnWidth, baseY+trackHeight);
        }

        //draw curve
        pen.SetColour(128,255,0);
        dc.SetPen(pen);
        int s = begin.GetCol() * columnWidth;
        int e = end.GetCol() * columnWidth;
        for(int x = s; x < e; x++){
            //go through all pixels
            float sampleX = (float)(x) / unitWidth;
            float sampleHeight = track.Evaluate(sampleX);
            int y = baseY + round((float)trackHeight * (1.0f - sampleHeight));
            if(sampleHeight != INVALID_HEIGHT){
                dc.DrawPoint(x,y);
                dc.DrawPoint(x - 1, y);
                dc.DrawPoint(x + 1, y);
                dc.DrawPoint(x, y - 1);
                dc.DrawPoint(x, y + 1);
            }
        }

        //separator
        pen.SetColour(31,31,31);
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
    return wxCoord(unitWidth / unitSubdivisions);
}
