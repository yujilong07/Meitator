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

        int choice{};
        std::cin >> choice;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice != 1)
        {
            return std::nullopt; 
        }
    }
}

bool is_filetype_suitable(const std::filesystem::path& path,Extensions mode){
    if (!path.has_extension()){
        return false;
    }
    std::string extension = path.extension().string();

    for (char& c : extension)
    {
        c = std::tolower(c);
    }

    if (mode == Extensions::DocxToPDF){
        return extension == ".docx";
    }
    else if(mode == Extensions::PDFtoDocx ){
        return extension == ".pdf";
    }

    return false;

}

bool file_exists(const std::filesystem::path& path){
    if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path)){
        return false;
    }
    else
        return true;
}

std::optional<std::filesystem::path> resolve_output_conflict(const std::filesystem::path& Outputpath){
    if (file_exists(Outputpath) == false){
        return Outputpath;
    }
    if (file_exists(Outputpath)){
        int choice{};
        std::string answer{};
        while (true)
        {
            std::cout << "In this directory exists file with same name as you gave: " << Outputpath << "\n" ;
            std::cout << "What you want to do?\n";
            std::cout << "  1 - Rewrite existing file,\n";
            std::cout << "  2 - Change the name of Output(new) file,\n";
            std::cout << "  3 - Cancel any changes\n";
            std::cout << "Choice: ";

            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choice > 3 || choice <= 0)
                return std::nullopt; 
            
            switch (choice)
            {
            case 1:
            do {
                std::cout << "Are you sure? (Y/n) \n";
                std::cin >> answer;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
                if (answer == "y" || answer == "Y") {
                    return Outputpath;
                } else if (answer == "n" || answer == "N") {
                    break;  
                } else {
                    std::cout << "You wrote wrong answer, try again\n";
                }
            } while (true);
            break;

            case 2:
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
            break;
            
            case 3:
                return std::nullopt; 
                break;
            }

            
        }
        
    }
    return std::nullopt;

}