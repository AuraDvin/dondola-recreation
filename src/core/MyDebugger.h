#ifndef MY_DEBUGGER_H
#define MY_DEBUGGER_H

#include <iostream>


namespace debugger {
    inline bool debug_mode = false;
    void print_debug_impl() {
    }

    /// Private function for implementation of the print_debug function
    /// Prints out first, then recursively calls itself until it runs out of arguments
    /// Please call debugger::print_debug(args) function for debugging
    template<typename T, typename... Args>
    void print_debug_impl(T first, Args... args) {
        std::cout << first << " ";
        print_debug_impl(args...);
    }

    /// Prints debug statements depending on launch arguments, if no --debug is present at program launch, no data will be printed.
    /// @param args things to be printed.
    template<typename... Args>
    void print_debug(Args... args) {
        if (!debug_mode) {
            return;
        }
        print_debug_impl(args...);
        std::cout << std::endl;
    }
}

#endif //MY_DEBUGGER_H
