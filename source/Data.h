#pragma once
#include <vector>

struct Data
{
    std::vector<double> inputs;
    int expectedOutcome;

    Data(std::vector<double> in, int out)
        : inputs(in), expectedOutcome(out) {}
};