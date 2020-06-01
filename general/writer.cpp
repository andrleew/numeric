#include "writer.h"

using namespace NGeneral;

void TWriter::AddOutput(std::ostream& os) {
    Outputs.push_back(&os);
}

std::ostream& TWriter::GetOutput(size_t id) {
    return *Outputs[id];
}