#ifndef SIMULATED_ANNEALING_ALGORITHM_HPP_
#define SIMULATED_ANNEALING_ALGORITHM_HPP_

#include <functional>
#include <vector>

#include "graph.hpp"


using SAA = class SimulatedAnnealingAlgorithm;

class SimulatedAnnealingAlgorithm {
public:
    using LoadDataFcntPtr = 
        std::function<std::vector<std::vector<int>>(const std::string&)>;

    void load_data(const std::string &path, LoadDataFcntPtr load_data);

    void enter_stop_criterium();
    void enter_algorithm_parameters();

    void start();
private:
    void do_internal_iterations();

    std::vector<int> get_random_permutation();
    std::vector<int> get_adjacent_permutation(const std::vector<int> &permutation);

    bool should_change_soulution(int delta);

    int calculate_path_length(std::vector<int> route);

    double get_double_parameter(std::string_view param);
    int get_int_parameter(std::string_view param);

    Graph graph_;
    std::vector<int> last_permutation_;
};


#endif // SIMULATED_ANNEALING_ALGORITHM_HPP_
