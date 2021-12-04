#include "trackRenderer.h"

wxBEGIN_EVENT_TABLE(TrackRenderer,wxHVScrolledWindow)
    EVT_PAINT(TrackRenderer::onPaintEvt)
    EVT_MOTION(TrackRenderer::onMotion)
wxEND_EVENT_TABLE()

TrackRenderer::TrackRenderer(wxWindow* parent, TrackManager& trackman)
    : wxHVScrolledWindow(parent), tm(trackman)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void TrackRenderer::onMotion(wxMouseEvent& e){
    //forward event to trackmanager
    tm.onMotion(e);
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
            if(x % unitSubdivisions == 0){
                pen.SetStyle(wxPENSTYLE_SOLID);
                pen.SetWidth(2);
            } else {
                pen.SetStyle(wxPENSTYLE_SHORT_DASH);
                pen.SetWidth(1);
            }
            dc.SetPen(pen);
            dc.DrawLine(x*columnWidth, baseY, x*columnWidth, baseY+trackHeight);
        }

        //draw curve
        pen.SetColour(128,255,0);
        dc.SetPen(pen);
        int startPixel = begin.GetCol() * columnWidth;
        int endPixel = end.GetCol() * columnWidth;
        for(int x = startPixel; x < endPixel; x++){
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

        //draw points
        brush.SetColour(200,0,0);
        pen.SetColour(200,0,0);
        dc.SetBrush(brush);
        dc.SetPen(pen);
        for(int i = 0; i < track.points.size(); i++){
            const Point& point = track.points[i];
            float startView = (float)(begin.GetCol()) / unitSubdivisions;
            float endView = (float)(end.GetCol()) / unitSubdivisions;

            if(startView <= point.x && point.x < endView){
                dc.DrawCircle(point.x * unitWidth, baseY + (1.0 - point.y) * trackHeight, 5);
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
