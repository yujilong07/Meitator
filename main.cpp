#include <iostream>
#include <string>
#include <filesystem>
#include <limits>
#include <optional>

#include "logo.hpp"
#include "dirsearch/dir.hpp"
#include "fileconv/fileconv.hpp"
#include "fileconv/prep.hpp"

std::optional<int> readInt(const std::string& prompt, int min, int max);

int showMenu()
{
    std::cout << "DEBUG: Entering showMenu()\n" << std::flush;
    
    for(int i = 0; i < 5; i++)
        std::cout << MEITATOR_LOGO[i] << '\n';

    std::cout << "============================================\n" << std::flush;
    std::cout << "Welcome to file extension changer!\n" << std::flush;
    std::cout << "Choose your option:\n" << std::flush;
    std::cout << "  0: DocxToPDF\n" << std::flush;
    std::cout << "  1: PDFtoDocx\n" << std::flush;
    std::cout << "  2: Exit\n" << std::flush;

    std::cout << "DEBUG: Before readInt()\n" << std::flush;
    auto choice = readInt("Enter choice (0-2): ", 0, 2);
    std::cout << "DEBUG: After readInt()\n" << std::flush;
    
    if (!choice)
        return -1;

    return *choice;
}

std::optional<int> readInt(const std::string& prompt, int min, int max)
{
    std::cout << "DEBUG: Inside readInt()\n" << std::flush;
    
    while (true)
    {
        std::cout << prompt << std::flush;

        std::string line;
        std::getline(std::cin, line);

        std::cout << "DEBUG: Read line: '" << line << "'\n" << std::flush;

        if (line.empty())
            return std::nullopt;

        try {
            int value = std::stoi(line);
            if (value < min || value > max)
                throw std::out_of_range("range");

            return value;
        }
        catch (...) {
            std::cout << "Invalid input. Try again.\n" << std::flush;
        }
    }
}

int main()
{
    std::cout << "Starting Meitator...\n" << std::flush;
    
    std::cout << "DEBUG: Before checkLibreOffice()\n" << std::flush;
    if (!checkLibreOffice())
    {
        std::cout << "Warning: LibreOffice may not be properly configured.\n" << std::flush;
        return 1;
    }
    
    std::cout << "DEBUG: After checkLibreOffice(), entering main loop\n" << std::flush;

    while (true)
    {
        std::cout << "DEBUG: Top of while loop\n" << std::flush;
        
        int choice = showMenu();
        
        std::cout << "DEBUG: Got choice: " << choice << "\n" << std::flush;
        
        if (choice == 2)
            break;
        if (choice < 0)
            continue;

        std::string targetExt =
            (choice == 0) ? "pdf" :
            (choice == 1) ? "docx" : "";

        auto inputOpt = ask_file_dir();
        if (!inputOpt)
            continue;

        if (!is_filetype_suitable(
                *inputOpt,
                choice == 0 ? Extensions::DocxToPDF : Extensions::PDFtoDocx))
        {
            std::cout << "Invalid file type.\n" << std::flush;
            continue;
        }

        auto result = Conv(*inputOpt, targetExt);
        if (result)
            std::cout << "Success: " << result->string() << "\n" << std::flush;
        else
            std::cout << "Conversion failed.\n" << std::flush;

        std::cout << "============================================\n" << std::flush;
    }
    
    std::cout << "Goodbye!\n" << std::flush;
    return 0;
}