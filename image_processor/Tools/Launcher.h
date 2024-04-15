#pragma once
#include "FileHandler.h"
#include "Parser.h"
#include "Applier.h"

class Launcher {
public:
    Launcher() {
    }
    void Start(int argc, char* argv[]);
};
