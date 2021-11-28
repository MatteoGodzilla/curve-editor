#pragma once
#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "trackManager.h"
#include "trackRenderer.h"

class MainWin : public wxFrame{
public:
    MainWin(const TrackManager* trackMan);
    void onPaintEvt(wxPaintEvent& e);
private:
    wxStatusBar* status;
    const TrackManager* tm;
    TrackRenderer renderer;

    wxDECLARE_EVENT_TABLE();
};