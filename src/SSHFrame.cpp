// SSHFrame.cpp
#include "SSHFrame.h"

#include <wx/button.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>

#include "CommandFrame.h"
#include "MacGeneratorFrame.h"
#include "NotesFrame.h"

/**
 * @brief Constructs the SSHFrame window.
 */
SSHFrame::SSHFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 250)),
      session(nullptr),
      commandWindow(nullptr)
{
    // Main sizer for the window
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Text fields for IP, Username, Password
    ipField = new wxTextCtrl(this, wxID_ANY, "192.168.8.1", wxDefaultPosition, wxSize(250, 30));
    userField = new wxTextCtrl(this, wxID_ANY, "root", wxDefaultPosition, wxSize(250, 30));
    passField = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(250, 30), wxTE_PASSWORD);

    // Buttons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* macGenBtn      = new wxButton(this, wxID_ANY, "MAC Generator");
    wxButton* notesBtn       = new wxButton(this, wxID_ANY, "Notes");
    wxButton* connectBtn     = new wxButton(this, wxID_ANY, "Connect");
    wxButton* disconnectBtn  = new wxButton(this, wxID_ANY, "Disconnect");
    wxButton* exitBtn        = new wxButton(this, wxID_EXIT, "Exit");

    // Add buttons to the buttonSizer
    buttonSizer->Add(macGenBtn,     0, wxRIGHT | wxLEFT, 15);
    buttonSizer->Add(notesBtn,      0, wxRIGHT | wxLEFT, 15);
    buttonSizer->Add(connectBtn,    0, wxRIGHT | wxLEFT, 15);
    buttonSizer->Add(disconnectBtn, 0, wxRIGHT | wxLEFT, 15);
    buttonSizer->Add(exitBtn,       0, wxRIGHT | wxLEFT, 15);

    // Add everything to the main sizer
    sizer->Add(ipField,    0, wxEXPAND | wxALL, 10);
    sizer->Add(userField,  0, wxEXPAND | wxALL, 10);
    sizer->Add(passField,  0, wxEXPAND | wxALL, 10);
    sizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(sizer);

    // Bind events
    macGenBtn->Bind(wxEVT_BUTTON, &SSHFrame::OnMacGenerator,    this);
    notesBtn->Bind(wxEVT_BUTTON,  &SSHFrame::OnOpenNotes,       this);
    connectBtn->Bind(wxEVT_BUTTON, &SSHFrame::OnConnect,        this);
    disconnectBtn->Bind(wxEVT_BUTTON, &SSHFrame::OnDisconnect,  this);
    exitBtn->Bind(wxEVT_BUTTON,   &SSHFrame::OnExit,            this);
}

/**
 * @brief Destructor. Ensures the session is freed.
 */
SSHFrame::~SSHFrame()
{
    if (session)
    {
        ssh_disconnect(session);
        ssh_free(session);
        session = nullptr;
    }
}

/**
 * @brief Launches the MAC Generator window.
 */
void SSHFrame::OnMacGenerator(wxCommandEvent& WXUNUSED(event))
{
    MacGeneratorFrame* macFrame = new MacGeneratorFrame();
    macFrame->Show(true);
}

/**
 * @brief Launches the Notes window.
 */
void SSHFrame::OnOpenNotes(wxCommandEvent& WXUNUSED(event))
{
    NotesFrame* notesFrame = new NotesFrame();
    notesFrame->Show(true);
}

/**
 * @brief Creates an SSH session, connects, and authenticates.
 */
void SSHFrame::OnConnect(wxCommandEvent& WXUNUSED(event))
{
    wxString ip   = ipField->GetValue();
    wxString user = userField->GetValue();
    wxString pass = passField->GetValue();

    session = ssh_new();
    if (session == nullptr)
    {
        wxMessageBox("Error: Unable to create SSH session.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    ssh_options_set(session, SSH_OPTIONS_HOST, ip.mb_str());
    ssh_options_set(session, SSH_OPTIONS_USER, user.mb_str());

    if (ssh_connect(session) != SSH_OK)
    {
        wxMessageBox("SSH Connection failed: " + wxString(ssh_get_error(session)), "Error", wxOK | wxICON_ERROR);
        ssh_free(session);
        session = nullptr;
        return;
    }

    if (ssh_userauth_password(session, user.mb_str(), pass.mb_str()) != SSH_AUTH_SUCCESS)
    {
        wxMessageBox("SSH Authentication failed!", "Error", wxOK | wxICON_ERROR);
        ssh_disconnect(session);
        ssh_free(session);
        session = nullptr;
        return;
    }

    wxMessageBox("Connected to Router!", "Success", wxOK | wxICON_INFORMATION);

    // Open the command window
    commandWindow = new CommandFrame(this, session);
    commandWindow->Show(true);
}

/**
 * @brief Disconnects SSH session and cleans up.
 */
void SSHFrame::OnDisconnect(wxCommandEvent& WXUNUSED(event))
{
    // Close command window if open
    if (commandWindow)
    {
        commandWindow->Close(true);
        commandWindow = nullptr;
    }

    // Disconnect and free the session if it exists
    if (session)
    {
        ssh_disconnect(session);
        ssh_free(session);
        session = nullptr;
        wxMessageBox("Disconnected from Router.", "Info", wxOK | wxICON_INFORMATION);
    }
}

/**
 * @brief Closes the application.
 */
void SSHFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
    if (commandWindow)
    {
        commandWindow->Close(true);
        commandWindow = nullptr;
    }

    Close(true);           // Close main window
    wxTheApp->ExitMainLoop(); // Ensure all windows close and app exits
}