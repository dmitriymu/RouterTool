// MacGeneratorFrame.cpp
#include "MacGeneratorFrame.h"
#include <wx/sizer.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/msgdlg.h>
#include <algorithm>

/**
 * @brief Constructs the MAC generator frame, loads CSV data, and sets up UI.
 */
MacGeneratorFrame::MacGeneratorFrame()
    : wxFrame(nullptr, wxID_ANY, "MAC Address Generator", wxDefaultPosition, wxSize(450, 250))
{
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Load vendor list
    vendors = loadMacVendorList("mac-vendor.csv");
    filteredVendors = vendors;

    // Search
    wxStaticText* searchLabel = new wxStaticText(panel, wxID_ANY, "Search Vendor:");
    vbox->Add(searchLabel, 0, wxLEFT | wxTOP, 10);

    searchBox = new wxTextCtrl(panel, wxID_ANY);
    vbox->Add(searchBox, 0, wxEXPAND | wxALL, 10);

    // Vendor dropdown
    vendorDropdown = new wxComboBox(panel, wxID_ANY);
    for (const auto& vendor : vendors)
    {
        vendorDropdown->Append(vendor.vendor);
    }
    vbox->Add(vendorDropdown, 0, wxEXPAND | wxALL, 10);

    // Generate button
    wxButton* generateBtn = new wxButton(panel, wxID_ANY, "Generate MAC");
    vbox->Add(generateBtn, 0, wxEXPAND | wxALL, 10);

    // Output field
    generatedMacOutput = new wxTextCtrl(panel, wxID_ANY, "",
                                        wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    vbox->Add(generatedMacOutput, 0, wxEXPAND | wxALL, 10);

    panel->SetSizer(vbox);

    // Bind events
    searchBox->Bind(wxEVT_TEXT, &MacGeneratorFrame::OnSearch, this);
    generateBtn->Bind(wxEVT_BUTTON, &MacGeneratorFrame::OnGenerateMAC, this);
}

/**
 * @brief Filters the dropdown list as the user types in the search box.
 */
void MacGeneratorFrame::OnSearch(wxCommandEvent& WXUNUSED(event))
{
    wxString query = searchBox->GetValue().Lower();
    vendorDropdown->Clear();
    filteredVendors.clear();

    // Filter vendors by search query
    for (const auto& vendor : vendors)
    {
        wxString vendorName = wxString::FromUTF8(vendor.vendor);
        if (vendorName.Lower().Find(query) != wxNOT_FOUND)
        {
            vendorDropdown->Append(vendor.vendor);
            filteredVendors.push_back(vendor);
        }
    }
}

/**
 * @brief Generates a random MAC address based on the selected vendor's prefix.
 */
void MacGeneratorFrame::OnGenerateMAC(wxCommandEvent& WXUNUSED(event))
{
    int selection = vendorDropdown->GetSelection();
    if (selection == wxNOT_FOUND)
    {
        wxMessageBox("Please select a vendor!", "Error", wxOK | wxICON_ERROR);
        return;
    }

    std::string selectedVendor = vendorDropdown->GetString(selection).ToStdString();
    std::string prefix;

    // Find the prefix for the chosen vendor
    for (const auto& vendor : vendors)
    {
        if (vendor.vendor == selectedVendor)
        {
            prefix = vendor.macPrefix;
            break;
        }
    }

    // Generate the MAC
    std::string generatedMAC = generateRandomMAC(prefix);
    generatedMacOutput->SetValue(generatedMAC);
}