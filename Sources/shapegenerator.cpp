#include "shapegenerator.hpp"

static const Shape Shapes[] = {
    I, O, T, S, Z, J, L
};

ShapeGenerator::ShapeGenerator()
    : gen(rd()), dis(0, NUM_PIECES - 1) {}

ShapeGenerator::~ShapeGenerator() {}

Shape ShapeGenerator::generateNext() {
    return Shapes[dis(gen)];
}