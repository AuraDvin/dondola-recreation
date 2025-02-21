#include <cstring>

#include "src/GameManager.h"
#include "src/MyDebugger.h"

int main(const int argc, const char **argv) {
    srand(static_cast<unsigned>(time(nullptr)));
    if (argc > 1) {
        if (strcmp(argv[1], "--debug") == 0) {
            debugger::debug_mode = true;
            debugger::print_debug("Debug mode enabled");
        }
    }
    GameManager gm;
    return 0;
}
