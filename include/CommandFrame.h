// CommandFrame.h
#ifndef COMMANDFRAME_H
#define COMMANDFRAME_H

#include <wx/wx.h>
#include <libssh/libssh.h>

/**
 * @class CommandFrame
 * @brief A window that allows the user to execute commands on the connected SSH session.
 */
class CommandFrame : public wxFrame
{
public:
    /**
     * @brief Constructor that initializes the command execution window.
     * @param parent Parent window (usually the SSHFrame).
     * @param sshSession An active ssh_session.
     */
    CommandFrame(wxWindow* parent, ssh_session sshSession);

private:
    wxTextCtrl* commandField; ///< Input field for commands
    wxTextCtrl* outputBox;    ///< Displays the command output

    ssh_session session;      ///< Reference to the SSH session

    /**
     * @brief Handles the execution of the entered command over SSH.
     * @param event The button click event.
     */
    void OnExecute(wxCommandEvent& event);
};

#endif // COMMANDFRAME_H