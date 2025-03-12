// CommandFrame.cpp
#include "CommandFrame.h"
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>

/**
 * @brief Initializes the command execution frame layout.
 */
CommandFrame::CommandFrame(wxWindow* parent, ssh_session sshSession)
    : wxFrame(parent, wxID_ANY, "Command Execution", wxDefaultPosition, wxSize(500, 400)),
      session(sshSession)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    commandField = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(250, 30));
    wxButton* executeBtn = new wxButton(this, wxID_ANY, "Execute");
    outputBox = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition,
                               wxSize(480, 200),
                               wxTE_MULTILINE | wxTE_READONLY);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Enter Command:"), 0, wxLEFT, 10);
    sizer->Add(commandField, 0, wxEXPAND | wxALL, 10);
    sizer->Add(executeBtn, 0, wxALIGN_CENTER | wxALL, 10);
    sizer->Add(outputBox, 1, wxEXPAND | wxALL, 10);

    SetSizer(sizer);

    executeBtn->Bind(wxEVT_BUTTON, &CommandFrame::OnExecute, this);
}

/**
 * @brief Executes the user's command over SSH and displays the output.
 */
void CommandFrame::OnExecute(wxCommandEvent& WXUNUSED(event))
{
    wxString command = commandField->GetValue();
    ssh_channel channel = ssh_channel_new(session);
    if (channel == nullptr)
    {
        outputBox->AppendText("Error: Unable to create SSH channel.\n");
        return;
    }

    if (ssh_channel_open_session(channel) != SSH_OK)
    {
        outputBox->AppendText("Error: Unable to open SSH session.\n");
        ssh_channel_free(channel);
        return;
    }

    // Execute command using a full shell session
    wxString fullCommand = "sh -c '" + command + " 2>&1'"; // Redirect stderr to stdout

    if (ssh_channel_request_exec(channel, fullCommand.mb_str()) != SSH_OK)
    {
        outputBox->AppendText("Error: Failed to execute command.\n");
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        return;
    }

    char buffer[1024];
    int nbytes;
    wxString result;

    // Read stdout
    while ((nbytes = ssh_channel_read(channel, buffer, sizeof(buffer) - 1, 0)) > 0)
    {
        buffer[nbytes] = '\0';
        result += buffer;
    }

    // Check if there's anything on stderr (sometimes it's also read on the same stream)
    if ((nbytes = ssh_channel_read(channel, buffer, sizeof(buffer) - 1, 1)) > 0)
    {
        buffer[nbytes] = '\0';
        result += buffer;
    }

    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_channel_free(channel);

    if (result.IsEmpty())
    {
        result = "No output received.\n";
    }

    outputBox->AppendText(result + "\n");
}