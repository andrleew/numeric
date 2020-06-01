#ifndef RUN_SOLUTION_H
#define RUN_SOLUTION_H

#include "reader.h"
#include "writer.h"
#include <iostream>

namespace NGeneral {
    template<class Solution>
    class TRunSolution {
    public:
        TRunSolution() {}

        inline void Do() {
            Solution s;
            s.Start(Is);
            s.Do(Is, Os);
            s.Finish(Os);
        }

        inline TRunSolution& Input(std::istream& is) {
            Is.AddInput(is);
            return *this;
        }

        inline TRunSolution& Output(std::ostream& os) {
            Os.AddOutput(os);
            return *this;
        }

    private:
        TReader Is;
        TWriter Os;
    };
} // namespace NGeneral


#endif