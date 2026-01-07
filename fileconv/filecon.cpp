#include <filesystem>
#include <iostream>
#include <string>
namespace fs = std::filesystem;

void convert_prep(){
    std::string file_name;
    std::cout << "Enter the name of file you want to convert:" << std::endl;
    std::cin >> file_name;

    std::string input_fold_path = "input_file/";
    std::string input_file_path = input_fold_path + file_name;

    if (!fs::exists(input_file_path)){
        std::cerr << "Error: input file does not exist in directory!";
    }
}