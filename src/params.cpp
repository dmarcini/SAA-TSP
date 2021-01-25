#include "params.hpp"


int Params::iterations_number = 1000;

double Params::T = 10000.0;
int Params::L = 500;
double Params::r = 0.95;

void Params::calculate_new_temperature() {
    T *= r;
}
