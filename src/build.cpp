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

std::string ToLower(std::string Value) {
    for(int i = 0; i < Value.size(); ++i) {
        Value[i] = tolower(Value[i]);
    }
    return Value;
}

std::vector<Function> Init() {
    std::ifstream Program(".build");
    if(!Program.is_open()) {
        std::cerr << "Error opening file (make sure you have a .build file)\n";
        std::exit(EXIT_FAILURE);
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
    Pixel::Print("Welcome to Build. Type \"Help\" to see all the commands.\n");
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
                        return false;
                    }
                    std::system(line.c_str());
                }
            }
            return false;
        } else if(ToLower(Input) == "exit") {
            std::exit(EXIT_SUCCESS);
        } else if(ToLower(Input) == "restart") {
            return true;
        } else if(ToLower(Input) == "help") {
            Pixel::Print("exit - Exits the program.\nrestart - Restarts the program and updates the .build so new things you type in there show up.\n");
            return false;
        }
    }
    Pixel::Print("Not valid command!\n");
    return false;
}

int main() {
    std::vector<Function> funcs = Init();
    while(true) {
        bool IsRestart = Update(funcs);
        if(IsRestart) {
            funcs = Init();
        } else if(!IsRestart) {
            continue;
        }
    }
    return EXIT_SUCCESS;
}