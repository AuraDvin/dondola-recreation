//
// Created by aura on 21/02/25.
//

#ifndef MYDEBUGGER_H
#define MYDEBUGGER_H

#include <iostream>

namespace debugger{
    inline bool debug_mode = false;


    inline void print_debug_impl() {}

    template<typename T, typename... Args>
    void print_debug_impl(T first, Args... args) {
        if (debug_mode) {
            std::cout << first;
        }
        print_debug_impl(args...);
    }


    template<typename... Args>
    void print_debug(Args... args) {
        print_debug_impl(args...);
        if (debug_mode) {
            std::cout << std::endl;
        }
    }
}

#endif //MYDEBUGGER_H
