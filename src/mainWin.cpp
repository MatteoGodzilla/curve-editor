#include "mainWin.h"

MainWin::MainWin(TrackManager& trackman)
    : wxFrame(nullptr,wxID_ANY,"Curve Editor 0.1.0",wxDefaultPosition,wxSize(800,600))
{
    new TrackRenderer(this, trackman);

    status = CreateStatusBar();
    status->SetStatusText("Statusbar is working");
    status ->Show();

    wxMenuBar* menubar = new wxMenuBar();

    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(wxID_EXIT,"Exit", "Exit Curve editor");
    menubar->Append(fileMenu,"File");

    SetMenuBar(menubar);
}