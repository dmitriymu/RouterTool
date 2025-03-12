// NotesFrame.cpp
#include "NotesFrame.h"
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/msgdlg.h>
#include <fstream>
#include <sstream>

/**
 * @brief Constructor. Loads existing notes from file if found.
 */
NotesFrame::NotesFrame()
    : wxFrame(nullptr, wxID_ANY, "Notes", wxDefaultPosition, wxSize(500, 400)),
      notesFile("notes.txt")
{
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Multiline text control for notes
    notesEditor = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    wxButton* saveBtn = new wxButton(this, wxID_ANY, "Save");

    vbox->Add(notesEditor, 1, wxEXPAND | wxALL, 10);
    vbox->Add(saveBtn, 0, wxALIGN_RIGHT | wxALL, 10);

    SetSizer(vbox);

    saveBtn->Bind(wxEVT_BUTTON, &NotesFrame::OnSave, this);

    LoadNotes(); // Load existing notes (if any)
}

/**
 * @brief Load notes from 'notes.txt' into the editor.
 */
void NotesFrame::LoadNotes()
{
    std::ifstream file(notesFile);
    if (file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        notesEditor->SetValue(buffer.str());
        file.close();
    }
}

/**
 * @brief Save notes to 'notes.txt'.
 */
void NotesFrame::OnSave(wxCommandEvent& WXUNUSED(event))
{
    std::ofstream file(notesFile);
    if (file.is_open())
    {
        file << notesEditor->GetValue().ToStdString();
        file.close();
        wxMessageBox("Notes saved successfully!", "Success", wxOK | wxICON_INFORMATION);
    }
    else
    {
        wxMessageBox("Error saving notes!", "Error", wxOK | wxICON_ERROR);
    }
}