#ifndef OPTS_H
#define OPTS_H

#include <unordered_map>
#include <vector>
#include <string>

namespace NGeneral {

    struct TOption {
        std::string Param;
        std::string Explain;
        bool IsRequired;

        TOption(std::string param = "", std::string explain = "", bool isRequired = false)
        : Param(std::move(param))
        , Explain(std::move(explain))
        , IsRequired(isRequired) {}
    };

    class TOpts {
    public:
        TOpts& AddOpt(const std::string&, const std::string& explain = "", bool isRequired = false);
        bool Parce(const std::vector<std::string>&);
        std::string Get(const std::string&);
        bool Has(const std::string&);

        void Help();

    private:
        bool CheckRequired();

    private:
        std::unordered_map<std::string, TOption> Opts;
    };
}
#endif