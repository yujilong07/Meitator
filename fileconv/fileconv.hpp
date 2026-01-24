#pragma once

#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>  
#include "prep.hpp"


std::optional<std::filesystem::path>
Conv(const std::filesystem::path& INpath, const std::string& extension);
