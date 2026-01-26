#include "fileconv.hpp"
#include "dir.hpp"
#include <iostream>

std::optional<std::filesystem::path> Conv(const std::filesystem::path& INpath, const std::string& extension) 
{
    // Вихідна директорія та ім'я файлу
    std::filesystem::path OUTpath = INpath.parent_path();
    std::string basename = INpath.stem().string();
    std::filesystem::path outputFile = OUTpath / (basename + "." + extension);

    // !!! Перевіряємо конфлікт перед конвертацією
    auto resolvedPath = resolve_output_conflict(outputFile);
    if (!resolvedPath)
    {
        std::cout << "Operation cancelled by user.\n";
        return std::nullopt;
    }

    // Якщо користувач змінив ім'я, оновлюємо outputFile
    outputFile = *resolvedPath;

    // Формуємо команду LibreOffice
    std::string command;
    
#if defined(_WIN32)
    command = "libreoffice --headless --convert-to " + extension +
              " --outdir \"" + OUTpath.string() + "\" \"" + INpath.string() + "\"";
#else
    command = "libreoffice --headless --convert-to " + extension +
              " --outdir \"" + OUTpath.string() + "\" \"" + INpath.string() + "\" > /dev/null 2>&1";
#endif

    std::cout << "Converting file... Please wait.\n";

    int result = system(command.c_str());
    if (result != 0)
    {
        std::cout << "LibreOffice conversion command failed.\n";
        return std::nullopt;
    }

    std::filesystem::path defaultOutput = OUTpath / (basename + "." + extension);

    if (!std::filesystem::exists(defaultOutput))
    {
        std::cout << "Output file was not created by LibreOffice.\n";
        return std::nullopt;
    }

    if (defaultOutput != outputFile)
    {
        try {
            std::filesystem::rename(defaultOutput, outputFile);
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            std::cout << "Failed to rename output file: " << e.what() << "\n";
            return std::nullopt;
        }
    }

    return outputFile;
}