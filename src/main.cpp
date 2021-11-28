#include <vector>
#include "wx/wx.h"
#include "trackManager.h"
#include "trackRenderer.h"
#include "mainWin.h"

class MainApp : public wxApp{
public:
    virtual bool OnInit() override {
        tm = TrackManager();
        
        win = new MainWin(&tm);
        win->Show();

        return true;
    }
private:
    MainWin* win;
    TrackManager tm;
    TrackRenderer tr;
};

wxIMPLEMENT_APP(MainApp);

