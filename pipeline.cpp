#include "pipeline.h"

void Pipeline::advance() {

    WB = MEM;
    MEM = EX;
    EX = ID;
    ID = IF;

    IF.empty = true;
}