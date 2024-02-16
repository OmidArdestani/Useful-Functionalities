#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <list>

struct SSystemInfo
{
    std::string OSName;
    std::string OSVersion;
    std::string OSManufacturer;
    std::string OSBuildType;
    std::string RegisteredOwner;
    std::string RegisteredOrganization;
    std::string ProductID;
    std::string OriginalInstallDate;
    std::string SystemBootTime;
    std::string SystemManufacturer;
    std::string SystemModel;
    std::list<std::string> ProcessorsInfo;
    std::string BIOSVersion;
    std::string WindowsDirectory;
    std::string SystemDirectory;
    std::string BootDevice;
    std::string SystemLocale;
    std::string InputLocale;
    std::string TimeZone;
    uint64_t TotalPhysicalMemory;
    uint64_t AvailablePhysicalMemory;
    uint64_t MemoryUsage(){return TotalPhysicalMemory-AvailablePhysicalMemory;}
    double MemoryUsagePercentage(){return (MemoryUsage() - TotalPhysicalMemory) * 100.0;};
    struct SVirtualMemory
    {
        uint64_t MaxSize;
        uint64_t Available;
        uint64_t InUse;
    }VirtualMemory;
    std::string PageFileLocation;
    std::string Domain;
    std::string LogonServer;
    struct SNetworkCard
    {
        std::string Info;
        std::string ConnectionName;
        std::string Status;
        bool DHCPEnabled;
        std::string DHCPServer;
        std::list<std::string> IpList;
    };
    std::list<SNetworkCard> NetworkCards;
    std::string HyperVRequirements;

    void FillSystemInfo(const std::string& systemInfoText)
    {
        #if defined(_WIN32) || defined(WIN32)
        // Regular expressions for extracting information
        std::regex osNameRegex(R"(OS Name:\s+(.*))");
        std::regex osVersionRegex(R"(OS Version:\s+(.*))");
        std::regex osManufacturerRegex(R"(OS Manufacturer:\s+(.*))");
        std::regex osBuildTypeRegex(R"(OS Build Type:\s+(.*))");
        std::regex registeredOwnerRegex(R"(Registered Owner:\s+(.*))");
        std::regex registeredOrganizationRegex(R"(Registered Organization:\s+(.*))");
        std::regex productIDRegex(R"(Product ID:\s+(.*))");
        std::regex originalInstallDateRegex(R"(Original Install Date:\s+(.*))");
        std::regex systemBootTimeRegex(R"(System Boot Time:\s+(.*))");
        std::regex systemManufacturerRegex(R"(System Manufacturer:\s+(.*))");
        std::regex systemModelRegex(R"(System Model:\s+(.*))");
        std::regex processorsRegex(R"(Processor\(s\) Installed:\s+(.*))");
        std::regex biosVersionRegex(R"(BIOS Version:\s+(.*))");
        std::regex windowsDirectoryRegex(R"(Windows Directory:\s+(.*))");
        std::regex systemDirectoryRegex(R"(System Directory:\s+(.*))");
        std::regex bootDeviceRegex(R"(Boot Device:\s+(.*))");
        std::regex systemLocaleRegex(R"(System Locale:\s+(.*))");
        std::regex inputLocaleRegex(R"(Input Locale:\s+(.*))");
        std::regex timeZoneRegex(R"(Time Zone:\s+(.*))");
        std::regex totalPhysicalMemoryRegex(R"(Total Physical Memory:\s+(\d+))");
        std::regex availablePhysicalMemoryRegex(R"(Available Physical Memory:\s+(\d+))");
        std::regex maxVirtualMemoryRegex(R"(Virtual Memory: Max Size:\s+(\d+))");
        std::regex availableVirtualMemoryRegex(R"(Virtual Memory: Available:\s+(\d+))");
        std::regex inUseVirtualMemoryRegex(R"(Virtual Memory: In Use:\s+(\d+))");
        std::regex pageFileLocationRegex(R"(Page File Location\(s\):\s+(.*))");
        std::regex domainRegex(R"(Domain:\s+(.*))");
        std::regex logonServerRegex(R"(Logon Server:\s+(.*))");

        // Search for matches and fill the structure accordingly
        std::smatch match;

        if (std::regex_search(systemInfoText, match, osNameRegex))
        {
            this->OSName = match[1].str();
        }
        if (std::regex_search(systemInfoText, match, osVersionRegex))
        {
            this->OSVersion = match[1].str();
        }
        if (std::regex_search(systemInfoText, match, osManufacturerRegex))
        {
            this->OSManufacturer = match[1].str();
        }
        if (std::regex_search(systemInfoText, match, osBuildTypeRegex))
        {
            this->OSBuildType = match[1].str();
        }
        if (std::regex_search(systemInfoText, match, registeredOwnerRegex))
        {
            this->RegisteredOwner = match[1].str();
        }
        if (std::regex_search(systemInfoText, match, registeredOrganizationRegex))
        {
            this->RegisteredOrganization = match[1].str();
        }
        if (std::regex_search(systemInfoText, match, productIDRegex))
        {
            this->ProductID = match[1].str();
        }
        if (std::regex_search(systemInfoText, match, totalPhysicalMemoryRegex))
        {
            this->TotalPhysicalMemory = std::stod(match[1].str());
        }
        if (std::regex_search(systemInfoText, match, availablePhysicalMemoryRegex))
        {
            this->AvailablePhysicalMemory = std::stod(match[1].str());
        }
        #elif __unix__
        // TODO implementing for UNIX
        #endif
    }
};

