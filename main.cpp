#include <cstring>

#include "src/GameManager.h"
#include "src/MyDebugger.h"
// #include "src/jsonReader.h"

int main(const int argc, const char **argv) {
    srand(static_cast<unsigned>(time(nullptr)));
    if (argc > 1) {
        if (strcmp(argv[1], "--debug") == 0) {
            debugger::debug_mode = true;
            debugger::print_debug("Debug mode enabled");
        }
    }
    // Json reader demo
    // const jsonReader jr("assets/dondola_test.json");
    // std::cout << jr.json["frames"]["Sprite-0002 0."]["frame"];
    GameManager gm;
    return 0;
}
