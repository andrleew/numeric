#include "mod.h"

#include <iostream>

using namespace NGeneral;

TMod::TMod(int argc, const char* argv[])
: Argc(std::move(argc))
{
    for (int i = 0; i < Argc; ++i)
        Argv.push_back(argv[i]);
}

TMod& TMod::AddMode(const std::string& nameFunction
    , const std::function<int(const std::vector<std::string>&)>& function
    , const std::string& explanation)
    {
        Mods.insert({nameFunction, {function, explanation}});
        return *this;
    }

int TMod::Run() {
    for (int i = 0; i < Argc; ++i){
        auto it = Mods.find(Argv[i]);
        if (it != Mods.end()) return it->second.RunFunction(Argv);
    }
    Help();
    return -1;
}

void TMod::Help() {
    for (const auto& it : Mods)
        std::cout << "> " << it.first << "\t" << it.second.explain << "\n";
}