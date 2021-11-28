#include <vector>
#include "wx/wx.h"
#include "trackManager.h"
#include "trackRenderer.h"
#include "mainWin.h"

class MainApp : public wxApp{
public:
    virtual bool OnInit() override {
        win = new MainWin(&tm);
        win->Show();

        return true;
    }
private:
    MainWin* win;
    TrackManager tm = TrackManager();
    TrackRenderer tr;
};

wxIMPLEMENT_APP(MainApp);

