#ifndef READER_H
#define READER_H

#include <iostream>
#include <vector>

namespace NGeneral{
    class TReader {
    public:
    TReader();
    inline size_t CurrentId() const {
        return CurId;
    }

    inline bool IsValid() const {
        return CurId != Inputs.size();
    }

    void AddInput(std::istream&);
    std::istream& GetInput();

    private:
    bool CheckInput();

    private:
        std::vector<std::istream*> Inputs;
        size_t CurId;
    };
} // namespace NGeneral


#endif