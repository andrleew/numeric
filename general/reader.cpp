#include "reader.h"

using namespace NGeneral;

TReader::TReader()
: CurId(0)
{}

void TReader::AddInput(std::istream& is) {
    Inputs.push_back(&is);
}

bool TReader::CheckInput() {
    auto is = Inputs[CurId];
    while (!is->eof() && isspace(is->get()));
    if (is->eof()) return false;
    else {
        is->unget();
        return true;
    }
}

std::istream& TReader::GetInput() {
    while (!CheckInput()) {
        ++CurId;
    }
    return *Inputs[CurId];
}