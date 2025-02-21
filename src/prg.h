#ifndef PRG_H
#define PRG_H
#include <random>

inline std::random_device rd;  // Will be used to obtain a seed for the random number engine
inline std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()


#endif //PRG_H
