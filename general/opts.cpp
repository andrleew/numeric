#include "opts.h"
#include "general.h"
#include <iostream>

using namespace NGeneral;

TOpts& TOpts::AddOpt(const std::string& opt, const std::string& explain, bool isRequired) {
    Opts.insert({opt, TOption("", explain, isRequired)});
    return *this;
}

bool TOpts::Parce(const std::vector<std::string>& argv) {
    for (size_t i = 1; i < argv.size(); ++i) {
        if (IsStartWith(argv[i], "-")) Opts[argv[i]].Param = argv[i + 1];
    }
    return CheckRequired();
}

bool TOpts::CheckRequired() {
    for (const auto& it : Opts) {
        if (it.second.IsRequired && it.second.Param.empty()) return false;
    }
    return true;
}

std::string TOpts::Get(const std::string & str) {
    return Opts[str].Param;
}

bool TOpts::Has(const std::string& str) {
    return Opts.find(str) != Opts.end();
}

void TOpts::Help() {
    for (const auto& it : Opts)
        std::cout << "> " 
            << it.first 
            << " - " 
            << it.second.Explain 
            << (it.second.IsRequired ? "<- required" : "") 
            << "\n";
}