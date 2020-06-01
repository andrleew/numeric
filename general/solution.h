#ifndef SOLUTION_H
#define SOLUTION_H

#include "reader.h"
#include "writer.h"
#include <iostream>

namespace NGeneral {

    class TSolution {
        virtual void Start(TReader&) {}
        virtual void Do(TReader&, TWriter&) = 0;
        virtual void Finish(TWriter&) {}
    };
}

#endif