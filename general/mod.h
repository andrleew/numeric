#ifndef MOD_H
#define MOD_H

#include <functional>
#include <unordered_map>
#include <vector>

namespace NGeneral {

    struct TProgram {
        std::function<int(const std::vector<std::string>&)> RunFunction;
        std::string explain;
    };

    class TMod {
    public:

        TMod(int _argc, const char* _argv[]);

        TMod& AddMode(const std::string& nameFunction
        , const std::function<int(const std::vector<std::string>&)>& function
        , const std::string& explanation);

        int Run();

        void Help();

    private:
        std::unordered_map<std::string, TProgram> Mods;
        std::vector<std::string> Argv;
        int Argc;
    };
}

#endif