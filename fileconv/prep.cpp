#include "prep.hpp"
#include <cstdlib>

std::optional<std::string> getLibrePath() {
    #if defined(_WIN32)
        std::vector<std::string> standPath = {
            "C:\\Program Files\\LibreOffice\\program\\soffice.exe",
            "C:\\Program Files (x86)\\LibreOffice\\program\\soffice.exe"
        };

        for (const auto& path : standPath){
            if(std::filesystem::exists(path)){
                return path;
            }
        } 

        std::cout << "LibreOffice not found in standard locations.\n";
        std::cout << "Please enter full path to soffice.exe: ";
        std::string userPath;
        std::getline(std::cin, userPath);

        if (!userPath.empty() && std::filesystem::exists(userPath)){
            return userPath;
        }
        else {
            std::cout << "Invalid path provided.\n";
            return std::nullopt; 
        }
    #elif defined(__linux__) || defined(__APPLE__)
        return "libreoffice";
    #else
        #error Unsupported OS
    #endif
}


bool checkLibreOffice() {

    // std::cout << "Checking for LibreOffice..." << std::flush;
    
    #if defined(__linux__) || defined(__APPLE__)
        int result = system("which libreoffice > /dev/null 2>&1");
        if (result == 0) {
            std::cout << " Found!\n" << std::flush;
            return true;
        } else {
            std::cout << " Not found in PATH.\n" << std::flush;
            return false;
        }
    #elif defined(_WIN32)
        auto librePathOpt = getLibrePath();
        if (librePathOpt) {
            std::cout << " Found!\n" << std::flush;
            return true;
        } else {
            std::cout << " Not found.\n" << std::flush;
            return false;
        }
    #endif
    
    return false;
}