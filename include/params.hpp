#ifndef PARAMS_HPP_
#define PARAMS_HPP_


class Params
{
public:
    static int iterations_number;

    // temperature value
    static double T;
    // epoch length (number of internal iterations)
    static int L;
    // temperature change factor
    static double r;

    static void calculate_new_temperature();
};


#endif // PARAMS_HPP_
