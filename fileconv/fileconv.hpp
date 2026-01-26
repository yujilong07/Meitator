#ifndef FILECONV_HPP
#define FILECONV_HPP

#include <filesystem>
#include <optional>
#include <string>

std::optional<std::filesystem::path> Conv(const std::filesystem::path& INpath, const std::string& extension);

#endif 