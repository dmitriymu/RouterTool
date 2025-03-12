// MacVendor.h
#ifndef MACVENDOR_H
#define MACVENDOR_H

#include <string>
#include <vector>

/**
 * @struct VendorMAC
 * @brief A small struct holding a MAC prefix and the associated vendor name.
 */
struct VendorMAC
{
    std::string macPrefix; ///< MAC prefix (e.g., "001A2B")
    std::string vendor;    ///< Vendor name (e.g., "Cisco")
};

/**
 * @brief Reads the CSV file and loads a list of VendorMAC entries.
 * @param filename Path to the CSV file (e.g., "mac-vendor.csv").
 * @return A vector of VendorMAC structs containing prefixes and vendor names.
 */
std::vector<VendorMAC> loadMacVendorList(const std::string& filename);

/**
 * @brief Generates a random MAC using the first three octets from `prefix` and random last 3.
 * @param prefix The first three octets of the MAC in a string (without separators, e.g. "001A2B").
 * @return A newly generated MAC string (e.g., "00:1A:2B:12:34:56").
 */
std::string generateRandomMAC(const std::string& prefix);

#endif // MACVENDOR_H