#ifndef PRG_H
#define PRG_H
#include <random>

/// Will be used to obtain a seed for the random number engine
inline std::random_device rd;
/// Standard mersenne_twister_engine seeded with rd()
inline std::mt19937 gen(rd());


#endif //PRG_H
