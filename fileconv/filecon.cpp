#include "fileconv.hpp"

// Conv(inputPath, targetExtension):

//   
//     2. Визначити outputDirectory
//          outputDirectory = inputPath.parent_directory

//     3. Визначити очікуване output-імʼя
//          baseName = імʼя input без розширення
//          outputFile = outputDirectory / (baseName + "." + targetExtension)

//     4. Сформувати команду LibreOffice
//          command =
//              libreoffice
//              --headless
//              --convert-to targetExtension
//              --outdir outputDirectory
//              inputPath

//     5. Виконати команду (system)

//     6. Якщо system повернув помилку
//          повернути failure

//     7. Перевірити: чи існує outputFile
//          якщо НІ
//              повернути failure

//     8. Повернути outputFile (success)



std::optional<std::filesystem::path> Conv(const std::filesystem::path& INpath,const std::string& extension) {
    // Вихідна директорія та імʼя файлу
    std::filesystem::path OUTpath = INpath.parent_path();
    std::string basename = INpath.stem().string();
    std::filesystem::path outputFile = OUTpath / (basename + "." + extension);

    // Формуємо команду LibreOffice
    std::string command = 
        "libreoffice --headless --convert-to " + extension +
        " --outdir \"" + OUTpath.string() + "\" \"" + INpath.string() + "\"";

    // Виконуємо команду
    int result = system(command.c_str());
    if (result != 0) {
        return std::nullopt;  // Помилка LibreOffice
    }

    // Перевіряємо, чи зʼявився файл
    if (!std::filesystem::exists(outputFile)) {
        return std::nullopt;  // Помилка конвертації
    }

    // Успіх — повертаємо шлях до output
    return outputFile;
}