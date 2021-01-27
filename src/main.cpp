#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>

#include "menu.hpp"

#include "simulated_annealing_algorithm.hpp"


std::vector<std::vector<int>> load_data(const std::string &path)
{
    std::ifstream ifs(path);
    std::vector<std::vector<int>> matrix;
    int size;

    ifs >> size;

    for (int i {0}; i < size; ++i) {
        matrix.push_back({});

        for (int j {0}; j < size; ++j) {
            int value;

            ifs >> value;

            matrix[i].push_back(value);         
        }
    }

    if (matrix.empty()) {
        std::cout << "Invalid file path!\n";
        std::exit(-1);
    }

    return matrix;
}

int main() {
    SimulatedAnnealingAlgorithm saa;

    utility::Menu menu("\nTraveling Salesman Problem - "
                       "Simulated Annealing Algorithm");

    bool was_data_loaded {false};

    menu.append({"Load data", [&saa, &was_data_loaded]() { 
        saa.load_data(load_data);

        was_data_loaded = true;
    }});
    menu.append({"Enter stop criterium", [&saa]() {
        saa.enter_stop_criterium();
    }});
    menu.append({"Enter algorithm parameters", [&saa]() {
        saa.enter_algorithm_parameters();
    }});
    menu.append({"Start", [&saa, &was_data_loaded]() {
        if (!was_data_loaded) {
            std::cout << "\nFirst load data!\n";
            return;
        }

        saa.start();
    }});

    menu.show();
}
