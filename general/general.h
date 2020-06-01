#ifndef GENERAL_H
#define GENERAL_H

#include <string>

namespace NGeneral {

    bool IsStartWith(const std::string& str, const std::string& prefix) {
        if (prefix.size() > str.size()) return false;
        for (size_t i = 0; i < prefix.size(); ++i)
            if (str[i] != prefix[i]) return false;
        return true;
    }
}

#endif