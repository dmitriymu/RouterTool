// NotesFrame.h
#ifndef NOTESFRAME_H
#define NOTESFRAME_H

#include <wx/wx.h>
#include <string>

/**
 * @class NotesFrame
 * @brief A simple text editor for saving and loading notes to a file.
 */
class NotesFrame : public wxFrame
{
public:
    /**
     * @brief Constructor, initializes the notes editor and loads saved content if available.
     */
    NotesFrame();

private:
    wxTextCtrl* notesEditor; ///< Text control for editing notes
    std::string notesFile;   ///< The file path for storing notes

    /**
     * @brief Reads notes from the file and displays them in the editor.
     */
    void LoadNotes();

    /**
     * @brief Saves notes to the file.
     * @param event The button click event.
     */
    void OnSave(wxCommandEvent& event);
};

#endif // NOTESFRAME_H