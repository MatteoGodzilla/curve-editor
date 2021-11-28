#include "mainWin.h"

wxBEGIN_EVENT_TABLE(MainWin,wxFrame)
    EVT_PAINT(MainWin::onPaintEvt)
wxEND_EVENT_TABLE()

MainWin::MainWin(const TrackManager* trackman)
    : wxFrame(nullptr,wxID_ANY,"Curve Editor 0.1.0",wxDefaultPosition,wxSize(800,600))
{
    tm = trackman;
    renderer = TrackRenderer(trackman);

    status = CreateStatusBar();
    status->SetStatusText("Statusbar is working");
    status ->Show();

    wxMenuBar* menubar = new wxMenuBar();

    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(wxID_EXIT,"Exit", "Exit Curve editor");
    menubar->Append(fileMenu,"File");

    SetMenuBar(menubar);

    //for paint device context
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void MainWin::onPaintEvt(wxPaintEvent& e){
    wxBufferedPaintDC dc(this);
    renderer.onDraw(dc);
}