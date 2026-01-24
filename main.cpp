#include <iostream>
#include <string>
#include <filesystem>

#include "dirsearch/dir.hpp"   // если там есть нужные объявления
#include "fileconv/prep.hpp"   // ask_file_dir, is_filetype_suitable, resolve_output_conflict
#include "fileconv/fileconv.hpp" // Conv
#include "logo.hpp"

int showMenu(){
    for(int i = 0; i < 5; i++) {
        std::cout << MEITATOR_LOGO[i] << std::endl;
    }
    std::cout << "============================================" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "Welcome to file extension changer!" <<std::endl;
    std::cout << "Choose your option:" << std::endl;
    std::cout << "    0: DocxToPDF" << std::endl;
    std::cout << "    1: PDFtoDocx" << std::endl;
    std::cout << "    2: Exit" << std::endl;
    std:: cout << "Enter choice (1-2): ";
    int Inchoice;
    std:: cin >> Inchoice;
    return Inchoice;
}

int main() {
    int choice;

    while (true) {
        choice = showMenu();

        if (choice == 2) break;  // Exit

        // Визначаємо розширення залежно від вибору
        std::string targetExt;
        if (choice == 0) targetExt = "pdf";
        else if (choice == 1) targetExt = "docx";
        else {
            std::cout << "Invalid choice. Try again.\n";
            continue;
        }

        // 1. Запитуємо файл у користувача
        auto inputOpt = ask_file_dir();
        if (!inputOpt) continue;  // користувач відмінив

        // 2. Перевіряємо формат
        if (!is_filetype_suitable(*inputOpt, (choice == 0 ? Extensions::DocxToPDF : Extensions::PDFtoDocx))) {
            std::cout << "Invalid file type for the selected conversion.\n";
            continue;
        }

        // 3. Формуємо вихідний шлях
        std::filesystem::path outputPath = inputOpt->parent_path() / ((*inputOpt).stem().string() + "." + targetExt);

        // 4. Перевіряємо, чи не перезаписуємо файл
        auto resolvedOutput = resolve_output_conflict(outputPath);
        if (!resolvedOutput) continue;  // користувач відмінив

        // 5. Конвертуємо
        auto result = Conv(*inputOpt, targetExt);

        if (result) {
            std::cout << "Conversion successful! Output: " << result->string() << "\n";
        } else {
            std::cout << "Conversion failed. Check LibreOffice installation or file permissions.\n";
        }

        std::cout << "============================================\n";
    }

    return 0;
}
