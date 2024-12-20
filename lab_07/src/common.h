#pragma once

#include <mutex>
#include <random>

extern std::mutex print_mutex;

// Используем один глобальный ГПСЧ для всех
inline std::mt19937& global_rng() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

inline int rollDice() {
    std::uniform_int_distribution<int> dist(1,6);
    return dist(global_rng());
}

// Для случайного смещения в движении
inline int randOffset(int range) {
    std::uniform_int_distribution<int> dist(-range, range);
    return dist(global_rng());
}