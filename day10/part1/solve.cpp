#include <iostream>
#include <fstream>
#include "solve.hpp"

#define JOLT_CONVERSION 3

int main(void)
{
    std::ifstream infile("../input.txt");
    std::string line;
    std::vector<int> adapters, options;
    int one_jolts_variance = 0, three_jolts_variance = 0, max_adapter = 0, diff = 0;

    while (std::getline(infile, line))
        adapters.push_back(std::stoi(line));

    max_adapter = *std::max_element(adapters.begin(), adapters.end());
    three_jolts_variance++;
    adapters.insert(adapters.begin(), 0);

    for (int current_adapter : adapters)
    {
        if (current_adapter == max_adapter)
            continue;
        diff = get_option(&adapters, &options, current_adapter) - current_adapter;
        if (diff == 3)
            three_jolts_variance++;
        else if (diff == 1)
            one_jolts_variance++;

        options.clear();
    }

    std::cout << "total :: " << one_jolts_variance * three_jolts_variance << std::endl;
}

int get_option(std::vector<int> *adapters, std::vector<int> *options, int current_adapter)
{
    for (int maybe : *adapters)
        if (in_range(maybe, current_adapter + 1, current_adapter + 3))
            options->push_back(maybe);

    return *std::min_element(options->begin(), options->end());
}

bool in_range(int check, int lower, int upper)
{
    return (check >= lower && check <= upper);
}