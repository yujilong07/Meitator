#pragma once

#include <filesystem>
#include <optional>

enum class Extensions {
    DocxToPDF,
    PDFtoDocx
};


std::optional<std::filesystem::path> ask_file_dir();


bool is_filetype_suitable(const std::filesystem::path& path, Extensions mode);

bool file_exists(const std::filesystem::path& path);

std::optional<std::filesystem::path>
resolve_output_conflict(const std::filesystem::path& Outputpath);
