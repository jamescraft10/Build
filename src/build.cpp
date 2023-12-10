#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

#include "pixel.hpp"

struct Function {
    std::string Name;
    std::string Value;
};

std::vector<Function> Init() {
    std::ifstream Program(".build");
    if (!Program.is_open()) {
        std::cerr << "Error opening file (make sure you have a .build file)\n";
        exit(EXIT_FAILURE);
    }

    std::vector<Function> funcs;
    std::string Name;
    std::string Value;

    while(Program >> Name) {
        Program >> std::ws;
        std::getline(Program, Value, ';');

        Function func = {Name, Value};
        funcs.push_back(func);
    }
    Program.close();

    // Start Message (the first time i use my terminal graphics i made a few months ago https://github.com/jamescraft10/Pixel/)
    Pixel::TurnOnBold();
    Pixel::BackgroundColor(7,7,7);
    Pixel::TextColor(233,233,233);
    Pixel::ClearScrean();
    Pixel::Print("Welcome to Build. To exit do the command \"exit\".\n");
    return funcs;
}

bool Update(std::vector<Function> funcs) {
    std::string Input;
    std::cin >> Input;
    for(int i = 0; i < funcs.size(); ++i) {
        if(funcs[i].Name == Input) {
            std::istringstream ss(funcs[i].Value);
            std::string line;

            while(std::getline(ss, line)) {
                if(!line.empty()) {
                    if(line == ";") {
                        return true;
                    }
                    std::system(line.c_str());
                }
            }
            return true;
        } else if(Input == "exit") {
            exit(EXIT_SUCCESS);
        }
    }
    return false;
}

int main() {
    std::vector<Function> funcs = Init();
    while(true) {
        bool ErrorCheck = Update(funcs);
        if(!ErrorCheck) {
            std::cout << "Not a vaild command(not in the .build file)\n";
        }
    }
    return EXIT_SUCCESS;
}