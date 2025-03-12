// App.cpp
#include "App.h"
#include "SSHFrame.h" // We need the definition of SSHFrame to create it

wxIMPLEMENT_APP(RouterConfigApp);

bool RouterConfigApp::OnInit()
{
    // Create main frame and display it
    SSHFrame* frame = new SSHFrame("Router Configuration");
    frame->Show(true);
    return true; 
}