#include <iostream>
#include <string>
#include <filesystem>
#include <optional>
#include <limits>

#include "dir.hpp"

std::optional<std::filesystem::path> ask_file_dir()
{
    while (true)
    {
        std::cout << "Enter path to the file:\n";

        std::string inputPath;
        std::getline(std::cin, inputPath);

        if (inputPath.empty())
        {
            std::cout << "Path cannot be empty.\n";
        }
        else
        {
            std::filesystem::path path(inputPath);

            if (std::filesystem::exists(path) &&
                std::filesystem::is_regular_file(path))
            {
                return path; 
            }
            else
            {
                std::cout << "File does not exist or is not a regular file.\n";
            }
        }

        std::cout << "Do you want to continue?\n";
        std::cout << "  1 - Yes\n";
        std::cout << "  2 - Cancel\n";
        std::cout << "Choice: ";

        std::string choiceStr;
        std::getline(std::cin, choiceStr);
        
        int choice = 0;
        try {
            choice = std::stoi(choiceStr);
        } catch (...) {
            choice = 2; // За замовчуванням Cancel
        }

        if (choice != 1)
        {
            return std::nullopt; 
        }
    }
}

bool is_filetype_suitable(const std::filesystem::path& path, Extensions mode)
{
    if (!path.has_extension())
    {
        return false;
    }
    
    std::string extension = path.extension().string();

    for (char& c : extension)
    {
        c = std::tolower(static_cast<unsigned char>(c));
    }

    if (mode == Extensions::DocxToPDF)
    {
        return extension == ".docx";
    }
    else if (mode == Extensions::PDFtoDocx)
    {
        return extension == ".pdf";
    }

    return false;
}

bool file_exists(const std::filesystem::path& path)
{
    return std::filesystem::exists(path) && 
           std::filesystem::is_regular_file(path);
}

std::optional<std::filesystem::path> resolve_output_conflict(const std::filesystem::path& Outputpath)
{
    if (!file_exists(Outputpath))
    {
        return Outputpath;
    }
    
    while (true)
    {
        std::cout << "In this directory exists file with same name: " 
                  << Outputpath << "\n";
        std::cout << "What you want to do?\n";
        std::cout << "  1 - Rewrite existing file,\n";
        std::cout << "  2 - Change the name of Output(new) file,\n";
        std::cout << "  3 - Cancel any changes\n";
        std::cout << "Choice: ";

        std::string choiceStr;
        std::getline(std::cin, choiceStr);
        
        int choice = 0;
        try {
            choice = std::stoi(choiceStr);
        } catch (...) {
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice <= 0 || choice > 3)
        {
            std::cout << "Invalid choice. Try again.\n";
            continue;
        }
        
        switch (choice)
        {
        case 1:
        {
            std::cout << "Are you sure? (Y/n): ";
            std::string answer;
            std::getline(std::cin, answer);
            
            if (answer == "y" || answer == "Y")
            {
                return Outputpath;
            }
            // Повертаємось до меню вибору
            break;
        }

        case 2:
        {
            while (true)
            {
                std::cout << "Enter a new file name (without extension):\n";

                std::string newName;
                std::getline(std::cin, newName);

                if (newName.empty())
                {
                    std::cout << "File name cannot be empty.\n";
                    continue;
                }

                std::filesystem::path newPath =
                    Outputpath.parent_path() /
                    (newName + Outputpath.extension().string());

                if (file_exists(newPath))
                {
                    std::cout << "File \"" << newPath.filename()
                              << "\" already exists. Try another name.\n";
                }
                else
                {
                    return newPath;
                }
            }
        }
        
        case 3:
            return std::nullopt;
        }
    }
}