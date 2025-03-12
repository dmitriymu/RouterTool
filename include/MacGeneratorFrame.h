// MacGeneratorFrame.h
#ifndef MACGENERATORFRAME_H
#define MACGENERATORFRAME_H

#include <wx/wx.h>
#include <vector>
#include "MacVendor.h" // For VendorMAC struct and loading function

/**
 * @class MacGeneratorFrame
 * @brief A window that allows the user to generate a random MAC for a selected vendor.
 */
class MacGeneratorFrame : public wxFrame
{
public:
    /**
     * @brief Constructs the MAC generator frame and loads vendor data from CSV.
     */
    MacGeneratorFrame();

private:
    wxComboBox* vendorDropdown;     ///< Dropdown to pick a vendor
    wxTextCtrl* generatedMacOutput; ///< Displays the generated MAC address
    wxTextCtrl* searchBox;          ///< Allows user to filter vendors by search text

    std::vector<VendorMAC> vendors;        ///< All loaded vendors
    std::vector<VendorMAC> filteredVendors;///< Filtered vendors after search

    /**
     * @brief Event handler for text changes in search box.
     * @param event The text change event.
     */
    void OnSearch(wxCommandEvent& event);

    /**
     * @brief Event handler for "Generate MAC" button.
     * @param event The button click event.
     */
    void OnGenerateMAC(wxCommandEvent& event);
};

#endif // MACGENERATORFRAME_H