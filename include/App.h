// App.h
#ifndef APP_H
#define APP_H

#include <wx/wx.h>

// Forward declare your main frame here:
class SSHFrame;

/**
 * @class RouterConfigApp
 * @brief Main application class for initializing and running the wxWidgets application.
 */
class RouterConfigApp : public wxApp
{
public:
    /**
     * @brief Called on application start. Initializes the main window and shows it.
     * @return true if successful.
     */
    virtual bool OnInit() override;
};

#endif // APP_H