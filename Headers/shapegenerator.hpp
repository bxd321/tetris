#pragma once
#include "defines.hpp"
#include <random>

class ShapeGenerator {
public:
    ShapeGenerator();
    ~ShapeGenerator();
    Shape generateNext();

private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
};