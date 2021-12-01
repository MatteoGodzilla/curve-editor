#pragma once
#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "trackManager.h"
#include "trackRenderer.h"

class MainWin : public wxFrame{
public:
    MainWin(const TrackManager& trackMan);
private:
    wxStatusBar* status;
};