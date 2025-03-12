// MacVendor.cpp
#include "MacVendor.h"
#include <fstream>
#include <sstream>
#include <random>
#include <iomanip>
#include <iostream>

/**
 * @brief Reads the CSV file and loads a list of VendorMAC entries.
 */
std::vector<VendorMAC> loadMacVendorList(const std::string& filename)
{
    std::vector<VendorMAC> vendorList;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        // You might print/log an error, or handle it differently in production
        std::cerr << "Error opening file: " << filename << std::endl;
        return vendorList;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string mac, vendor;
        if (std::getline(ss, mac, ',') && std::getline(ss, vendor))
        {
            vendorList.push_back({mac, vendor});
        }
    }

    file.close();
    return vendorList;
}

/**
 * @brief Generates a random MAC address using the given prefix for the first 3 octets.
 */
std::string generateRandomMAC(const std::string& prefix)
{
    // Random generation setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 255);

    // Build a stringstream for the MAC address
    std::stringstream ss;

    // Add the prefix, inserting ':' every two chars
    for (size_t i = 0; i < prefix.length(); i += 2)
    {
        if (i > 0) ss << ":";
        ss << std::uppercase << prefix.substr(i, 2);
    }

    // Add 3 random octets
    for (int i = 0; i < 3; ++i)
    {
        ss << ":" << std::uppercase << std::hex
           << std::setw(2) << std::setfill('0') << dist(gen);
    }

    return ss.str();
}