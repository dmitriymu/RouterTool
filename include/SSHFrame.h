// SSHFrame.h
#ifndef SSHFRAME_H
#define SSHFRAME_H

#include <wx/wx.h>
#include <libssh/libssh.h>

// Forward declarations
class CommandFrame;

/**
 * @class SSHFrame
 * @brief The main window containing IP/User/Pass inputs, and buttons for MAC Generator, Notes, Connect, Disconnect, and Exit.
 */
class SSHFrame : public wxFrame
{
public:
    /**
     * @brief Constructs the SSHFrame window.
     * @param title The title of the frame.
     */
    SSHFrame(const wxString& title);

    /**
     * @brief Destructor. Cleans up SSH session if still active.
     */
    ~SSHFrame();

private:
    // Widgets
    wxTextCtrl* ipField;   ///< Text field for IP address
    wxTextCtrl* userField; ///< Text field for username
    wxTextCtrl* passField; ///< Text field for password

    ssh_session session;   ///< SSH session handle
    CommandFrame* commandWindow; ///< Pointer to the command execution window

    // Event handlers
    void OnMacGenerator(wxCommandEvent& event);
    void OnOpenNotes(wxCommandEvent& event);
    void OnConnect(wxCommandEvent& event);
    void OnDisconnect(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
};

#endif // SSHFRAME_H