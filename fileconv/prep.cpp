#include "prep.hpp"

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
    auto librePathOpt = getLibrePath();
    if (!librePathOpt) {
        std::cout << "LibreOffice was not found. File conversion requires LibreOffice in headless mode.\n";
        return false;
    }

    std::string command = "\"" + *librePathOpt + "\" --version >nul 2>&1";
#if defined(__linux__) || defined(__APPLE__)
    command = *librePathOpt + " --version > /dev/null 2>&1";
#endif

    int result = system(command.c_str());
    if (result == 0) {
        return true;
    } else {
        std::cout << "LibreOffice was found but failed to execute.\n";
        return false;
    }
}
