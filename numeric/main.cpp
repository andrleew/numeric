#include "mod.h"
#include "lab1.1.h"
#include "lab1.2.h"
#include "lab1.3.h"
#include "lab1.4.h"
#include "lab1.5.h"
#include "logger.h"

using namespace NGeneral;
using namespace NNumeric;

int main(int argc, const char* argv[]) {
    TMod mod(argc, argv);

    mod.AddMode("Lab1.1", LU, "First lab");
    mod.AddMode("Lab1.2", Running, "Second lab");
    mod.AddMode("Lab1.3", Iterations, "Third lab");
    mod.AddMode("Lab1.4", Rotations, "Fourth lab");
    mod.AddMode("Lab1.5", QR, "Fifth lab");

    return mod.Run();
}