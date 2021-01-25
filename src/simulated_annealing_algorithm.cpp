#include "simulated_annealing_algorithm.hpp"

#include <string>
#include <numeric>
#include <algorithm>
#include <random>
#include <cmath>

#include "scanner.hpp"
#include "rand.hpp"

#include "params.hpp"


void SAA::load_data(const std::string &path,
                    LoadDataFcntPtr load_data)
{
    graph_.load(load_data(path));
}


void SAA::enter_stop_criterium()
{
    Params::iterations_number = get_int_parameter("iterations number");
}


void SAA::enter_algorithm_parameters()
{
    Params::T = get_double_parameter("initial temperature");
    Params::L = get_int_parameter("epoch length (number of "
                                  "internal iterations)");
    Params::r = get_double_parameter("temperature change factor");
}


void SAA::start()
{
    last_permutation_ = get_random_permutation();

    graph_.path().route() = last_permutation_;
    graph_.path().length() = calculate_path_length(last_permutation_);

    for (int i {0}; i < Params::iterations_number; ++i) {
        do_internal_iterations();

        Params::calculate_new_temperature();
    }

    graph_.print_path();
}


void SAA::do_internal_iterations()
{
    for (int i {0}; i < Params::L; ++i) {
        std::vector<int> adjacent_permutation {
            get_adjacent_permutation(last_permutation_)
        };

        if (calculate_path_length(adjacent_permutation) <
            calculate_path_length(last_permutation_)) {
            graph_.path().route() = adjacent_permutation;
            graph_.path().length() = calculate_path_length(adjacent_permutation);
        }

        int delta {
            calculate_path_length(adjacent_permutation) -
            calculate_path_length(last_permutation_)
        };

        if (should_change_soulution(delta)) {
            last_permutation_ = adjacent_permutation;
        }
    }
}


std::vector<int> SAA::get_random_permutation()
{
    std::vector<int> permutation(graph_.size());

    std::generate(permutation.begin(), permutation.end(), [n = 0]() mutable {
        return n++;
    });
    std::shuffle(permutation.begin(), permutation.end(),
                 std::mt19937{std::random_device{}()});

    return permutation;
}


std::vector<int> SAA::get_adjacent_permutation(const std::vector<int> &permutation)
{
    std::vector<int> adjacent_permutation {permutation};

    int last_position {utility::rand(0, adjacent_permutation.size())};
    int new_position {utility::rand(0, adjacent_permutation.size())};

    int value {adjacent_permutation[last_position]};

    adjacent_permutation.erase(adjacent_permutation.begin() + last_position);
    adjacent_permutation.insert(adjacent_permutation.begin() + new_position, 
                                value);

    return adjacent_permutation;
}


bool SAA::should_change_soulution(int delta)
{
    if (delta < 0) {
        return true;
    }

    int divider {1000000};

    double x {utility::rand(0, divider) / static_cast<double>(divider)};

    if (x < std::pow(-delta, Params::T)) {
        return true;
    }

    return false;
}


int  SAA::calculate_path_length(std::vector<int> route) {
    int distance {0};

    for (size_t i = 0; i < route.size() - 1; ++i) {
        distance += graph_.distance(route[i], route[i + 1]);
    }

    return distance;
}


double SAA::get_double_parameter(std::string_view parameter)
{
    utility::Scanner scanner(std::cin);

    std::cout << "Enter " << parameter << ": ";

    while (!scanner.has_next_double()) {
        std::cout << parameter << " have to be double!\n";
        std::cout << "Enter " << parameter << ": ";
    }

    return scanner.next_double();
}


int SAA::get_int_parameter(std::string_view parameter)
{
    utility::Scanner scanner(std::cin);

    std::cout << "Enter " << parameter << ": ";

    while (!scanner.has_next_int()) {
        std::cout << parameter << " have to be integer!\n";
        std::cout << "Enter " << parameter << ": ";
    }

    return scanner.next_int();
}
