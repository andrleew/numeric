#ifndef WRITER_H
#define WRITER_H

#include <iostream>
#include <vector>

namespace NGeneral {
    class TWriter {
    public:
        inline bool IsValid() const {
            return !Outputs.empty();
        }

        void AddOutput(std::ostream& os);
        std::ostream& GetOutput(size_t index);

    private:
        std::vector<std::ostream*> Outputs;
    };
}

#endif